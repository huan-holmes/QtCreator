#include "virtualwalldockwidget.h"


VirtualWallDockWidget::VirtualWallDockWidget(QWidget *parent, Paint *paint)
    : QDockWidget(parent), paint_(paint)
{
    ImageLabel = new QLabel(this);

    ImageLabel->setGeometry(0, 0, 20, 20);
    Img=new QImage; //新建一个image对象
    Img->load("/home/boocax/QtCreator/log/Icon/chuanganqizhuangtai.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
    Img->scaled(ImageLabel->size(), Qt::KeepAspectRatio);
    ImageLabel->setScaledContents(true);
    ImageLabel->setPixmap(QPixmap::fromImage(*Img)); //将图片放入label，使用setPixmap,注意指针*img
    VirtualWallType = new QLabel(this);
    VirtualWallType->setGeometry(3, 30, 75, 20);
    VirtualWallType->setStyleSheet("color: white;font: 14px");
    VirtualWallType->setText("虚拟墙类型:");
    LineButton = new QPushButton(this);
    LineButton->setGeometry(85, 30, 20, 20);
    LineButton->setStyleSheet("border:0.5px dotted white;");
    LineButton->setFlat(true);
    LineButton->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/line.png"));

    CurveButton = new QPushButton(this);
    CurveButton->setGeometry(110, 30, 20, 20);
    CurveButton->setStyleSheet("border:0.5px dotted white;");
    CurveButton->setFlat(true);
    CurveButton->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/curve.png"));

    SquareButton = new QPushButton(this);
    SquareButton->setGeometry(135, 30, 20, 20);
    SquareButton->setStyleSheet("border:0.5px dotted white;");
    SquareButton->setFlat(true);
    SquareButton->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/square.png"));

    AbnormalButton = new QPushButton(this);
    AbnormalButton->setGeometry(160, 30, 20, 20);
    AbnormalButton->setStyleSheet("border:0.5px dotted white;");
    AbnormalButton->setFlat(true);
    AbnormalButton->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/zidingyi.png"));

    VirtualWallColor = new QLabel(this);
    VirtualWallColor->setGeometry(3, 60, 75, 20);
    VirtualWallColor->setStyleSheet("color: white;font: 14px");
    VirtualWallColor->setText("虚拟墙颜色:");
    ColorButton = new QPushButton(this);
//    ColorPalette = new QPalette;
//    ColorPalette->setColor(QPalette::Button, Qt::blue);
//    ColorButton->setPalette(*ColorPalette);
    ColorButton->setStyleSheet("background-color: blue");
//    ColorButton->setFlat(true);
//    ColorButton->setAutoFillBackground(true);
    ColorButton->setGeometry(85, 60, 20, 20);

    BrushSizeLabel = new QLabel(this);
    BrushSizeLabel->setText("画笔大小:");
    BrushSizeLabel->setStyleSheet("color: white;font: 14px");
    BrushSizeLabel->setGeometry(3, 90, 75, 20);

    OneSizeButton = new QPushButton(this);
    OneSizeButton->setGeometry(85, 99, 20, 20);
    OneSizeButton->setStyleSheet("background-color: white;border-style: solid;border-width:0.5px;border-radius:1.25px;border-color: white;max-width:2.5px;max-height:2.5px;min-width:2.5px;min-height:2.5px;");

    TwoSizeButton = new QPushButton(this);
    TwoSizeButton->setGeometry(110, 97.5, 20, 20);
    TwoSizeButton->setStyleSheet("background-color: white;border-style: solid;border-width:0.5px;border-radius:2.5px;border-color: white;max-width:5px;max-height:5px;min-width:5px;min-height:5px;");

    ThreeSizeButton = new QPushButton(this);
    ThreeSizeButton->setGeometry(135, 95, 20, 20);
    ThreeSizeButton->setStyleSheet("background-color: white;border-style: solid;border-width:0.5px;border-radius:5px;border-color: white;max-width:10px;max-height:10px;min-width:10px;min-height:10px;");

    FourSizeButton = new QPushButton(this);
    FourSizeButton->setGeometry(165, 90, 20, 20);
    FourSizeButton->setStyleSheet("background-color: white;border-style: solid;border-width:0.5px;border-radius:10px;border-color: white;max-width:20px;max-height:20px;min-width:20px;min-height:20px;");


    RevokeButton = new QPushButton(this);
    RevokeButton->setText("撤销");
    RevokeButton->setGeometry(3, 130, 70, 20);
    RevokeButton->setStyleSheet("background-color: #FFE4AD;");

    CancelRevokeButton = new QPushButton(this);
    CancelRevokeButton->setText("取消撤销");
    CancelRevokeButton->setGeometry(103, 130, 70, 20);
    CancelRevokeButton->setStyleSheet("background-color: #FFE4AD;");

    EmptyButton = new QPushButton(this);
    EmptyButton->setText("清空");
    EmptyButton->setGeometry(3, 160, 70, 20);
    EmptyButton->setStyleSheet("background-color: #FFE4AD;");

    SaveButton = new QPushButton(this);
    SaveButton->setText("保存");
    SaveButton->setGeometry(103, 160, 70, 20);
    SaveButton->setStyleSheet("background-color: #FFE4AD;");
    connect(LineButton, SIGNAL(clicked()), this, SLOT(onLineClicked()));
    connect(AbnormalButton, SIGNAL(clicked()), this, SLOT(onAbnormalClicked()));
    connect(ColorButton, SIGNAL(clicked()), this, SLOT(onColorClicked()));
}

void VirtualWallDockWidget::onLineClicked()
{
    paint_->changeVirtualWallState();
}
void VirtualWallDockWidget::onAbnormalClicked()
{
    paint_->changeVirtualWallStateAbnormal();
}
void VirtualWallDockWidget::onColorClicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this);
    paint_->setVirtualWallColor(color);
    qDebug()<<color.red();
    qDebug()<<color.green();
    qDebug()<<color.blue();
    QString col = converRGB16HexStr(color);
    qDebug()<<col;
    ColorButton->setStyleSheet("background-color:" + col);
}
QString VirtualWallDockWidget::converRGB16HexStr(QColor color) {
    //r的rgb转化为16进制
    QString redStr = QString("%1").arg(color.red(),2,16,QChar('0'));
    //g的rgb转化为16进制
    QString greenStr = QString("%1").arg(color.green(),2,16,QChar('0'));
    //b的rgb转化为16进制
    QString blueStr = QString("%1").arg(color.blue(),2,16,QChar('0'));
    //将各rgb的拼接在一起形成#000000
    QString hexStr = "#"+redStr+greenStr+blueStr;
    //返回hexStr
    return hexStr;
}

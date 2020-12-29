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
    ColorPalette = new QPalette;
    ColorPalette->setColor(QPalette::Button, Qt::blue);
    ColorButton->setPalette(*ColorPalette);
    ColorButton->setStyleSheet("background-color: blue");
    //ColorButton->setFlat(true);
    ColorButton->setGeometry(85, 60, 20, 20);

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

}

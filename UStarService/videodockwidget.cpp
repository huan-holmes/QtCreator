#include "videodockwidget.h"

VideoDockWidget::VideoDockWidget(QWidget *parent)
    : QDockWidget(parent)
{
    VideoShowLabel = new QLabel(this);
    VideoShowLabel->setGeometry(5, 20, 190, 230);
    Img = new QImage; //新建一个image对象
    Img->load("/home/boocax/QtCreator/log/1.jpeg"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
    qDebug()<<width();
    Img->scaled(VideoShowLabel->size(), Qt::KeepAspectRatio);
    VideoShowLabel->setScaledContents(true);
    VideoShowLabel->setPixmap(QPixmap::fromImage(*Img)); //将图片放入label，使用setPixmap,注意指针*img
}


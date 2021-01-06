#include "videodockwidget.h"

VideoDockWidget::VideoDockWidget(QWidget *parent)
    : QDockWidget(parent)
{
    socket_ = new QTcpSocket();
    VideoShowLabel = new QLabel(this);
    VideoShowLabel->setGeometry(5, 20, 190, 230);
    //Img = new QImage; //新建一个image对象

    VideoShowLabel->setScaledContents(true);
    //Img->load("/home/boocax/QtCreator/log/1.jpeg"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
    InitSocketInfo();



}

VideoDockWidget::~VideoDockWidget()
{
//    QString br = "-1";
//    socket_->write(br.toUtf8().data());
    qDebug()<<"----~VideoDockWidget()----";
    socket_->disconnectFromHost();
    socket_->close();
}
void VideoDockWidget::InitSocketInfo()
{
    QString ip = "127.0.0.1";
    qint16 port = 1234;
    socket_->connectToHost(QHostAddress(ip),port);
    if (!socket_->waitForConnected(30000))
    {
        QMessageBox::information(this, "QT网络通信", "连接服务端失败！");
    }
    QString pwd = "hello world;";
    socket_->write(pwd.toUtf8().data());
    ReadSocketImage2Label();
}
void VideoDockWidget::ReadSocketImage2Label()
{
    qDebug()<<"----ReadSocketImage2Label()---";
    socket_->waitForReadyRead(1000);
    char recvMsg[65536] = {0};
    int recvRe = socket_->read(recvMsg, 65536);
    //QString res = recvMsg;
    std::vector<uchar> vec_data(recvMsg, recvMsg+65536);
    //qDebug()<<vec_data[0];
    cv::Mat img;
    cv::imdecode(cv::Mat(vec_data), CV_LOAD_IMAGE_COLOR, &img);
    Img = QImage((const uchar*)(img.data), img.cols, img.rows, img.cols * img.channels(), QImage::Format_RGB888);
    Img.scaled(VideoShowLabel->size(), Qt::KeepAspectRatio);
    qDebug()<<1;
    VideoShowLabel->setPixmap(QPixmap::fromImage(Img)); //将图片放入label，使用setPixmap,注意指针*img
}

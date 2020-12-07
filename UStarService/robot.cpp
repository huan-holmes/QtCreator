#include "robot.h"


RobotWindow::RobotWindow(QDialog *parent) :
    QDialog(parent),
    connect_flag_(false),
    write_file_(false)
{
    qDebug()<<"robot";
    //this->setGeometry(700, 350, 500, 400);
    this->setWindowTitle(tr("选择机器人"));
    this->setStyleSheet("background-color:gray;");
    this->setMaximumSize(500, 400);
    this->setMinimumSize(500, 400);






    //ip Label
    ip_ = new QLabel(this);   //new一个标签对象
    ip_->move(140,80);         //移动到(70,80)位置(Label左上角坐标，相对于父窗体)
    ip_->setText("ip :");  //设置标签文本

    //ip 输入框
    ip_edi_ = new QLineEdit(this);
    ip_edi_->move(180,80);
    ip_edi_->setPlaceholderText(tr("请输入ip!"));//占位符

    port_ = new QLabel(this);
    port_->move(140, 130);
    port_->setText("port :");
    //
    port_edi_ = new QLineEdit(this);
    port_edi_->move(180, 130);
    ip_edi_->setPlaceholderText(tr("请输入port!"));//占位符
    //密码Label
    pwd_ = new QLabel(this);
    pwd_->move(140,180);
    pwd_->setText("密码:");

    //密码输入框
    pwd_edi_ = new QLineEdit(this);
    pwd_edi_->move(180,180);
    pwd_edi_->setPlaceholderText("请输入密码!");
    pwd_edi_->setEchoMode(QLineEdit::Password);//输入的密码以圆点显示

    //连接
    connect_ = new QPushButton(this);
    connect_->move(140,270);
    connect_->setText("连接");

    send_ = new QPushButton(this);
    send_->move(250, 270);
    send_->setText("发送");

    connect(connect_,SIGNAL(clicked()),this,SLOT(onConnectClicked()));
    connect(send_,SIGNAL(clicked()),this,SLOT(onSendData()));
}

RobotWindow::~RobotWindow()
{
    socket_->disconnectFromHost();
    socket_->close();
}

void RobotWindow::onConnectClicked()
{
    socket_ = new QTcpSocket();
    QString ip = this->ip_edi_->text();
    qint16 port = this->port_edi_->text().toInt();
    qDebug()<< ip;
    qDebug()<< port;

    socket_->connectToHost(QHostAddress(ip),port);
    if (!socket_->waitForConnected(30000))
    {
        QMessageBox::information(this, "QT网络通信", "连接服务端失败！");
        return;
    }
    connect(socket_, SIGNAL(readyRead()), this, SLOT(onReceivedData()));
}
void RobotWindow::onSendData()
{
    QString s;
    if (!connect_flag_)
    {
        QString pwd = this->pwd_edi_->text();
        s = pwd + "hello world!";
        connect_flag_ = true;
    }
    else
    {
        s = "hello world!";
    }
    socket_->write(s.toUtf8().data());
}

void RobotWindow::onReceivedData()
{
    char recvMsg[1024] = {0};
    int recvRe = socket_->read(recvMsg, 1024);
    QString res = recvMsg;
    if(recvRe == -1 || res == "登入失败")
    {
        QMessageBox::information(this, "QT网络通信", "接收服务端数据失败！");
        connect_flag_ = false;
    }
    if(!write_file_)
    {
        QString data_file = "/home/boocax/QtCreator/log";
        QDir dir_;
        bool exist = dir_.exists(data_file);
        if(!exist)
        {

            bool isok = dir_.mkdir(data_file); // 新建文件夹

                if(!isok)

                    QMessageBox::warning(this,"sdf","can't mkdir",QMessageBox::Yes);

        }
        QString fileName = data_file+"/"+"login.txt";
        QFile file(fileName);
        if(!file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append))

        {

            QMessageBox::warning(this,"sdf","can't open",QMessageBox::Yes);

        }

        QTextStream stream(&file);

        stream<<ip_edi_->text()<<"\n";

        file.close();
        write_file_ = true;
    }
    qDebug()<<res;
}

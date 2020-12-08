#include "robot.h"


RobotWindow::RobotWindow(QDialog *parent) :
    QDialog(parent),
    connect_flag_(false),
    write_flag_(false)
{
    qDebug()<<"robot";
    //this->setGeometry(700, 350, 500, 400);
    this->setWindowTitle(tr("选择机器人"));
    this->setStyleSheet("background-color:gray;");
    this->setMaximumSize(500, 400);
    this->setMinimumSize(500, 400);






    //ip Label
    IpLabel = new QLabel(this);   //new一个标签对象
    IpLabel->move(140,80);         //移动到(70,80)位置(Label左上角坐标，相对于父窗体)
    IpLabel->setText("ip :");  //设置标签文本

    //ip 输入框
    IpLineEdit = new QLineEdit(this);
    IpLineEdit->move(180,80);
    IpLineEdit->setPlaceholderText(tr("请输入ip!"));//占位符

    PortLabel = new QLabel(this);
    PortLabel->move(140, 130);
    PortLabel->setText("port :");
    //
    PortLineEdit = new QLineEdit(this);
    PortLineEdit->move(180, 130);
    PortLineEdit->setPlaceholderText(tr("请输入port!"));//占位符
    //密码Label
    PwdLabel = new QLabel(this);
    PwdLabel->move(140,180);
    PwdLabel->setText("密码:");

    //密码输入框
    PwdLineEdit = new QLineEdit(this);
    PwdLineEdit->move(180,180);
    PwdLineEdit->setPlaceholderText("请输入密码!");
    PwdLineEdit->setEchoMode(QLineEdit::Password);//输入的密码以圆点显示

    //连接
    ConnectButton = new QPushButton(this);
    ConnectButton->move(140,270);
    ConnectButton->setText("连接");

    SendButton = new QPushButton(this);
    SendButton->move(250, 270);
    SendButton->setText("发送");

    connect(ConnectButton,SIGNAL(clicked()),this,SLOT(onConnectClicked()));
    connect(SendButton,SIGNAL(clicked()),this,SLOT(onSendDataClicked()));
}

RobotWindow::~RobotWindow()
{
    socket_->disconnectFromHost();
    socket_->close();
}

void RobotWindow::onConnectClicked()
{
    socket_ = new QTcpSocket();
    QString ip = this->IpLineEdit->text();
    qint16 port = this->PortLineEdit->text().toInt();
    qDebug()<< ip;
    qDebug()<< port;

    socket_->connectToHost(QHostAddress(ip),port);
    if (!socket_->waitForConnected(30000))
    {
        QMessageBox::information(this, "QT网络通信", "连接服务端失败！");
    }
    connect(socket_, SIGNAL(readyRead()), this, SLOT(onReceivedData()));
}
void RobotWindow::onSendDataClicked()
{
    QString s;
    if (!connect_flag_)
    {
        QString pwd = this->PwdLineEdit->text();
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
        return;
    }
    if(!write_flag_)
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

        stream<<IpLineEdit->text()<<"\n";

        file.close();
        write_flag_ = true;
    }
    qDebug()<<res;
}

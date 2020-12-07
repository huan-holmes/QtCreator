#include "robot.h"


RobotWindow::RobotWindow(QDialog *parent) :
    QDialog(parent)
{
    qDebug()<<"robot";
    //this->setGeometry(700, 350, 500, 400);
    this->setWindowTitle(tr("选择机器人"));
    this->setStyleSheet("background-color:gray;");
    this->setMaximumSize(500, 400);
    this->setMinimumSize(500, 400);


    socket_ = new QTcpSocket();



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
    connect_->move(200,270);
    connect_->setText("连接");

    connect(connect_,SIGNAL(clicked()),this,SLOT(onConnectClicked()));
}

RobotWindow::~RobotWindow()
{

}

void RobotWindow::onConnectClicked()
{
    QString ip = this->ip_edi_->text();
    qint16 port = this->port_edi_->text().toInt();
    qDebug()<< ip;
    qDebug()<< port;

}

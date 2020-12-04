#include "robot.h"


RobotWindow::RobotWindow(QWidget *parent) :
    QWidget(parent)
{
    qDebug()<<"robot";
    this->setWindowTitle(tr("选择机器人"));

    //ip Label
    ip_ = new QLabel(this);   //new一个标签对象
    ip_->move(80,80);         //移动到(70,80)位置(Label左上角坐标，相对于父窗体)
    ip_->setText("ip :");  //设置标签文本

    //ip 输入框
    ip_edi_ = new QLineEdit(this);
    ip_edi_->move(120,80);
    ip_edi_->setPlaceholderText(tr("请输入ip!"));//占位符

    //密码Label
    pwd_ = new QLabel(this);
    pwd_->move(80,130);
    pwd_->setText("密码:");

    //密码输入框
    pwd_edi_ = new QLineEdit(this);
    pwd_edi_->move(120,130);
    pwd_edi_->setPlaceholderText("请输入密码!");
    pwd_edi_->setEchoMode(QLineEdit::Password);//输入的密码以圆点显示

    //连接
    connetct_ = new QPushButton(this);
    connetct_->move(100,200);
    connetct_->setText("连接");
}

RobotWindow::~RobotWindow()
{

}

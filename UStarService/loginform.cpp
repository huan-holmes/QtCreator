#include "loginform.h"
#include <QMessageBox>

LoginForm::LoginForm(QDialog *parent) :
    QDialog(parent)
{
    //设置窗体标题
    this->setStyleSheet("background-color:#1E1E1E;");
    this->setMaximumSize(608, 735);
    this->setMinimumSize(608, 735);
    this->setWindowTitle(tr("欢迎使用优智达"));

    logo_label_ = new QLabel(this);

    logo_ = new QImage();

    logo_label_->setScaledContents(true);
    logo_label_->resize(155, 207);
    logo_label_->move(227, 87);
    logo_->load("/home/boocax/QtCreator/log/Icon/logo2.png");
    logo_label_->setPixmap(QPixmap::fromImage(*logo_));

    DescriptionLabel1 = new QLabel(this);
    DescriptionLabel1->setGeometry(212, 334, 199, 50);
    DescriptionLabel1->setText("优智达机器人");
    QFont font1("Microsoft YaHei", 25, 75);
    DescriptionLabel1->setFont(font1);
    DescriptionLabel1->setAlignment(Qt::AlignCenter);
    DescriptionLabel1->setStyleSheet("color: #FFFFFF;");
    DescriptionLabel2 = new QLabel(this);
    DescriptionLabel2->setGeometry(190, 396, 240, 28);
    DescriptionLabel2->setText("全国领先的机器人管理软件");
    QFont font2("Microsoft ChangGuiTi", 15);
    DescriptionLabel2->setFont(font2);
    DescriptionLabel2->setAlignment(Qt::AlignCenter);
    DescriptionLabel2->setStyleSheet("color: #FFFFFF;");
    //用户名Label
    userNameLbl = new QLabel(this);   //new一个标签对象
    userNameLbl->setGeometry(166, 453, 48, 22);
    userNameLbl->setText("用户名:");  //设置标签文本
    userNameLbl->setAlignment(Qt::AlignCenter);

    //用户名输入框
    userNameLEd = new QLineEdit(this);
    userNameLEd->setGeometry(225, 448, 200, 32);
    userNameLEd->setPlaceholderText(tr("请输入用户名!"));//占位符

    //密码Label
    pwdLbl = new QLabel(this);
    pwdLbl->setGeometry(179, 508, 32, 22);
    pwdLbl->setText("密码:");

    //密码输入框
    pwdLEd = new QLineEdit(this);
    pwdLEd->setGeometry(225, 503, 200, 32);
    pwdLEd->setPlaceholderText("请输入密码!");
    pwdLEd->setEchoMode(QLineEdit::Password);//输入的密码以圆点显示

    PWDCheckBox = new QCheckBox(this);
    PWDCheckBox->setGeometry(225, 563, 16, 16);

    RememberLabel = new QLabel(this);
    RememberLabel->setGeometry(245, 559, 60, 22);
    RememberLabel->setText("记住密码");

    ForgetLabel = new QLabel(this);
    ForgetLabel->setGeometry(358, 559, 60, 22);
    ForgetLabel->setText("<u>忘记密码</u>");
    //登录按钮
    loginBtn = new QPushButton(this);
    loginBtn->setGeometry(225, 605, 72, 32);
    loginBtn->setText("提交");
    loginBtn->setStyleSheet("background-color: #FFE4AD;");

    //退出按钮
    exitBtn = new QPushButton(this);
    exitBtn->setGeometry(355, 605, 72, 32);
    exitBtn->setStyleSheet("background-color: #FFE4AD;");
    exitBtn->setText("退出");

    MapCheckBox = new QCheckBox(this);
    MapCheckBox->setGeometry(355, 670, 16, 16);
    MapLabel = new QLabel(this);
    MapLabel->setGeometry(375, 665, 60, 22);
    MapLabel->setText("建图人员");

    OperationCheckBox = new QCheckBox(this);
    OperationCheckBox->setGeometry(443, 670, 16, 16);
    OperationLabel = new QLabel(this);
    OperationLabel->setGeometry(463, 665, 60, 22);
    OperationLabel->setText("运维人员");

    //单击登录按钮时 执行 LoginForm::login 槽函数(自定义)；单击退出按钮时 执行 LoginForm::close 槽函数(窗体的关闭函数，不用自己写)
    connect(loginBtn,&QPushButton::clicked,this,&LoginForm::login);
    connect(exitBtn,&QPushButton::clicked,this,&LoginForm::close);


}

void LoginForm::login()
{
    //获得userNameLEd输入框的文本：userNameLEd->text()；
    //trimmed()去掉前后空格
    //tr()函数，防止设置中文时乱码
    if(userNameLEd->text().trimmed() == tr("ustar") && pwdLEd->text() == tr("ustar123"))
    {
//        QDateTime dTime;
//        QTime time;
//        QDate date;
//        dTime.setTime(time.currentTime());
//        dTime.setDate(date.currentDate());
//        QString currentDate = dTime.toString("yyyy:MM:dd:hh:mm:ss");
//        qDebug()<<currentDate;
//        QString data_file = "/home/boocax/QtCreator/log";
//        QDir dir_;
//        bool exist = dir_.exists(data_file);
//        if(!exist)
//        {

//            bool isok = dir_.mkdir(data_file); // 新建文件夹

//                if(!isok)

//                    QMessageBox::warning(this,"sdf","can't mkdir",QMessageBox::Yes);

//        }
//        QString fileName = data_file+"/"+"login.txt";
//        QFile file(fileName);
//        if(!file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append))

//        {

//            QMessageBox::warning(this,"sdf","can't open",QMessageBox::Yes);

//        }

//        QTextStream stream(&file);

//        stream<<currentDate+":"+"ustar"<<"\n";

//        file.close();
        writeLog(userNameLEd->text().trimmed());
        //accept();//关闭窗体，并设置返回值为Accepted
        done(1);
    }
    else if(userNameLEd->text().trimmed() == tr("ustar123") && pwdLEd->text() == tr("ustar123"))
    {
        writeLog(userNameLEd->text().trimmed());
        done(2);
    }
    else
    {                              //标题              内容                OK按钮
       QMessageBox::warning(this, tr("警告！"),tr("用户名或密码错误！"),QMessageBox::Yes);

    // 清空输入框内容
       userNameLEd->clear();
       pwdLEd->clear();

       //光标定位
       userNameLEd->setFocus();
    }
}
void LoginForm::writeLog(QString str)
{
    QDateTime dTime;
    QTime time;
    QDate date;
    dTime.setTime(time.currentTime());
    dTime.setDate(date.currentDate());
    QString currentDate = dTime.toString("yyyy:MM:dd:hh:mm:ss");
    qDebug()<<currentDate;
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

    stream<<currentDate+":"+str<<"\n";

    file.close();
}


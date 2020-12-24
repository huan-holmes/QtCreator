#include "mianwindow.h"
#include "operationwidget.h"
#include <QApplication>
#include "loginform.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //MainWindow mw;
    LoginForm login;
    OperationWidget ow;
    if (login.exec() == QDialog::Accepted)//调用login.exec()，阻塞主控制流，直到完成返回，继续执行主控制流
    {
       ow.show();
    }
    return app.exec();
//    QApplication a(argc, argv);
//    //MainWindow w;
//    //w.show();

//    QFont font("ZYSong18030" , 12);
//    a.setFont(font);

//    QSplitter *splitterMain = new QSplitter(Qt::Vertical, 0); //新建主分割窗口，水平分割
//    splitterMain->setGeometry(450, 50, 1500, 1200);
//    MainWindow mw;
//    //QMainWindow *qw = new QMainWindow(MainWindow::MainWindow, splitterMain);
//    splitterMain->addWidget(&mw);
//    //QTextEdit *textLeft = new QTextEdit(QObject::tr("左部件"),splitterMain);

//    QSplitter *splitterBottom = new QSplitter(Qt::Horizontal, splitterMain);   //右分割窗口，并以主分割窗口作为父窗口
//    splitterBottom->setOpaqueResize(false);

//    QTextEdit *textleft = new QTextEdit(QObject::tr("上部件"),splitterBottom);
//    textleft->setAlignment(Qt::AlignCenter);

//    QTextEdit *textMiddle = new QTextEdit(QObject::tr("中间部件"),splitterBottom);
//    textMiddle->setAlignment(Qt::AlignCenter);

//    QTextEdit *textright = new QTextEdit(QObject::tr("底部部件"),splitterBottom);
//    textright->setAlignment(Qt::AlignCenter);

//    splitterMain->setStretchFactor(1,1);
//    //splitterMain->setWindowTitle(QObject::tr("分割窗口"));
//    splitterMain->show();
//    return a.exec();
}

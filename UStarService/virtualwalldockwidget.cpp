#include "virtualwalldockwidget.h"


VirtualWallDockWidget::VirtualWallDockWidget(QWidget *parent)
    : QDockWidget(parent)
{
    qDebug()<<"v";
    //setWindowTitle("虚拟墙");
    QLabel *VirtualWallType = new QLabel(this);
    VirtualWallType->setGeometry(0, 0, 100, 20);
    VirtualWallType->setText("虚拟墙类型:");
//    QTextEdit *te = new QTextEdit("MainWindow",this);
//    te->setAlignment(Qt::AlignCenter);
//    setCentralWidget(te);

//    //停靠窗口1
//    QDockWidget *dw1 = new QDockWidget("停靠窗口1",this);//构建停靠窗口，指定父类

//    dw1->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable);//设置停靠窗口特性，可移动，可关闭

//    dw1->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);//设置可停靠区域为主窗口左边和右边

//    QTextEdit *dte = new QTextEdit("DockWindow First");
//    dw1->setWidget(dte);
//    addDockWidget(Qt::RightDockWidgetArea,dw1);

//    //停靠窗口2
//    QDockWidget *dw2 = new QDockWidget("停靠窗口2",this);//构建停靠窗口，指定父类

//    dw2->setFeatures(QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetClosable);//设置停靠窗口特性，可浮动,可关闭

//    QTextEdit *dte2 = new QTextEdit("DockWindow Second");
//    dw2->setWidget(dte2);
//    addDockWidget(Qt::RightDockWidgetArea,dw2);

//    //停靠窗口3
//    QDockWidget *dw3 = new QDockWidget("停靠窗口3",this);//构建停靠窗口，指定父类

//    dw3->setFeatures(QDockWidget::AllDockWidgetFeatures);//设置停靠窗口特性，具有全部停靠窗口的特性

//    QTextEdit *dte3 = new QTextEdit("DockWindow Third");
//    dw3->setWidget(dte3);
//    addDockWidget(Qt::RightDockWidgetArea,dw3);


}

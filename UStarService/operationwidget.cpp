#include "operationwidget.h"
OperationWidget::OperationWidget(QWidget *parent):
    QWidget(parent)
{
    this->setGeometry(300, 30, 1200, 1000);
    this->setStyleSheet("background-color:#1E1E1E;");
    MainVLayout = new QVBoxLayout(this);
    MVLFirstWidget = new QWidget(this);
    MVLSecondWidget = new QWidget(this);
    MVLThirdWidget = new QWidget(this);
    MVLFourthWidget = new QWidget(this);
    MainVLayout->addWidget(MVLFirstWidget);
    MainVLayout->addWidget(MVLSecondWidget);
    MainVLayout->addWidget(MVLThirdWidget);
    MainVLayout->addWidget(MVLFourthWidget);
    MVLFirstWidget->setGeometry(0, 0, width(), 30);
    MVLFirstWidget->setStyleSheet("background-color:gray;color:#FFFFFF;max-height: 30px;min-height: 30px;");
    MVLSecondWidget->setGeometry(0, MVLFirstWidget->height(), width(), 60);
    MVLSecondWidget->setStyleSheet("background-color:gray;color:#FFFFFF;max-height: 60px;min-height: 60px;");
    MVLThirdWidget->setGeometry(0, MVLFirstWidget->height() + MVLSecondWidget->height(), width(), height() - MVLFirstWidget->height() - MVLFirstWidget->height() -30);
    MVLThirdWidget->setStyleSheet("background-color:#1E1E1E;color:#FFFFFF;border:1px solid gray;");
    MVLFourthWidget->setGeometry(0, MVLFirstWidget->height() + MVLSecondWidget->height() + MVLThirdWidget->height(), width(), 30);
    MVLFourthWidget->setStyleSheet("background-color:#1E1E1E;color:#FFFFFF;max-height: 30px;min-height: 30px;border:1px solid gray;");
    this->setLayout(MainVLayout);
    FirstToolBar = new QToolBar(tr("工具栏1"), MVLFirstWidget);
    //FirstToolBar->setStyleSheet("QToolBar{border:1px solid gray;}");
    FirstToolBar->setGeometry(0, 0, MVLFirstWidget->width(), MVLFirstWidget->height());
    SecondToolBar = new QToolBar(tr("工具栏2"), MVLSecondWidget);
    //SecondToolBar->setStyleSheet("QToolBar{border:1px solid gray;}");
    SecondToolBar->setGeometry(0, 0, MVLSecondWidget->width(), MVLSecondWidget->height());
    InitToolBarAction();
}
void OperationWidget::InitToolBarAction()
{

    MapBagToolButton = new QToolButton(this);
    MapBagToolButton->setText("地图包");
    MapBagToolButton->setCheckable(true);
    FirstToolBar->addWidget(MapBagToolButton);
    LocalImportAction = new QAction(tr("&本地导入"), MVLSecondWidget);
    LocalImportAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/localbeifen.png"));
    ServerImportAction = new QAction(tr("&服务器导入"), MVLSecondWidget);
    ServerImportAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/localbeifen.png"));
    LoaclCopyAction = new QAction(tr("&新建地图"), MVLSecondWidget);
    LoaclCopyAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/localbeifen.png"));
    ServerCopyAction = new QAction(tr("&增量构建"), MVLSecondWidget);
    ServerCopyAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/fuwuqibeifen.png"));

    FunctionToolButton = new QToolButton(this);
    FunctionToolButton->setText("功能操作");
    FunctionToolButton->setCheckable(true);
    FirstToolBar->addWidget(FunctionToolButton);
    RobotAction = new QAction((tr("&机器人功能")), MVLSecondWidget);
    RobotAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/robot.png"));
    DrawerAction = new QAction((tr("&抽屉挂钩")), MVLSecondWidget);
    DrawerAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/choutiguagou.png"));
    CallAction = new QAction((tr("&呼叫电梯")), MVLSecondWidget);
    CallAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/dianti.png"));
    RouteAction = new QAction((tr("&行进路线")), MVLSecondWidget);
    RouteAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/route.png"));
    ContainerControlAction = new QAction((tr("&货柜控制")), MVLSecondWidget);
    ContainerControlAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/huoguikongzhi.png"));
    OrderAction = new QAction((tr("&订单")), MVLSecondWidget);
    OrderAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/order.png"));
    LogAction = new QAction((tr("&日志")), MVLSecondWidget);
    LogAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/log.png"));
    AbnormalPushAction = new QAction((tr("&异常推送")), MVLSecondWidget);
    AbnormalPushAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/log.png"));

    onMapBagClicked();
    connect(MapBagToolButton, SIGNAL(clicked()), this, SLOT(onMapBagClicked()));
    connect(FunctionToolButton, SIGNAL(clicked()), this, SLOT(onFunctionClicked()));
}
void OperationWidget::onMapBagClicked()
{
    MapBagToolButton->setChecked(true);
    FunctionToolButton->setChecked(false);
    SecondToolBar->clear();
    SecondToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    SecondToolBar->addAction(LocalImportAction);
    SecondToolBar->addAction(ServerImportAction);
    SecondToolBar->addAction(LoaclCopyAction);
    SecondToolBar->addAction(ServerCopyAction);
}

void OperationWidget::onFunctionClicked()
{

    MapBagToolButton->setChecked(false);
    FunctionToolButton->setChecked(true);
    SecondToolBar->clear();
    SecondToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    SecondToolBar->addAction(RobotAction);
    SecondToolBar->addAction(DrawerAction);
    SecondToolBar->addAction(CallAction);
    SecondToolBar->addAction(RouteAction);
    SecondToolBar->addAction(ContainerControlAction);
    SecondToolBar->addAction(OrderAction);
    SecondToolBar->addAction(LogAction);
    SecondToolBar->addAction(AbnormalPushAction);


}

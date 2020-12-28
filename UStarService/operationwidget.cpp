#include "operationwidget.h"
OperationWidget::OperationWidget(QWidget *parent):
    QWidget(parent)
{
    this->setGeometry(300, 30, 1200, 1000);
    this->setStyleSheet("background-color:#1E1E1E;");
    createView();
    InitToolBarAction();
    connect(LocalImportAction, &QAction::triggered, this, &OperationWidget::onLocalImportClicked);
    connect(MapBagToolButton, SIGNAL(clicked()), this, SLOT(onMapBagClicked()));
    connect(POIToolButton, SIGNAL(clicked()), this, SLOT(onPOIClicked()));
    connect(FunctionToolButton, SIGNAL(clicked()), this, SLOT(onFunctionClicked()));
    connect(OperationLogToolButton, SIGNAL(clicked()), this, SLOT(onOperationClicked()));
}
void OperationWidget::createView()
{
    MainVLayout = new QVBoxLayout(this);
    MainVLayout->setMargin(0);
    MainVLayout->setSpacing(0);
    this->setLayout(MainVLayout);
    MVLFirstWidget = new QWidget(this);
    MVLSecondWidget = new QWidget(this);
    MVLThirdWidget = new QWidget(this);
    MVLFourthWidget = new QWidget(this);
    MainVLayout->addWidget(MVLFirstWidget);
    MainVLayout->addWidget(MVLSecondWidget);
    MainVLayout->addWidget(MVLThirdWidget);
    MainVLayout->addWidget(MVLFourthWidget);
    MVLFirstWidget->setFixedHeight(height() * 0.03);
    MVLSecondWidget->setFixedHeight(height() * 0.06);
    MVLThirdWidget->setFixedHeight(height() * 0.88);
    MVLFourthWidget->setFixedHeight(height() * 0.03);
    MVLFirstWidget->setFixedWidth(width());
    MVLSecondWidget->setFixedWidth(width());
    MVLThirdWidget->setFixedWidth(width());
    MVLFourthWidget->setFixedWidth(width());
    MVLFirstWidget->setStyleSheet("QWidget{color:#FFFFFF;}");
    MVLSecondWidget->setStyleSheet("QWidget{color:#FFFFFF;}");
    MVLFourthWidget->setStyleSheet("QWidget{color:#FFFFFF;}");
    FirstToolBar = new QToolBar(tr("工具栏1"), MVLFirstWidget);
    FirstToolBar->resize(MVLFirstWidget->width(), MVLFirstWidget->height());
    SecondToolBar = new QToolBar(tr("工具栏2"), MVLSecondWidget);
    SecondToolBar->resize(MVLSecondWidget->width(), MVLSecondWidget->height());
}
void OperationWidget::InitToolBarAction()
{

    MapBagToolButton = new QToolButton(MVLFirstWidget);
    MapBagToolButton->setText("地图包");
    MapBagToolButton->setStyleSheet("QToolButoon{color:#FFFFFF;border: 1px solid gray;}");
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

    POIToolButton = new QToolButton(MVLFirstWidget);
    POIToolButton->setText("POI");
    POIToolButton->setCheckable(true);
    FirstToolBar->addWidget(POIToolButton);
    RoomPointAction = new QAction((tr("&房间点")), MVLSecondWidget);
    RoomPointAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/blue.png"));
    GoalPointAction = new QAction((tr("&目标点")), MVLSecondWidget);
    GoalPointAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/yellow.png"));
    DeceleratePointAction = new QAction((tr("&减速点")), MVLSecondWidget);
    DeceleratePointAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/red.png"));
    ChargePointAction = new QAction((tr("&充电点")), MVLSecondWidget);
    ChargePointAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/green.png"));
    LiftPointAction = new QAction((tr("&电梯点")), MVLSecondWidget);
    LiftPointAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/white.png"));


    FunctionToolButton = new QToolButton(MVLFirstWidget);
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

    OperationLogToolButton = new QToolButton();
    OperationLogToolButton->setText("操作记录");
    OperationLogToolButton->setCheckable(true);
    FirstToolBar->addWidget(OperationLogToolButton);

    onMapBagClicked();
    InitPaint();

}
void OperationWidget::InitPaint()
{
    qDebug()<<"----InitPaint()----";
    paint_ = new Paint(MVLThirdWidget);
    paint_->resize(MVLThirdWidget->width(), MVLThirdWidget->height());
    paint_->setPaintRect(MVLThirdWidget->width(), MVLThirdWidget->height());
}
void OperationWidget::onMapBagClicked()
{
    MapBagToolButton->setChecked(true);
    POIToolButton->setChecked(false);
    FunctionToolButton->setChecked(false);
    OperationLogToolButton->setChecked(false);
    SecondToolBar->clear();
    SecondToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    SecondToolBar->addAction(LocalImportAction);
    SecondToolBar->addAction(ServerImportAction);
    SecondToolBar->addAction(LoaclCopyAction);
    SecondToolBar->addAction(ServerCopyAction);

}
void OperationWidget::onPOIClicked()
{
    MapBagToolButton->setChecked(false);
    POIToolButton->setChecked(true);
    FunctionToolButton->setChecked(false);
    OperationLogToolButton->setChecked(false);
    SecondToolBar->clear();
    SecondToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ToolStoreyLable = new QLabel;
    ToolStoreyLable->setText("当前楼层:");
    StoreyComboBox = new QComboBox;
    StoreyComboBox->setStyleSheet("QComboBox { min-width: 24px; }");
    StoreyComboBox->addItem("1F");
    StoreyComboBox->addItem("2F");
    StoreyComboBox->addItem("3F");
    StoreyComboBox->addItem("4F");
    StoreyComboBox->addItem("5F");
    StoreyComboBox->addItem("6F");

    SecondToolBar->addWidget(ToolStoreyLable);
    SecondToolBar->addWidget(StoreyComboBox);
    SecondToolBar->addAction(RoomPointAction);
    SecondToolBar->addAction(GoalPointAction);
    SecondToolBar->addAction(DeceleratePointAction);
    SecondToolBar->addAction(ChargePointAction);
    SecondToolBar->addAction(LiftPointAction);
}

void OperationWidget::onFunctionClicked()
{

    MapBagToolButton->setChecked(false);
    POIToolButton->setChecked(false);
    FunctionToolButton->setChecked(true);
    OperationLogToolButton->setChecked(false);
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

void OperationWidget::onOperationClicked()
{
    MapBagToolButton->setChecked(false);
    POIToolButton->setChecked(false);
    FunctionToolButton->setChecked(false);
    OperationLogToolButton->setChecked(true);
    SecondToolBar->clear();
    UserNameLabel = new QLabel;
    QLabel *loginTimeLabel = new QLabel;
    loginTimeLabel->setText("登录时间: ");
    QLabel *endTimeLabel = new QLabel;
    endTimeLabel->setText("至：");
    UserNameLabel->setText("用户名:");
    UserNameLineEdit = new QLineEdit;
    UserNameLineEdit->setStyleSheet("QLineEdit { min-width: 120px; max-width: 120px}");
    UserNameLineEdit->setPlaceholderText(tr("请输入用户名!"));
    QDateTimeEdit *startDateEdit = new QDateTimeEdit(QDate::currentDate(), this);
    startDateEdit->setStyleSheet("QDateTimeEdit { min-width: 120px; max-width: 120px; min-height: 30};");
    startDateEdit->setMinimumDate(QDate::currentDate().addDays(-365));  // -365天
    startDateEdit->setMaximumDate(QDate::currentDate().addDays(365));  // +365天
    startDateEdit->setCalendarPopup(true);  // 日历弹出

    QDateTimeEdit *endDateEdit = new QDateTimeEdit(QDate::currentDate(), this);
    endDateEdit->setStyleSheet("QDateTimeEdit { min-width: 120px; max-width: 120px; min-height: 30};");
    endDateEdit->setMinimumDate(QDate::currentDate().addDays(-365));  // -365天
    endDateEdit->setMaximumDate(QDate::currentDate().addDays(365));  // +365天
    endDateEdit->setCalendarPopup(true);  // 日历弹出

    QToolButton *searchToolButton = new QToolButton;
    searchToolButton->setText(tr("查询"));
    searchToolButton->setStyleSheet("QToolButton {background-color:#FFFFC8; color: black};");
    SecondToolBar->addWidget(UserNameLabel);
    SecondToolBar->addWidget(UserNameLineEdit);
    SecondToolBar->addWidget(loginTimeLabel);
    SecondToolBar->addWidget(startDateEdit);
    SecondToolBar->addWidget(endTimeLabel);
    SecondToolBar->addWidget(endDateEdit);
    SecondToolBar->addWidget(searchToolButton);
}


void OperationWidget::onLocalImportClicked()
{
    QString str = QFileDialog::getOpenFileName(this,
                                               "Please choose an Image file",
                                               "",
                                               "Image Files(*.jpg *.png *.bmp *.pgm *.pbm);;All(*.*)");
    paint_->showImage(str);

}

#include "mappingwidget.h"
MappingWidget::MappingWidget(QWidget *parent):
    QWidget(parent)
{
    this->setGeometry(300, 30, 1200, 1000);
    this->setStyleSheet("background-color:#1E1E1E;");
    createView();
    InitToolBarAction();
    onMappingClicked();
    InitPaint();
    connect(MappingToolButton, SIGNAL(clicked()), this, SLOT(onMappingClicked()));
    connect(MapBagToolButton, SIGNAL(clicked()), this, SLOT(onMapBagClicked()));
    connect(POIToolButton, SIGNAL(clicked()), this, SLOT(onPOIClicked()));
    connect(OperationLogToolButton, SIGNAL(clicked()), this, SLOT(onOperationLogClicked()));
    connect(LocalImportAction, &QAction::triggered, this, &MappingWidget::onLocalImportClicked);
    connect(RoomPointAction, &QAction::triggered, this, &MappingWidget::onRoomPointClicked);
    connect(GoalPointAction, &QAction::triggered, this, &MappingWidget::onGoalPointClicked);
    connect(DeceleratePointAction, &QAction::triggered, this, &MappingWidget::onDeceleratePointClicked);
    connect(ChargePointAction, &QAction::triggered, this, &MappingWidget::onChargePointClicked);
    connect(LiftPointAction, &QAction::triggered, this, &MappingWidget::onLiftPointClicked);
    connect(OtherPointAction, &QAction::triggered, this, &MappingWidget::onOtherPointClicked);
}
void MappingWidget::createView()
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
void MappingWidget::InitToolBarAction()
{

    MappingToolButton = new QToolButton(MVLFirstWidget);
    MappingToolButton->setText("地图构建");
    MappingToolButton->setCheckable(true);
    FirstToolBar->addWidget(MappingToolButton);
    NewMapAction = new QAction((tr("&新建地图")), MVLSecondWidget);
    NewMapAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/newmap.png"));
    ModifyMappingAction = new QAction((tr("&增量构建")), MVLSecondWidget);
    ModifyMappingAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/zengliang.png"));
    DecorateAction = new QAction((tr("&修饰地图")), MVLSecondWidget);
    DecorateAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/xiushiditu.png"));
    VirtualWallAction = new QAction((tr("&虚拟墙设置")), MVLSecondWidget);
    VirtualWallAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/virtualWall.png"));

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
    OtherPointAction = new QAction((tr("&其他点")), MVLSecondWidget);
    OtherPointAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/yellow.png"));

    OperationLogToolButton = new QToolButton();
    OperationLogToolButton->setText("操作记录");
    OperationLogToolButton->setCheckable(true);
    FirstToolBar->addWidget(OperationLogToolButton);



}
void MappingWidget::InitPaint()
{
    qDebug()<<"----InitPaint()----";
    paint_ = new Paint(MVLThirdWidget);
    paint_->resize(MVLThirdWidget->width(), MVLThirdWidget->height());
    paint_->setPaintRect(MVLThirdWidget->width(), MVLThirdWidget->height());
}
void MappingWidget::onMappingClicked()
{
    MappingToolButton->setChecked(true);
    MapBagToolButton->setChecked(false);
    POIToolButton->setChecked(false);
    OperationLogToolButton->setChecked(false);
    SecondToolBar->clear();
    SecondToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    SecondToolBar->addAction(NewMapAction);
    SecondToolBar->addAction(ModifyMappingAction);
    SecondToolBar->addAction(DecorateAction);
    SecondToolBar->addAction(VirtualWallAction);

}
void MappingWidget::onMapBagClicked()
{
    MappingToolButton->setChecked(false);
    MapBagToolButton->setChecked(true);
    POIToolButton->setChecked(false);
    OperationLogToolButton->setChecked(false);
    SecondToolBar->clear();
    SecondToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    SecondToolBar->addAction(LocalImportAction);
    SecondToolBar->addAction(ServerImportAction);
    SecondToolBar->addAction(LoaclCopyAction);
    SecondToolBar->addAction(ServerCopyAction);

}
void MappingWidget::onPOIClicked()
{
    MappingToolButton->setChecked(false);
    MapBagToolButton->setChecked(false);
    POIToolButton->setChecked(true);
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
    SecondToolBar->addAction(OtherPointAction);
}
void MappingWidget::onOperationLogClicked()
{
    MappingToolButton->setChecked(false);
    MapBagToolButton->setChecked(false);
    POIToolButton->setChecked(false);
    OperationLogToolButton->setChecked(true);
    SecondToolBar->clear();

    UserNameLabel = new QLabel;
    UserNameLabel->setText("用户名:");
    UserNameLineEdit = new QLineEdit;
    UserNameLineEdit->setStyleSheet("QLineEdit { min-width: 120px; max-width: 120px}");
    UserNameLineEdit->setPlaceholderText(tr("请输入用户名!"));
    StartTimeLabel = new QLabel;
    StartTimeLabel->setText("登录时间: ");
    EndTimeLabel = new QLabel;
    EndTimeLabel->setText("至：");

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

    SearchToolButton = new QToolButton;
    SearchToolButton->setText(tr("查询"));
    SearchToolButton->setStyleSheet("QToolButton {background-color:#FFFFC8; color: black};");
    SecondToolBar->addWidget(UserNameLabel);
    SecondToolBar->addWidget(UserNameLineEdit);
    SecondToolBar->addWidget(StartTimeLabel);
    SecondToolBar->addWidget(startDateEdit);
    SecondToolBar->addWidget(EndTimeLabel);
    SecondToolBar->addWidget(endDateEdit);
    SecondToolBar->addWidget(SearchToolButton);
}
void MappingWidget::onLocalImportClicked()
{
    QString str = QFileDialog::getOpenFileName(this,
                                               "Please choose an Image file",
                                               "",
                                               "Image Files(*.jpg *.png *.bmp *.pgm *.pbm);;All(*.*)");
    paint_->showImage(str);

}
void MappingWidget::onRoomPointClicked()
{
    button_style_ = "blue";
    paint_->setPOIPointStyle(button_style_);
    qDebug()<<button_style_;
}

void MappingWidget::onGoalPointClicked()
{
    button_style_ = "yellow";
    paint_->setPOIPointStyle(button_style_);
    qDebug()<<button_style_;
}
void MappingWidget::onDeceleratePointClicked()
{
    button_style_ = "red";
    paint_->setPOIPointStyle(button_style_);
    qDebug()<<button_style_;
}
void MappingWidget::onChargePointClicked()
{
    button_style_ = "green";
    paint_->setPOIPointStyle(button_style_);
    qDebug()<<button_style_;
}
void MappingWidget::onLiftPointClicked()
{
    button_style_ = "gray";
    paint_->setPOIPointStyle(button_style_);
    qDebug()<<button_style_;
}
void MappingWidget::onOtherPointClicked()
{
    button_style_ = "goldyellow";
    paint_->setPOIPointStyle(button_style_);
    qDebug()<<button_style_;
}

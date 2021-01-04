#include "mappingwidget.h"
MappingWidget::MappingWidget(QWidget *parent):
    QWidget(parent)
{
    this->setGeometry(300, 30, 1200, 1000);
    this->setStyleSheet("background-color:#1E1E1E;");
    this->setWindowTitle("优智达建图");
    createView();
    InitToolBarAction();
    onMappingClicked();
    InitPaint();
    InitVideoDockWidget();
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
    connect(VirtualWallAction, &QAction::triggered, this, &MappingWidget::onVirtualWallClicked);
    connect(IPChangeAction,  &QAction::triggered, this, &MappingWidget::onIPChangeClicked);
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

    OperationLogToolButton = new QToolButton(MVLFirstWidget);
    OperationLogToolButton->setText("操作记录");
    OperationLogToolButton->setCheckable(true);
    FirstToolBar->addWidget(OperationLogToolButton);

    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    FirstToolBar->addWidget(spacer);

    IPChangeAction = new QAction(MVLFirstWidget);
    IPChangeAction->setText("  切换IP");
    QFont font1("Microsoft YaHei", 10, 5);
    font1.setUnderline(true);
    IPChangeAction->setFont(font1);

    //IPChangeAction->setAlignment(Qt::AlignCenter);
    FirstToolBar->addAction(IPChangeAction);

    NowTimeIPLabel = new QLabel(MVLFirstWidget);
    NowTimeIPLabel->setText("  当前IP：");
    QFont font2("Microsoft YaHei", 10, 5);
    NowTimeIPLabel->setFont(font2);
    NowTimeIPLabel->setAlignment(Qt::AlignCenter);
    FirstToolBar->addWidget(NowTimeIPLabel);

    NowTimeIPValueLabel = new QLabel(MVLFirstWidget);
    NowTimeIPValueLabel->setText("  192.168.14.133");
    QFont font3("Microsoft YaHei", 10, 5);
    NowTimeIPValueLabel->setFont(font3);
    NowTimeIPValueLabel->setAlignment(Qt::AlignCenter);
    FirstToolBar->addWidget(NowTimeIPValueLabel);


    AddressLabel = new QLabel(MVLFirstWidget);
    AddressLabel->setText("  苏州 苏州湾艾美酒店");
    QFont font4("Microsoft YaHei", 10, 10);
    AddressLabel->setFont(font4);
    AddressLabel->setAlignment(Qt::AlignCenter);
    FirstToolBar->addWidget(AddressLabel);


}
void MappingWidget::InitPaint()
{
    qDebug()<<"----InitPaint()----";
    paint_ = new Paint(MVLThirdWidget);
    paint_->resize(MVLThirdWidget->width(), MVLThirdWidget->height());
    paint_->setPaintRect(MVLThirdWidget->width(), MVLThirdWidget->height());
}
void MappingWidget::InitVideoDockWidget()
{
    qDebug()<<"----InitVideoDockWidget()----";
//    VirtualWallDockWindow vwdw(MVLThirdWidget);
    QDockWidget *vdw;
    vdw = new VideoDockWidget(MVLThirdWidget);
    vdw->setGeometry(MVLThirdWidget->width() - 205, 30, 200, 270);
    vdw->setStyleSheet("background-color:#1F1F1F;");
    vdw->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable);//设置停靠窗口特性，可移动，可关闭
    vdw->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);//设置可停靠区域为主窗口左边和右边
    vdw->show();
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
void MappingWidget::onVirtualWallClicked()
{
    qDebug()<<"----onVirtualWallClicked()----";
//    VirtualWallDockWindow vwdw(MVLThirdWidget);
    QDockWidget *vwdw;
    vwdw = new VirtualWallDockWidget(MVLThirdWidget, paint_);
    vwdw->setGeometry(43, 30, 300, 200);
    vwdw->setStyleSheet("background-color:#1F1F1F;");
    vwdw->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable);//设置停靠窗口特性，可移动，可关闭
    vwdw->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);//设置可停靠区域为主窗口左边和右边
    vwdw->show();
}

void MappingWidget::onIPChangeClicked()
{
    qDebug()<<"robot"<<endl;

    RobotWindow *robot = new RobotWindow();
    robot->show();
//    cv::Mat mat = robot->image_;
//    qDebug()<<robot->image_.channels();
//    cv::Mat Rgb;
//    QImage Img;
//    if (mat.channels() == 3)//RGB Img
//    {
//        cv::cvtColor(mat, Rgb, CV_BGR2RGB);//颜色空间转换
//        Img = QImage((const uchar*)(Rgb.data), Rgb.cols, Rgb.rows, Rgb.cols * Rgb.channels(), QImage::Format_RGB888);
//    }
//    else//Gray Img
//    {
//        Img = QImage((const uchar*)(mat.data), mat.cols, mat.rows, mat.cols*mat.channels(), QImage::Format_Indexed8);
//    }
//    MvLabel->setPixmap(QPixmap::fromImage(Img));
    //qDebug()<<Img.byteCount();
    //SplitterTopWidget->update();
}

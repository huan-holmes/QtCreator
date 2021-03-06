
#include "mianwindow.h"

MainWindow::MainWindow(QMainWindow *parent):
    QMainWindow(parent),

    clear_flag_(false),
    line_flag_(false),
    virtual_wall_flag_(0),
    virtual_wall_x1_(0),
    virtual_wall_y1_(0),
    virtual_wall_x2_(0),
    virtual_wall_y2_(0),
    button_style_(""),
    Alloffset(0,0),
    choose_(MAPSET)
{
    this->setGeometry(300, 30, 1500, 1200);
    this->setStyleSheet("background-color:#1E1E1E;");
    //PaintRect = QRect(4,45,width()/3*2 - 20 + 6, 1 + 5 + height() - 40 - this->statusBar()->height() - this->menuBar()->height() - 10 - 140);
    PaintRect = QRect(4,95,width()/3*2 - 20 + 6, 1 + 5 + height() - 40 - this->statusBar()->height() - this->menuBar()->height() - 10 - 140 - 50);
    MainVLayout = new QVBoxLayout(this);
    MainSplitter = new QSplitter(Qt::Vertical, this);
    TopWidget = new QWidget(this);

    SecondWidget = new QWidget(this);

    MainVLayout->addWidget(TopWidget);
    MainVLayout->addWidget(SecondWidget);
    MainVLayout->addWidget(MainSplitter);
    SplitterTopWidget = new QWidget(this);
    SplitterBottomWidget = new QWidget(this);
    MainSplitter->addWidget(SplitterTopWidget);
    MainSplitter->addWidget(SplitterBottomWidget);
    MainSplitter->setStretchFactor(0, 6);
    MainSplitter->setStretchFactor(1, 4);
    TopWidget->setGeometry(0, 0, width(), 30);
    TopWidget->setStyleSheet("background-color:#1E1E1E;color:#FFFFFF");
    SecondWidget->setGeometry(0, TopWidget->height(), width(), 60);
    SecondWidget->setStyleSheet("background-color:#1E1E1E;color:#FFFFFF");

    //MainSplitter->setGeometry(width() / 3 * 2 - 8, TopWidget->height() + 10 - 7, width() / 3 + 5, 4 + 5 + height() - TopWidget->height() - this->statusBar()->height() - this->menuBar()->height() - 10 - 140);
    MainSplitter->setGeometry(width() / 3 * 2 - 8, TopWidget->height() + 10 - 7 + 60, width() / 3 + 5, 4 + 5 + height() - TopWidget->height() - this->statusBar()->height() - this->menuBar()->height() - 10 - 140 - 60);
    MainSplitter->setStyleSheet("background-color:gray;");

    this->setLayout(MainVLayout);
    ratio_= 1.0;             //初始化图片缩放比例
    action_ = MainWindow::None;
    MainWindowMenuBar = this->menuBar(); //1.创建菜单栏
    //MainWindowToolBar = addToolBar(tr("工具栏"));
    MainWindowToolBar = new QToolBar(tr("工具栏"), TopWidget); //2.创建工具栏
    MainWindowToolBar->setGeometry(0, 0, TopWidget->width(), TopWidget->height());
    SecondToolBar = new QToolBar(tr("工具栏2"), SecondWidget); //2.创建工具栏
    SecondToolBar->setGeometry(0, 0, SecondWidget->width(), SecondWidget->height());
    SecondToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    MainWindowStatusBar = this->statusBar();    //3.状态栏

    MainWindowToolBar->setStyleSheet("background-color:#1E1E1E;");
    SecondToolBar->setStyleSheet("background-color:#1E1E1E;");
    MainWindowStatusBar->setStyleSheet("background-color:#1E1E1E;");

    FileMenu = new QMenu("文件(&F)");
    EditMenu = new QMenu("编辑(&E)");
    ToolMenu = new QMenu("工具(&T)");
    HelpMenu = new QMenu("帮助(&H)");
    CameraMenu = new QMenu("摄像头(&C)");

    StateLabel = new QLabel("100%",this);

    FileCreateAction = new QAction("打开(&O)", this);
    FileCreateAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/remap.png"));
    //fileCreateAction->setIcon(QIcon(":/ReplicationTool/png/open.png"));
    FileSaveAction = new QAction("保存(&S)",this);
    BaseAction = new QAction("&还原", this);
    BigAction = new QAction("&放大", this);
    LittleAction = new QAction("&缩小", this);
    RightAction = new QAction("&向右", this);
    LeftAction = new QAction("&向左", this);
    UpAction = new QAction("&向上", this);
    DownAction = new QAction("&向下", this);

    OpenCameraAction = new QAction(tr("&打开摄像头"), this);
    CloseCameraAction = new QAction(tr("&关闭摄像头"), this);
    TakeCameraPictureAction = new QAction(tr("捕获"), this);

    VirtualWallAction = new QAction(tr("&虚拟墙"), this);
    ClearAction = new QAction(tr("&清除"), this);
    LineAction = new QAction(tr("&绘图"), this);
    SlamAction = new QAction(tr("&SLAM"), this);
    ChooseAction = new QAction(tr("&选择机器人"), this);
    RedToolButton = new QToolButton;
    GreenToolButton = new QToolButton;
    BlueToolButton = new QToolButton;


    MainWindowMenuBar->addMenu(FileMenu);
    MainWindowMenuBar->addSeparator();
    FileMenu->addAction(FileCreateAction);
    FileCreateAction->setShortcut(Qt::CTRL | Qt::Key_O);
    FileMenu->addAction(FileSaveAction);
    FileSaveAction->setShortcut(Qt::CTRL | Qt::Key_S);

    MainWindowMenuBar->addMenu(EditMenu);
    MainWindowMenuBar->addSeparator();
    EditMenu->addAction(BaseAction);
    EditMenu->addAction(BigAction);
    EditMenu->addAction(LittleAction);
    EditMenu->addAction(RightAction);
    EditMenu->addAction(LeftAction);
    EditMenu->addAction(UpAction);
    EditMenu->addAction(DownAction);

    MainWindowMenuBar->addMenu(ToolMenu);
    MainWindowMenuBar->addSeparator();

    MainWindowMenuBar->addMenu(HelpMenu);
    MainWindowMenuBar->addSeparator();

    MainWindowMenuBar->addMenu(CameraMenu);
    MainWindowMenuBar->addSeparator();
    CameraMenu->addAction(OpenCameraAction);
    CameraMenu->addAction(CloseCameraAction);
    CameraMenu->addAction(TakeCameraPictureAction);


    InitSecondToolBarAction();
//    MainWindowToolBar->addAction(FileCreateAction);
//    MainWindowToolBar->addSeparator();
//    MainWindowToolBar->addAction(SlamAction);
//    MainWindowToolBar->addSeparator();
//    MainWindowToolBar->addAction(ClearAction);
//    MainWindowToolBar->addSeparator();
//    MainWindowToolBar->addAction(VirtualWallAction);
//    MainWindowToolBar->addSeparator();
//    MainWindowToolBar->addAction(LineAction);
//    MainWindowToolBar->addSeparator();
//    MainWindowToolBar->addAction(ChooseAction);
//    MainWindowToolBar->addSeparator();
//    MainWindowToolBar->addWidget(RedToolButton);
//    MainWindowToolBar->addSeparator();
//    MainWindowToolBar->addWidget(GreenToolButton);
//    MainWindowToolBar->addSeparator();
//    MainWindowToolBar->addWidget(BlueToolButton);
//    RedToolButton->setStyleSheet("QToolButton{background-color:rgba(255,0,0,200);width:15px;height:15px}");
//    GreenToolButton->setStyleSheet("QToolButton{background-color:rgba(0,255,0,200);width:15px;height:15px}}");
//    BlueToolButton->setStyleSheet("QToolButton{background-color:rgba(0,0,255,200);width:15px;height:15px}");
    MainWindowStatusBar->addWidget(StateLabel);
    StateLabel->setStyleSheet("background-color: rgba(255, 255, 224, 0%);border:0px;");
    timer_ = new QTimer(this);
    MvLabel = new QLabel(SplitterTopWidget);
    PicLabel = new QLabel(SplitterBottomWidget);
    MvLabel->resize(MainSplitter->width(), MainSplitter->height() * 0.6);
    MvLabel->setStyleSheet("background-color:gray;");
    PicLabel->resize(MainSplitter->width(), MainSplitter->height() * 0.4);
    PicLabel->setStyleSheet("background-color: #1E1E1E");
    //connect(timer_, SIGNAL(timeout()), this, SLOT(readCameraFrame());
    //connect(OpenCameraAction, &QAction::triggered, this, &MainWindow::onOpenCameraClicked);
    //connect(CloseCameraAction, &QAction::triggered, this, &MainWindow::onCloseCameraClicked);
    //connect(TakeCameraPictureAction, &QAction::triggered, this, &MainWindow::onTakePictureClicked);


    //QWidget *qw = new QWidget;
    //qw->resize(300, 200);

//    QDockWidget *dw1 = new QDockWidget("停靠窗口1", this);//构建停靠窗口，指定父类

//    dw1->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable);//设置停靠窗口特性，可移动，可关闭

//    dw1->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);//设置可停靠区域为主窗口左边和右边

//    //QTextEdit *dte = new QTextEdit("DockWindow First");
//    //dw1->setWidget(dte);
//    addDockWidget(Qt::RightDockWidgetArea,dw1);


    connect(FileCreateAction, &QAction::triggered, this, &MainWindow::onOpenClicked);
    connect(ClearAction, &QAction::triggered, this, &MainWindow::onClearClicked);
    connect(VirtualWallAction, &QAction::triggered, this, &MainWindow::onVirtualWallClicked);
    connect(LineAction, &QAction::triggered, this, &MainWindow::onLineClicked);
    connect(ChooseAction, &QAction::triggered, this, &MainWindow::onChooseRobotClicked);
    connect(BaseAction, &QAction::triggered, this, &MainWindow::onResetClicked);
    connect(BigAction, &QAction::triggered, this, &MainWindow::onBigClicked);
    connect(LittleAction, &QAction::triggered, this, &MainWindow::onLittleClicked);
    connect(RightAction, &QAction::triggered, this, &MainWindow::OnRightClicked);
    connect(LeftAction, &QAction::triggered, this, &MainWindow::OnLeftClicked);
    connect(UpAction, &QAction::triggered, this, &MainWindow::onUpClicked);
    connect(DownAction, &QAction::triggered, this, &MainWindow::onDownClicked);
    connect(RedToolButton, SIGNAL(clicked()), this, SLOT(onRedClicked()));
    connect(GreenToolButton, SIGNAL(clicked()), this, SLOT(onGreenClicked()));
    connect(BlueToolButton, SIGNAL(clicked()), this, SLOT(onBlueClicked()));
}

void MainWindow::InitSecondToolBarAction()
{
    QLabel *ToolLogLable = new QLabel;
    QImage *img=new QImage; //新建一个image对象
    img->load("/home/boocax/QtCreator/log/Icon/logo.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
    ToolLogLable->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
    MainWindowToolBar->addWidget(ToolLogLable);
    QToolButton *MapSetToolButton = new QToolButton;
    QToolButton *MapBagToolButton = new QToolButton;
    QToolButton *FunctionToolButton = new QToolButton;
    QToolButton *POIToolButton = new QToolButton;
    QToolButton *OperationLogToolButton = new QToolButton;
    MapSetToolButton->setText("地图构建");
    MapSetToolButton->setCheckable(true);
    MapBagToolButton->setText("地图包");
    MapBagToolButton->setCheckable(true);
    FunctionToolButton->setText("功能操作");
    FunctionToolButton->setCheckable(true);
    POIToolButton->setText("POI");
    POIToolButton->setCheckable(true);
    OperationLogToolButton->setText("操作记录");
    OperationLogToolButton->setCheckable(true);
    MainWindowToolBar->addWidget(MapSetToolButton);
    MainWindowToolBar->addWidget(MapBagToolButton);
    MainWindowToolBar->addWidget(FunctionToolButton);
    MainWindowToolBar->addWidget(POIToolButton);
    MainWindowToolBar->addWidget(OperationLogToolButton);
    NewMapAction = new QAction((tr("&新建地图")), SecondWidget);
    NewMapAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/newmap.png"));
    AddMapAction = new QAction((tr("&增量构建")), SecondWidget);
    AddMapAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/zengliang.png"));
    DecorateAction = new QAction((tr("&修饰地图")), SecondWidget);
    DecorateAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/xiushiditu.png"));
    VirtualWallSetAction = new QAction((tr("&虚拟墙设置")), SecondWidget);
    VirtualWallSetAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/virtualWall.png"));
    LoaclCopyAction = new QAction((tr("&新建地图")), SecondWidget);
    LoaclCopyAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/localbeifen.png"));
    ServerCopyAction = new QAction((tr("&增量构建")), SecondWidget);
    ServerCopyAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/fuwuqibeifen.png"));
    RobotAction = new QAction((tr("&机器人功能")), SecondWidget);
    RobotAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/robot.png"));
    DrawerAction = new QAction((tr("&抽屉挂钩")), SecondWidget);
    DrawerAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/choutiguagou.png"));
    CallAction = new QAction((tr("&呼叫电梯")), SecondWidget);
    CallAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/dianti.png"));
    RouteAction = new QAction((tr("&行进路线")), SecondWidget);
    RouteAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/route.png"));
    ContainerControlAction = new QAction((tr("&货柜控制")), SecondWidget);
    ContainerControlAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/huoguikongzhi.png"));
    OrderAction = new QAction((tr("&订单")), SecondWidget);
    OrderAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/order.png"));
    LogAction = new QAction((tr("&日志")), SecondWidget);
    LogAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/log.png"));

    RoomPointAction = new QAction((tr("&房间点")), SecondWidget);
    RoomPointAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/blue.png"));
    GoalPointAction = new QAction((tr("&目标点")), SecondWidget);
    GoalPointAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/yellow.png"));
    DeceleratePointAction = new QAction((tr("&减速点")), SecondWidget);
    DeceleratePointAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/red.png"));
    ChargePointAction = new QAction((tr("&充电点")), SecondWidget);
    ChargePointAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/green.png"));
    LiftPointAction = new QAction((tr("&电梯点")), SecondWidget);
    LiftPointAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/white.png"));
    SecondToolBar->addAction(NewMapAction);
    SecondToolBar->addAction(AddMapAction);
    SecondToolBar->addAction(DecorateAction);
    SecondToolBar->addAction(VirtualWallSetAction);
    connect(MapSetToolButton, SIGNAL(clicked()), this, SLOT(onMapSetClicked()));
    connect(MapBagToolButton, SIGNAL(clicked()), this, SLOT(onMapBagClicked()));
    connect(FunctionToolButton, SIGNAL(clicked()), this, SLOT(onFunctionClicked()));
    connect(POIToolButton, SIGNAL(clicked()), this, SLOT(onPOIClicked()));
    connect(OperationLogToolButton, SIGNAL(clicked()), this, SLOT(onOperationClicked()));
}

bool MainWindow::event(QEvent * event)
{
    //return true;
    static bool press=false;
    static QPoint PreDot;

    if(event->type() == QEvent::MouseButtonPress )
    {
           QMouseEvent *mouse = dynamic_cast<QMouseEvent* >(event);

           //判断鼠标是否是左键按下,且鼠标位置是否在绘画区域
           if(mouse->button()==Qt::LeftButton &&PaintRect.contains(mouse->pos()))
           {
               press=true;
               QApplication::setOverrideCursor(Qt::OpenHandCursor); //设置鼠标样式
               if(clear_flag_)
               {
                   QApplication::setOverrideCursor(Qt::CrossCursor);
               }

               if(line_flag_)
               {
                   QApplication::setOverrideCursor(Qt::SizeBDiagCursor);
               }
               if(button_style_ != "")
               {
                   int x = (mouse->x() - PaintRect.x() - (PaintRect.width()/2-ratio_*pix_width_/2)) / ratio_ - Alloffset.x() / ratio_;
                   int y = (mouse->y() - PaintRect.y() - (PaintRect.height()/2-ratio_*pix_height_/2)) / ratio_ - Alloffset.y() / ratio_;
                   addPointOfInterest(x, y);
                   button_style_ = "";
               }

               PreDot = mouse->pos();
           }
           if(mouse->button()==Qt::RightButton &&PaintRect.contains(mouse->pos()))
           {
               clear_flag_ = false;
               line_flag_ = false;
               virtual_wall_flag_ = 0;
               virtual_wall_x1_ = 0;
               virtual_wall_y1_ = 0;
               virtual_wall_x2_ = 0;
               virtual_wall_y2_ = 0;
               QApplication::setOverrideCursor(Qt::ArrowCursor);

           }

    }
    else if(event->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent *mouse = dynamic_cast<QMouseEvent* >(event);
        //判断鼠标是否是左键释放,且之前是在绘画区域
        if(mouse->button()==Qt::LeftButton && press )
        {
            QApplication::setOverrideCursor(Qt::ArrowCursor); //改回鼠标样式
            press=false;
            clear_flag_ = false;
            line_flag_ = false;
            if(virtual_wall_flag_ == 1)
            {
                virtual_wall_x1_ = (mouse->x() - PaintRect.x() - (PaintRect.width()/2-ratio_*pix_width_/2)) / ratio_ - Alloffset.x() / ratio_;
                virtual_wall_y1_ = (mouse->y() - PaintRect.y() - (PaintRect.height()/2-ratio_*pix_height_/2)) / ratio_ - Alloffset.y() / ratio_;
                virtual_wall_flag_ = 2;
                QApplication::setOverrideCursor(Qt::PointingHandCursor);
                if(virtual_wall_x2_ != 0 && virtual_wall_y2_ != 0)
                {
                    GridLine grid_line(virtual_wall_x2_, virtual_wall_y2_, virtual_wall_x1_, virtual_wall_y1_);
                    drawLine(grid_line.line_xs_, grid_line.line_ys_);
                }
            }
            else
            {
                if(virtual_wall_flag_ == 2)
                {
                    virtual_wall_x2_ = (mouse->x()-PaintRect.x() - (PaintRect.width()/2-ratio_*pix_width_/2))/ratio_ - Alloffset.x() / ratio_;
                    virtual_wall_y2_ = (mouse->y()-PaintRect.y() - (PaintRect.height()/2-ratio_*pix_height_/2))/ratio_ - Alloffset.y() / ratio_;
                    GridLine grid_line(virtual_wall_x1_, virtual_wall_y1_, virtual_wall_x2_, virtual_wall_y2_);
                    drawLine(grid_line.line_xs_, grid_line.line_ys_);
                    virtual_wall_flag_ = 1;
                    QApplication::setOverrideCursor(Qt::PointingHandCursor);
                }

            }
        }
    }

     if(event->type() == QEvent::MouseMove)              //移动图片
     {
          if(press)
         {
            QMouseEvent *mouse = dynamic_cast<QMouseEvent* >(event);

            if(clear_flag_ or line_flag_)
            {
                if(clear_flag_)
                {
                    for(int i=-2; i < 3; i++)
                    {
                        for(int j = -2; j < 3; j++)
                        {
                            Image.setPixel((mouse->x()-PaintRect.x() - (PaintRect.width()/2-ratio_*pix_width_/2))/ratio_ - Alloffset.x() / ratio_+i, (mouse->y()-PaintRect.y()-(PaintRect.height()/2-ratio_*pix_height_/2))/ratio_ - Alloffset.y() / ratio_+j, qRgb(255, 255, 255));
                        }

                    }

                    Pixmap = Pixmap.fromImage(Image);
                    action_ = MainWindow::Reset;
                }
                else
                {
                    for(int i=-1; i < 1; i++)
                    {
                        for(int j = -1; j < 1; j++)
                        {
                            Image.setPixel((mouse->x()-PaintRect.x() - (PaintRect.width()/2-ratio_*pix_width_/2))/ratio_ - Alloffset.x() / ratio_ +i, (mouse->y()-PaintRect.y()-(PaintRect.height()/2-ratio_*pix_height_/2))/ratio_ -Alloffset.y() / ratio_+ j, qRgb(0, 0, 0));
                        }

                    }

                    Pixmap = Pixmap.fromImage(Image);
                    action_ = MainWindow::Reset;
                }
            }
            else
            {
                offset.setX(mouse->x() - PreDot.x());
                offset.setY(mouse->y() - PreDot.y());
                PreDot = mouse->pos();
                action_ = MainWindow::Move;
            }
            this->update();
         }
     }
    return QWidget::event(event);
}

void MainWindow::wheelEvent(QWheelEvent* event)     //鼠标滑轮事件
{
 if (event->delta()>0) {      //上滑,缩小

    action_=MainWindow::Shrink;
    this->update();
 } else {                    //下滑,放大
     action_=MainWindow::Amplification;
     this->update();
 }

 event->accept();
}



void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter PaintRecter(this);

    PaintRecter.setRenderHints(QPainter::SmoothPixmapTransform|QPainter::Antialiasing|QPainter::TextAntialiasing);
    PaintRecter.drawRect(PaintRect.x()-1,PaintRect.y()-1,PaintRect.width()+1,PaintRect.height()+1); //画框
    if(Image.isNull())
    {
     return;
    }

    int NowW = ratio_ *pix_width_;
    int NowH = ratio_ *pix_height_;

    if(action_==MainWindow::Shrink)           //缩小
    {
          ratio_+=0.05*ratio_;
        if(ratio_<0.018)
          ratio_ = 0.01;

        /*显示比例*/
        QString str;
        str.sprintf("%.0f%",ratio_*100);
        StateLabel->setText(str) ;
        qDebug()<<"放大:"<<ratio_;
    }
    else  if(action_==MainWindow::Amplification)           //放大
    {

         ratio_-=0.05*ratio_;
       if(ratio_>4.5)
         ratio_ = 5.000;

        /*显示比例*/
        QString str;
        str.sprintf("%.0f%",ratio_*100);
        StateLabel->setText(str);
        qDebug()<<"缩小:"<<ratio_;
    }


    if(action_==MainWindow::Amplification || action_==MainWindow::Shrink || action_==MainWindow::Reset)      //更新图片
    {
      NowW = ratio_ *pix_width_;
      NowH = ratio_ *pix_height_;


      CrtPixmap= Pixmap.scaled(NowW, NowH,Qt::KeepAspectRatio,Qt::SmoothTransformation); //重新装载

      action_=MainWindow::None;
    }

    if(action_==MainWindow::Move)                    //移动
    {
        int offsetx=Alloffset.x()+offset.x();
        Alloffset.setX(offsetx);

        int offsety=Alloffset.y()+offset.y();
        Alloffset.setY(offsety);
        action_=MainWindow::None;
    }

    if(abs(Alloffset.x())>=(PaintRect.width()/2 + NowW/2 -10))    //限制X偏移值
    {
        if(Alloffset.x()>0)
            Alloffset.setX(PaintRect.width()/2 + NowW/2 -10);
        else
         Alloffset.setX(-PaintRect.width()/2 + -NowW/2 +10);

    }
    if(abs(Alloffset.y())>=(PaintRect.height()/2 + NowH/2 -10))    //限制Y偏移值
    {
        if(Alloffset.y()>0)
            Alloffset.setY(PaintRect.height()/2 + NowH/2 -10);
        else
         Alloffset.setY(-PaintRect.height()/2 + -NowH/2 +10);

    }

    int x = PaintRect.width()/2 + Alloffset.x() -NowW/2;
    if(x<0)
        x=0;

    int y = PaintRect.height()/2 + Alloffset.y() -NowH/2;
    if(y<0)
        y=0;

    int  sx = NowW/2 - PaintRect.width()/2 - Alloffset.x();
    if(sx<0)
        sx=0;

    int  sy = NowH/2 - PaintRect.height()/2 - Alloffset.y();
    if(sy<0)
        sy=0;

    int w =(NowW - sx)>PaintRect.width()? PaintRect.width() : (NowW - sx);
    if(w>(PaintRect.width()-x))
        w = PaintRect.width()-x;

    int h =(NowH - sy)>PaintRect.height()? PaintRect.height() : (NowH - sy);
    if(h>(PaintRect.height()-y))
        h = PaintRect.height()-y;



    PaintRecter.drawTiledPixmap(x+PaintRect.x(),y+PaintRect.y(),w,h,CrtPixmap,sx,sy);             //绘画图形



}

void  MainWindow::onLittleClicked()
{
  action_=MainWindow::Amplification;
  this->update();
}

void MainWindow::onClearClicked()
{
  resetVirtualWallState();
  action_=MainWindow::Clear;
  if(clear_flag_)
  {
    clear_flag_ = false;
  }
  else
  {
    QApplication::setOverrideCursor(Qt::CrossCursor);
    clear_flag_ = true;
  }
  this->update();
}
void MainWindow::onLineClicked()
{
    resetVirtualWallState();
    action_=MainWindow::Line;
    if(line_flag_)
    {
        line_flag_ = false;
    }
    else
    {
        QApplication::setOverrideCursor(Qt::SizeBDiagCursor);
        line_flag_ = true;

    }
    this->update();
}
void MainWindow::onVirtualWallClicked()
{
    virtual_wall_x1_ = 0;
    virtual_wall_y1_ = 0;
    virtual_wall_x2_ = 0;
    virtual_wall_y2_ = 0;
    action_=MainWindow::VirtualWall;
    if (virtual_wall_flag_ == 0)
    {
        virtual_wall_flag_ = 1;
        QApplication::setOverrideCursor(Qt::PointingHandCursor);
    }
    else
    {
        virtual_wall_flag_ = 0;
        QApplication::setOverrideCursor(Qt::ArrowCursor);
    }

    this->update();
}
void MainWindow::resetVirtualWallState(){
    virtual_wall_x1_ = 0;
    virtual_wall_y1_ = 0;
    virtual_wall_x2_ = 0;
    virtual_wall_y2_ = 0;
    virtual_wall_flag_ = 0;
    QApplication::setOverrideCursor(Qt::ArrowCursor);
}

void MainWindow::drawLine(std::vector<int> line_xs, std::vector<int> line_ys)
{
    for (int i = 0; i < line_xs.size(); i++)
    {
        for(int j = -1; j <= 1; j++)
        {
            Image.setPixel(line_xs[i+j], line_ys[i], qRgb(0, 0, 0));
        }
    }
    Pixmap = Pixmap.fromImage(Image);
    action_ = MainWindow::Reset;
    this->update();
}

void MainWindow::onRedClicked()
{
    button_style_ = "red";
    qDebug()<<button_style_;
}

void MainWindow::onGreenClicked()
{
    button_style_ = "green";
    qDebug()<<button_style_;
}

void MainWindow::onBlueClicked()
{
    button_style_ = "blue";
    qDebug()<<button_style_;
}

void MainWindow::addPointOfInterest(int x, int y)
{
    qDebug()<<Image.depth();
    QRgb qrgb = qRgb(255, 0, 0);

    if (button_style_ == "green")
    {
        qrgb = qRgb(0, 255, 0);
    }
    if (button_style_ == "blue")
    {
        qrgb = qRgb(0, 0, 255);
    }
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            Image.setPixel(x+i, y+j, qrgb);
        }


    }
    Pixmap = Pixmap.fromImage(Image);
    action_ = MainWindow::Reset;
    this->update();
}

void MainWindow::onChooseRobotClicked()
{
    qDebug()<<"robot"<<endl;

    RobotWindow *robot = new RobotWindow();
    robot->show();
    cv::Mat mat = robot->image_;
    qDebug()<<robot->image_.channels();
    cv::Mat Rgb;
    QImage Img;
    if (mat.channels() == 3)//RGB Img
    {
        cv::cvtColor(mat, Rgb, CV_BGR2RGB);//颜色空间转换
        Img = QImage((const uchar*)(Rgb.data), Rgb.cols, Rgb.rows, Rgb.cols * Rgb.channels(), QImage::Format_RGB888);
    }
    else//Gray Img
    {
        Img = QImage((const uchar*)(mat.data), mat.cols, mat.rows, mat.cols*mat.channels(), QImage::Format_Indexed8);
    }
    MvLabel->setPixmap(QPixmap::fromImage(Img));
    //qDebug()<<Img.byteCount();
    //SplitterTopWidget->update();
}
void MainWindow::onOpenClicked()
{


    QString str = QFileDialog::getOpenFileName(this,
                                               "Please choose an Image file",
                                               "",
                                               "Image Files(*.jpg *.png *.bmp *.pgm *.pbm);;All(*.*)");

    if(!str.isNull())
    {
       QImage frame;
       frame.load(str);
       qDebug()<<frame.depth()<<endl;
       Image = frame.convertToFormat(QImage::Format_RGBA8888);
       Pixmap = Pixmap.fromImage(Image);
       qDebug()<<Image.depth()<<endl;
       CrtPixmap = Pixmap;
       pix_width_ = Image.width();            //图片宽
       pix_height_ = Image.height();           //图片高
       qDebug()<<str<<pix_width_<<pix_height_;
       this->setWindowTitle("图片浏览器("+str+")");

       onResetClicked();
    }
}

void  MainWindow::onBigClicked()
{
  action_=MainWindow::Shrink;
  this->update();
}
void MainWindow::onUpClicked()
{
  action_=MainWindow::Move;
  offset.setX(0);
  offset.setY(-20);

  this->update();
}
void MainWindow::onDownClicked()
{
  action_=MainWindow::Move;
  offset.setX(0);
  offset.setY(20);
  this->update();
}
void MainWindow::onResetClicked()
{
  action_=MainWindow::Reset;
  Alloffset.setX(0);
  Alloffset.setY(0);
  ratio_ = 1.000;
  StateLabel->setText("100%");
  this->update();
}
void MainWindow::OnLeftClicked()
{
  action_=MainWindow::Move;
  offset.setX(-20);
  offset.setY(0);

  this->update();
}
void MainWindow::OnRightClicked()
{
  action_=MainWindow::Move;
  offset.setX(20) ;
  offset.setY(0) ;

  this->update();
}




void MainWindow::onMapSetClicked()
{
    SecondToolBar->clear();
    SecondToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
//    NewMapAction = new QAction((tr("&新建地图")), SecondWidget);
//    NewMapAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/newmap.png"));

//    AddMapAction = new QAction((tr("&增量构建")), SecondWidget);
//    AddMapAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/zengliang.png"));

//    DecorateAction = new QAction((tr("&修饰地图")), SecondWidget);
//    DecorateAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/xiushiditu.png"));

//    VirtualWallSetAction = new QAction((tr("&虚拟墙设置")), SecondWidget);
//    VirtualWallSetAction->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/virtualWall.png"));

    SecondToolBar->addAction(NewMapAction);
    SecondToolBar->addAction(AddMapAction);
    SecondToolBar->addAction(DecorateAction);
    SecondToolBar->addAction(VirtualWallSetAction);
    //SecondWidget->update();
}



void MainWindow::onMapBagClicked()
{

    SecondToolBar->clear();

    SecondToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    SecondToolBar->addAction(LoaclCopyAction);
    SecondToolBar->addAction(ServerCopyAction);



}

void MainWindow::onFunctionClicked()
{
    SecondToolBar->clear();
    SecondToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    SecondToolBar->addAction(RobotAction);
    SecondToolBar->addAction(DrawerAction);
    SecondToolBar->addAction(CallAction);
    SecondToolBar->addAction(RouteAction);
    SecondToolBar->addAction(ContainerControlAction);
    SecondToolBar->addAction(OrderAction);
    SecondToolBar->addAction(LogAction);

}

void MainWindow::onPOIClicked()
{
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

void MainWindow::onOperationClicked()
{

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

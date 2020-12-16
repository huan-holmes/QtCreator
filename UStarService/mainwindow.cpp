
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
    Alloffset(0,0)
{
    this->setGeometry(300, 30, 1500, 1200);
    this->setStyleSheet("background-color:white;");
    PaintRect = QRect(4,45,width()/3*2 - 20 + 6, 1 + 5 + height() - 40 - this->statusBar()->height() - this->menuBar()->height() - 10 - 140);
    MainVLayout = new QVBoxLayout(this);
    MainSplitter = new QSplitter(Qt::Vertical, this);
    TopWidget = new QWidget(this);
    MainVLayout->addWidget(TopWidget);
    MainVLayout->addWidget(MainSplitter);
    SplitterTopWidget = new QWidget(this);
    SplitterBottomWidget = new QWidget(this);
    MainSplitter->addWidget(SplitterTopWidget);
    MainSplitter->addWidget(SplitterBottomWidget);
    MainSplitter->setStretchFactor(0, 6);
    MainSplitter->setStretchFactor(1, 4);
    TopWidget->setGeometry(0, 0, width(), 40);
    TopWidget->setStyleSheet("background-color:white;");
    MainSplitter->setGeometry(width() / 3 * 2 - 8, TopWidget->height() + 10 - 7, width() / 3 + 5, 4 + 5 + height() - TopWidget->height() - this->statusBar()->height() - this->menuBar()->height() - 10 - 140);
    MainSplitter->setStyleSheet("background-color:#1E1E1E;");

    this->setLayout(MainVLayout);
    ratio_= 1.0;             //初始化图片缩放比例
    action_ = MainWindow::None;
    MainWindowMenuBar = this->menuBar(); //1.创建菜单栏
    //MainWindowToolBar = addToolBar(tr("工具栏"));
    MainWindowToolBar = new QToolBar(tr("工具栏"), TopWidget); //2.创建工具栏
    MainWindowToolBar->setGeometry(0, 0, TopWidget->width(), TopWidget->height());
    MainWindowStatusBar = this->statusBar();    //3.状态栏

    MainWindowToolBar->setStyleSheet("background-color:gray;");
    MainWindowStatusBar->setStyleSheet("background-color:gray;");

    FileMenu = new QMenu("文件(&F)");
    EditMenu = new QMenu("编辑(&E)");
    ToolMenu = new QMenu("工具(&T)");
    HelpMenu = new QMenu("帮助(&H)");
    CameraMenu = new QMenu("摄像头(&C)");

    StateLabel = new QLabel("100%",this);

    FileCreateAction = new QAction("打开(&O)", this);
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

    MainWindowToolBar->addAction(FileCreateAction);
    MainWindowToolBar->addSeparator();
    MainWindowToolBar->addAction(SlamAction);
    MainWindowToolBar->addSeparator();
    MainWindowToolBar->addAction(ClearAction);
    MainWindowToolBar->addSeparator();
    MainWindowToolBar->addAction(VirtualWallAction);
    MainWindowToolBar->addSeparator();
    MainWindowToolBar->addAction(LineAction);
    MainWindowToolBar->addSeparator();
    MainWindowToolBar->addAction(ChooseAction);
    MainWindowToolBar->addSeparator();
    MainWindowToolBar->addWidget(RedToolButton);
    MainWindowToolBar->addSeparator();
    MainWindowToolBar->addWidget(GreenToolButton);
    MainWindowToolBar->addSeparator();
    MainWindowToolBar->addWidget(BlueToolButton);
    RedToolButton->setStyleSheet("QToolButton{background-color:rgba(255,0,0,200);width:15px;height:15px}");
    GreenToolButton->setStyleSheet("QToolButton{background-color:rgba(0,255,0,200);width:15px;height:15px}}");
    BlueToolButton->setStyleSheet("QToolButton{background-color:rgba(0,0,255,200);width:15px;height:15px}");

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

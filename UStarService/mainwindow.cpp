
#include "mianwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    Paint(30,30,800,800),
    clear_flag_(false),
    line_flag_(false),
    virtual_wall_flag_(0),
    virtual_wall_x1_(0),
    virtual_wall_y1_(0),
    virtual_wall_x2_(0),
    virtual_wall_y2_(0),
    button_style_(""),
    BigButton("放大",this),
    LittleButton("缩小",this),
    LiftButton("向左",this),
    RightButton("向右",this),
    UpButton("向上",this),
    DownButton("向下",this),
    ResetButton("还原",this),
    ClearButton("清除", this),
    LineButton("画线", this),
    VirtualWallButton("虚拟墙", this),
    OpenButton("打开文件",this),
    CircularRedButton("", this),
    CircularGreenButton("", this),
    CircularBlueButton("", this),
    ChooseRobotButton("选择机器人", this),

    Alloffset(0,0),
    label("100%",this)
{
    this->setGeometry(450, 50, 1200, 1000);
    this->setStyleSheet("background-color:#1E1E1E;");
    //this->setStyleSheet("background-color:white;");
    tipLbl = new QLabel(this);
    //tipLbl->setText(tr("欢迎登录"));

    ratio= 1.0;             //初始化图片缩放比例
    action = MainWindow::None;

    //QFrame *frame = new QFrame(this);
    //frame->setFrameShape(QFrame::StyledPanel);
    //frame->setFrameShadow(QFrame::Raised);
    //frame->setStyleSheet("background-color:gray;");
    //frame->setGeometry(0, 0, width(), 40);
    QMenuBar *menuBar = this->menuBar(); //1.创建菜单栏
    QMenu *fileMenu = new QMenu("文件(&F)");   //2.创建菜单
    //3.创建行为(Action)
    QAction *fileCreateAction = new QAction("打开(&O)", this);
    //fileCreateAction->setIcon(QIcon(":/ReplicationTool/png/open.png"));
    QAction *fileSaveAction = new QAction("保存(&S)",this);
    //QAction *fileImportAction = new QAction("&import",this);
    //QAction *fileExportAction = new QAction("&export",this);
    //4.将行为添加到菜单

    //fileMenu->addAction(fileImportAction);
    //fileMenu->addAction(fileExportAction);

    fileMenu->addAction(fileCreateAction);
    fileCreateAction->setShortcut(Qt::CTRL | Qt::Key_O);
    fileMenu->addAction(fileSaveAction);
    fileSaveAction->setShortcut(Qt::CTRL | Qt::Key_S);
    //5.将菜单添加到菜单栏
    menuBar->addMenu(fileMenu);
    menuBar->addSeparator();

    QMenu *slam = new QMenu("SLAM");
    menuBar->addMenu(slam);
    menuBar->addSeparator();

    QMenu *virtualWall = new QMenu("虚拟墙");
    menuBar->addMenu(virtualWall);
    menuBar->addSeparator();

    QMenu *virtualNav = new QMenu("虚拟导轨");
    menuBar->addMenu(virtualNav);
    menuBar->addSeparator();

    QMenu *poi = new QMenu("POI");
    menuBar->addMenu(poi);
    menuBar->addSeparator();

    QMenu *help = new QMenu("帮助(&H)");
    menuBar->addMenu(help);
    menuBar->addSeparator();


    BigButton.setGeometry(842,30,60,25);
    connect(&BigButton,SIGNAL(clicked()),this,SLOT(onBigClicked()));

    LittleButton.setGeometry(842,60,60,25);
    connect(&LittleButton,SIGNAL(clicked()),this,SLOT(onLittleClicked()));

    LiftButton.setGeometry(842,90,60,25);
    connect(&LiftButton,SIGNAL(clicked()),this,SLOT(OnLiftClicked()));
    RightButton.setGeometry(842,120,60,25);
    connect(&RightButton,SIGNAL(clicked()),this,SLOT(OnRightClicked()));
    UpButton.setGeometry(842,150,60,25);
    connect(&UpButton,SIGNAL(clicked()),this,SLOT(onUpClicked()));
    DownButton.setGeometry(842,180,60,25);
    connect(&DownButton,SIGNAL(clicked()),this,SLOT(onDownClicked()));


    ResetButton.setGeometry(842,210,60,25);
    connect(&ResetButton,SIGNAL(clicked()),this,SLOT(onResetClicked()));

    ClearButton.setGeometry(842,240,60,25);
    connect(&ClearButton,SIGNAL(clicked()),this,SLOT(onClearClicked()));

    LineButton.setGeometry(842,270,60,25);
    connect(&LineButton,SIGNAL(clicked()),this,SLOT(onLineClicked()));

    VirtualWallButton.setGeometry(842,300,60,25);
    connect(&VirtualWallButton,SIGNAL(clicked()),this,SLOT(onVirtualWallClicked()));

    OpenButton.setGeometry(842,330,60,25);
    connect(&OpenButton,SIGNAL(clicked()),this,SLOT(onOpenClicked()));

    CircularRedButton.setGeometry(867, 370, 10, 10);
    CircularRedButton.setStyleSheet("QPushButton{background-color:rgba(255,0,0,200);}");
    connect(&CircularRedButton,SIGNAL(clicked()),this,SLOT(onButtonRedClicked()));

    CircularGreenButton.setGeometry(867, 410, 10, 10);
    CircularGreenButton.setStyleSheet("QPushButton{background-color:rgba(0,255,0,200);}");
    connect(&CircularGreenButton,SIGNAL(clicked()),this,SLOT(onButtonGreenClicked()));

    CircularBlueButton.setGeometry(867, 450, 10, 10);
    CircularBlueButton.setStyleSheet("QPushButton{background-color:rgba(0,0,255,200);}");
    connect(&CircularBlueButton,SIGNAL(clicked()),this,SLOT(onButtonBlueClicked()));

    ChooseRobotButton.setGeometry(842, 490, 60, 25);
    connect(&ChooseRobotButton,SIGNAL(clicked()),this,SLOT(onChooseRobotClicked()));

    label.move(860,530);
    //resize(890,850);

    this->setWindowTitle("图片浏览器(请打开文件)");
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
           if(mouse->button()==Qt::LeftButton &&Paint.contains(mouse->pos()))
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
                   int x = (mouse->x() - Paint.x() - (Paint.width()/2-ratio*pixW/2)) / ratio - Alloffset.x() / ratio;
                   int y = (mouse->y() - Paint.y() - (Paint.height()/2-ratio*pixH/2)) / ratio - Alloffset.y() / ratio;
                   addPointOfInterest(x, y);
                   button_style_ = "";
               }

               PreDot = mouse->pos();
           }
           if(mouse->button()==Qt::RightButton &&Paint.contains(mouse->pos()))
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
                virtual_wall_x1_ = (mouse->x() - Paint.x() - (Paint.width()/2-ratio*pixW/2)) / ratio - Alloffset.x() / ratio;
                virtual_wall_y1_ = (mouse->y() - Paint.y() - (Paint.height()/2-ratio*pixH/2)) / ratio - Alloffset.y() / ratio;
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
                    virtual_wall_x2_ = (mouse->x()-Paint.x() - (Paint.width()/2-ratio*pixW/2))/ratio - Alloffset.x() / ratio;
                    virtual_wall_y2_ = (mouse->y()-Paint.y() - (Paint.height()/2-ratio*pixH/2))/ratio - Alloffset.y() / ratio;
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
                            image.setPixel((mouse->x()-Paint.x() - (Paint.width()/2-ratio*pixW/2))/ratio - Alloffset.x() / ratio+i, (mouse->y()-Paint.y()-(Paint.height()/2-ratio*pixH/2))/ratio - Alloffset.y() / ratio+j, qRgb(255, 255, 255));
                        }

                    }

                    pix = pix.fromImage(image);
                    action = MainWindow::Reset;
                }
                else
                {
                    for(int i=-1; i < 1; i++)
                    {
                        for(int j = -1; j < 1; j++)
                        {
                            image.setPixel((mouse->x()-Paint.x() - (Paint.width()/2-ratio*pixW/2))/ratio - Alloffset.x() / ratio +i, (mouse->y()-Paint.y()-(Paint.height()/2-ratio*pixH/2))/ratio -Alloffset.y() / ratio+ j, qRgb(0, 0, 0));
                        }

                    }

                    pix = pix.fromImage(image);
                    action = MainWindow::Reset;
                }
            }
            else
            {
                offset.setX(mouse->x() - PreDot.x());
                offset.setY(mouse->y() - PreDot.y());
                PreDot = mouse->pos();
                action = MainWindow::Move;
            }
            this->update();
         }
     }
    return QWidget::event(event);
}

void MainWindow::wheelEvent(QWheelEvent* event)     //鼠标滑轮事件
{
 if (event->delta()>0) {      //上滑,缩小

    action=MainWindow::Shrink;
    this->update();
 } else {                    //下滑,放大
     action=MainWindow::Amplification;
     this->update();
 }

 event->accept();
}



void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::SmoothPixmapTransform|QPainter::Antialiasing|QPainter::TextAntialiasing);
    painter.drawRect(Paint.x()-1,Paint.y()-1,Paint.width()+1,Paint.height()+1); //画框

    if(image.isNull())
    {
     return;
    }

    int NowW = ratio *pixW;
    int NowH = ratio *pixH;

    if(action==MainWindow::Shrink)           //缩小
    {
          ratio+=0.05*ratio;
        if(ratio<0.018)
          ratio = 0.01;

        /*显示比例*/
        QString str;
        str.sprintf("%.0f%",ratio*100);
        label.setText(str) ;
        qDebug()<<"放大:"<<ratio;
    }
    else  if(action==MainWindow::Amplification)           //放大
    {

         ratio-=0.05*ratio;
       if(ratio>4.5)
         ratio = 5.000;

        /*显示比例*/
        QString str;
        str.sprintf("%.0f%",ratio*100);
        label.setText(str);
        qDebug()<<"缩小:"<<ratio;
    }


    if(action==MainWindow::Amplification || action==MainWindow::Shrink || action==MainWindow::Reset)      //更新图片
    {
      NowW = ratio *pixW;
      NowH = ratio *pixH;


      crtPix= pix.scaled(NowW, NowH,Qt::KeepAspectRatio,Qt::SmoothTransformation); //重新装载

      action=MainWindow::None;
    }

    if(action==MainWindow::Move)                    //移动
    {
        int offsetx=Alloffset.x()+offset.x();
        Alloffset.setX(offsetx);

        int offsety=Alloffset.y()+offset.y();
        Alloffset.setY(offsety);
        action=MainWindow::None;
    }

    if(abs(Alloffset.x())>=(Paint.width()/2 + NowW/2 -10))    //限制X偏移值
    {
        if(Alloffset.x()>0)
            Alloffset.setX(Paint.width()/2 + NowW/2 -10);
        else
         Alloffset.setX(-Paint.width()/2 + -NowW/2 +10);

    }
    if(abs(Alloffset.y())>=(Paint.height()/2 + NowH/2 -10))    //限制Y偏移值
    {
        if(Alloffset.y()>0)
            Alloffset.setY(Paint.height()/2 + NowH/2 -10);
        else
         Alloffset.setY(-Paint.height()/2 + -NowH/2 +10);

    }

    int x = Paint.width()/2 + Alloffset.x() -NowW/2;
    if(x<0)
        x=0;

    int y = Paint.height()/2 + Alloffset.y() -NowH/2;
    if(y<0)
        y=0;

    int  sx = NowW/2 - Paint.width()/2 - Alloffset.x();
    if(sx<0)
        sx=0;

    int  sy = NowH/2 - Paint.height()/2 - Alloffset.y();
    if(sy<0)
        sy=0;

    int w =(NowW - sx)>Paint.width()? Paint.width() : (NowW - sx);
    if(w>(Paint.width()-x))
        w = Paint.width()-x;

    int h =(NowH - sy)>Paint.height()? Paint.height() : (NowH - sy);
    if(h>(Paint.height()-y))
        h = Paint.height()-y;



    painter.drawTiledPixmap(x+Paint.x(),y+Paint.y(),w,h,crtPix,sx,sy);             //绘画图形



}

void  MainWindow::onLittleClicked()
{
  action=MainWindow::Amplification;
  this->update();
}

void MainWindow::onClearClicked()
{
  resetVirtualWallState();
  action=MainWindow::Clear;
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
    action=MainWindow::Line;
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
    action=MainWindow::VirtualWall;
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
            image.setPixel(line_xs[i+j], line_ys[i], qRgb(0, 0, 0));
        }
    }
    pix = pix.fromImage(image);
    action = MainWindow::Reset;
    this->update();
}

void MainWindow::onButtonRedClicked()
{
    button_style_ = "red";
    qDebug()<<button_style_;
}

void MainWindow::onButtonGreenClicked()
{
    button_style_ = "green";
    qDebug()<<button_style_;
}

void MainWindow::onButtonBlueClicked()
{
    button_style_ = "blue";
    qDebug()<<button_style_;
}

void MainWindow::addPointOfInterest(int x, int y)
{
    qDebug()<<image.depth();
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
            image.setPixel(x+i, y+j, qrgb);
        }


    }
    pix = pix.fromImage(image);
    action = MainWindow::Reset;
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
                                               "Please choose an image file",
                                               "",
                                               "Image Files(*.jpg *.png *.bmp *.pgm *.pbm);;All(*.*)");

    if(!str.isNull())
    {
       QImage frame;
       frame.load(str);
       qDebug()<<frame.depth()<<endl;
       image = frame.convertToFormat(QImage::Format_RGBA8888);
       pix = pix.fromImage(image);
       qDebug()<<image.depth()<<endl;
       crtPix = pix;
       pixW = image.width();            //图片宽
       pixH = image.height();           //图片高
       qDebug()<<str<<pixW<<pixH;
       this->setWindowTitle("图片浏览器("+str+")");

       onResetClicked();
    }
}

void  MainWindow::onBigClicked()
{
  action=MainWindow::Shrink;
  this->update();
}
void MainWindow::onUpClicked()
{
  action=MainWindow::Move;
  offset.setX(0);
  offset.setY(-20);

  this->update();
}
void MainWindow::onDownClicked()
{
  action=MainWindow::Move;
  offset.setX(0);
  offset.setY(20);
  this->update();
}
void MainWindow::onResetClicked()
{
  action=MainWindow::Reset;
  Alloffset.setX(0);
  Alloffset.setY(0);
  ratio = 1.000;
  label.setText("100%");
  this->update();
}
void MainWindow::OnLiftClicked()
{
  action=MainWindow::Move;
  offset.setX(-20);
  offset.setY(0);

  this->update();
}
void MainWindow::OnRightClicked()
{
  action=MainWindow::Move;
  offset.setX(20) ;
  offset.setY(0) ;

  this->update();
}

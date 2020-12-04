
#include "ustarservice.h"

UStarService::UStarService():
    Paint(10,10,810,810),
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

    tipLbl = new QLabel(this);
    //tipLbl->setText(tr("欢迎登录"));

    ratio= 1.0;             //初始化图片缩放比例
    action = UStarService::None;




    BigButton.setGeometry(822,10,60,25);
    connect(&BigButton,SIGNAL(clicked()),this,SLOT(onBigClicked()));

    LittleButton.setGeometry(822,40,60,25);
    connect(&LittleButton,SIGNAL(clicked()),this,SLOT(onLittleClicked()));

    LiftButton.setGeometry(822,70,60,25);
    connect(&LiftButton,SIGNAL(clicked()),this,SLOT(OnLiftClicked()));
    RightButton.setGeometry(822,100,60,25);
    connect(&RightButton,SIGNAL(clicked()),this,SLOT(OnRightClicked()));
    UpButton.setGeometry(822,130,60,25);
    connect(&UpButton,SIGNAL(clicked()),this,SLOT(onUpClicked()));
    DownButton.setGeometry(822,160,60,25);
    connect(&DownButton,SIGNAL(clicked()),this,SLOT(onDownClicked()));


    ResetButton.setGeometry(822,190,60,25);
    connect(&ResetButton,SIGNAL(clicked()),this,SLOT(onResetClicked()));

    ClearButton.setGeometry(822,220,60,25);
    connect(&ClearButton,SIGNAL(clicked()),this,SLOT(onClearClicked()));

    LineButton.setGeometry(822,250,60,25);
    connect(&LineButton,SIGNAL(clicked()),this,SLOT(onLineClicked()));

    VirtualWallButton.setGeometry(822,280,60,25);
    connect(&VirtualWallButton,SIGNAL(clicked()),this,SLOT(onVirtualWallClicked()));

    OpenButton.setGeometry(822,310,60,25);
    connect(&OpenButton,SIGNAL(clicked()),this,SLOT(onOpenClicked()));

    CircularRedButton.setGeometry(847, 350, 10, 10);
    CircularRedButton.setStyleSheet("QPushButton{background-color:rgba(255,0,0,200);}");
    connect(&CircularRedButton,SIGNAL(clicked()),this,SLOT(onButtonRedClicked()));

    CircularGreenButton.setGeometry(847, 390, 10, 10);
    CircularGreenButton.setStyleSheet("QPushButton{background-color:rgba(0,255,0,200);}");
    connect(&CircularGreenButton,SIGNAL(clicked()),this,SLOT(onButtonGreenClicked()));

    CircularBlueButton.setGeometry(847, 430, 10, 10);
    CircularBlueButton.setStyleSheet("QPushButton{background-color:rgba(0,0,255,200);}");
    connect(&CircularBlueButton,SIGNAL(clicked()),this,SLOT(onButtonBlueClicked()));

    ChooseRobotButton.setGeometry(822, 470, 60, 25);
    connect(&ChooseRobotButton,SIGNAL(clicked()),this,SLOT(onChooseRobotClicked()));

    label.move(840,260);
    resize(890,850);

    this->setWindowTitle("图片浏览器(请打开文件)");
}

bool UStarService::event(QEvent * event)
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
                    action = UStarService::Reset;
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
                    action = UStarService::Reset;
                }
            }
            else
            {
                offset.setX(mouse->x() - PreDot.x());
                offset.setY(mouse->y() - PreDot.y());
                PreDot = mouse->pos();
                action = UStarService::Move;
            }
            this->update();
         }
     }
    return QWidget::event(event);
}

void UStarService::wheelEvent(QWheelEvent* event)     //鼠标滑轮事件
{
 if (event->delta()>0) {      //上滑,缩小

    action=UStarService::Shrink;
    this->update();
 } else {                    //下滑,放大
     action=UStarService::Amplification;
     this->update();
 }

 event->accept();
}



void UStarService::paintEvent(QPaintEvent *event)
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

    if(action==UStarService::Shrink)           //缩小
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
    else  if(action==UStarService::Amplification)           //放大
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


    if(action==UStarService::Amplification || action==UStarService::Shrink || action==UStarService::Reset)      //更新图片
    {
      NowW = ratio *pixW;
      NowH = ratio *pixH;


      crtPix= pix.scaled(NowW, NowH,Qt::KeepAspectRatio,Qt::SmoothTransformation); //重新装载

      action=UStarService::None;
    }

    if(action==UStarService::Move)                    //移动
    {
        int offsetx=Alloffset.x()+offset.x();
        Alloffset.setX(offsetx);

        int offsety=Alloffset.y()+offset.y();
        Alloffset.setY(offsety);
        action=UStarService::None;
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

void  UStarService::onLittleClicked()
{
  action=UStarService::Amplification;
  this->update();
}

void UStarService::onClearClicked()
{
  resetVirtualWallState();
  action=UStarService::Clear;
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
void UStarService::onLineClicked()
{
    resetVirtualWallState();
    action=UStarService::Line;
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
void UStarService::onVirtualWallClicked()
{
    virtual_wall_x1_ = 0;
    virtual_wall_y1_ = 0;
    virtual_wall_x2_ = 0;
    virtual_wall_y2_ = 0;
    action=UStarService::VirtualWall;
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
void UStarService::resetVirtualWallState(){
    virtual_wall_x1_ = 0;
    virtual_wall_y1_ = 0;
    virtual_wall_x2_ = 0;
    virtual_wall_y2_ = 0;
    virtual_wall_flag_ = 0;
    QApplication::setOverrideCursor(Qt::ArrowCursor);
}

void UStarService::drawLine(std::vector<int> line_xs, std::vector<int> line_ys)
{
    for (int i = 0; i < line_xs.size(); i++)
    {
        for(int j = -1; j <= 1; j++)
        {
            image.setPixel(line_xs[i+j], line_ys[i], qRgb(0, 0, 0));
        }
    }
    pix = pix.fromImage(image);
    action = UStarService::Reset;
    this->update();
}

void UStarService::onButtonRedClicked()
{
    button_style_ = "red";
    qDebug()<<button_style_;
}

void UStarService::onButtonGreenClicked()
{
    button_style_ = "green";
    qDebug()<<button_style_;
}

void UStarService::onButtonBlueClicked()
{
    button_style_ = "blue";
    qDebug()<<button_style_;
}

void UStarService::addPointOfInterest(int x, int y)
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
    action = UStarService::Reset;
    this->update();
}

void UStarService::onChooseRobotClicked()
{
    qDebug()<<"robot"<<endl;

    RobotWindow *robot = new RobotWindow();
    robot->show();

}
void UStarService::onOpenClicked()
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

void  UStarService::onBigClicked()
{
  action=UStarService::Shrink;
  this->update();
}
void UStarService::onUpClicked()
{
  action=UStarService::Move;
  offset.setX(0);
  offset.setY(-20);

  this->update();
}
void UStarService::onDownClicked()
{
  action=UStarService::Move;
  offset.setX(0);
  offset.setY(20);
  this->update();
}
void UStarService::onResetClicked()
{
  action=UStarService::Reset;
  Alloffset.setX(0);
  Alloffset.setY(0);
  ratio = 1.000;
  label.setText("100%");
  this->update();
}
void UStarService::OnLiftClicked()
{
  action=UStarService::Move;
  offset.setX(-20);
  offset.setY(0);

  this->update();
}
void UStarService::OnRightClicked()
{
  action=UStarService::Move;
  offset.setX(20) ;
  offset.setY(0) ;

  this->update();
}

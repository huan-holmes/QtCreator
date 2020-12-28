#include "paint.h"

Paint::Paint(QWidget *parent):
    QWidget(parent),
    clear_flag_(false),
    line_flag_(false),
    virtual_wall_flag_(0),
    virtual_wall_x1_(0),
    virtual_wall_y1_(0),
    virtual_wall_x2_(0),
    virtual_wall_y2_(0),
    button_style_(""),
    allOffset_(0,0)
{
    paintRect_ = QRect(0, 0, width(), height());
    ratio_= 1.0;             //初始化图片缩放比例
    action_ = Paint::None;
    BigButton = new QPushButton(this);
    BigButton->setGeometry(2, 50, 40, 40);
    //BigButton->setStyleSheet("QPushButton{background-image:url(:/home/boocax/QtCreator/log/Icon/big2.png);background-position:center;}");
    BigButton->setStyleSheet("border:1px dotted white;");
    BigButton->setFlat(true);
    BigButton->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/big2.png"));

    LittleButton = new QPushButton(this);
    LittleButton->setGeometry(2, 100, 40, 40);
    LittleButton->setStyleSheet("border:1px dotted white;");
    LittleButton->setFlat(true);
    LittleButton->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/small2.png"));

    RotateButton = new QPushButton(this);
    RotateButton->setGeometry(2, 150, 40, 40);
    RotateButton->setStyleSheet("border:1px dotted white;");
    RotateButton->setFlat(true);
    RotateButton->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/rotate2.png"));

    ResetButton = new QPushButton(this);
    ResetButton->setGeometry(2, 200, 40, 40);
    ResetButton->setStyleSheet("border:1px dotted white;");
    ResetButton->setFlat(true);
    ResetButton->setIcon(QIcon("/home/boocax/QtCreator/log/Icon/move2.png"));
    connect(BigButton, SIGNAL(clicked()), this, SLOT(onBigClicked()));
    connect(LittleButton, SIGNAL(clicked()), this, SLOT(onLittleClicked()));
    connect(RotateButton, SIGNAL(clicked()), this, SLOT(onRotateClicked()));
    connect(ResetButton, SIGNAL(clicked()), this, SLOT(onResetClicked()));
}

bool Paint::event(QEvent * event)
{
    //return true;
    static bool press=false;
    static QPoint preDot;

    if(event->type() == QEvent::MouseButtonPress )
    {
           QMouseEvent *mouse = dynamic_cast<QMouseEvent* >(event);

           //判断鼠标是否是左键按下,且鼠标位置是否在绘画区域
           if(mouse->button()==Qt::LeftButton &&paintRect_.contains(mouse->pos()))
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
                   int x = (mouse->x() - paintRect_.x() - (paintRect_.width()/2-ratio_*pix_width_/2)) / ratio_ - allOffset_.x() / ratio_;
                   int y = (mouse->y() - paintRect_.y() - (paintRect_.height()/2-ratio_*pix_height_/2)) / ratio_ - allOffset_.y() / ratio_;
                   addPointOfInterest(x, y);
                   button_style_ = "";
               }

               preDot = mouse->pos();
           }
           if(mouse->button()==Qt::RightButton &&paintRect_.contains(mouse->pos()))
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
                virtual_wall_x1_ = (mouse->x() - paintRect_.x() - (paintRect_.width()/2-ratio_*pix_width_/2)) / ratio_ - allOffset_.x() / ratio_;
                virtual_wall_y1_ = (mouse->y() - paintRect_.y() - (paintRect_.height()/2-ratio_*pix_height_/2)) / ratio_ - allOffset_.y() / ratio_;
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
                    virtual_wall_x2_ = (mouse->x()-paintRect_.x() - (paintRect_.width()/2-ratio_*pix_width_/2))/ratio_ - allOffset_.x() / ratio_;
                    virtual_wall_y2_ = (mouse->y()-paintRect_.y() - (paintRect_.height()/2-ratio_*pix_height_/2))/ratio_ - allOffset_.y() / ratio_;
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
                            image_.setPixel((mouse->x()-paintRect_.x() - (paintRect_.width()/2-ratio_*pix_width_/2))/ratio_ - allOffset_.x() / ratio_+i, (mouse->y()-paintRect_.y()-(paintRect_.height()/2-ratio_*pix_height_/2))/ratio_ - allOffset_.y() / ratio_+j, qRgb(255, 255, 255));
                        }

                    }

                    pixmap_ = pixmap_.fromImage(image_);
                    action_ = Paint::Reset;
                }
                else
                {
                    for(int i=-1; i < 1; i++)
                    {
                        for(int j = -1; j < 1; j++)
                        {
                            image_.setPixel((mouse->x()-paintRect_.x() - (paintRect_.width()/2-ratio_*pix_width_/2))/ratio_ - allOffset_.x() / ratio_ +i, (mouse->y()-paintRect_.y()-(paintRect_.height()/2-ratio_*pix_height_/2))/ratio_ -allOffset_.y() / ratio_+ j, qRgb(0, 0, 0));
                        }

                    }

                    pixmap_ = pixmap_.fromImage(image_);
                    action_ = Paint::Reset;
                }
            }
            else
            {
                offset_.setX(mouse->x() - preDot.x());
                offset_.setY(mouse->y() - preDot.y());
                preDot = mouse->pos();
                action_ = Paint::Move;
            }
            this->update();
         }
     }
    return QWidget::event(event);
}
void Paint::wheelEvent(QWheelEvent* event)     //鼠标滑轮事件
{
 if (event->delta()>0) {      //上滑,缩小

    action_=Paint::Shrink;
    this->update();
 } else {                    //下滑,放大
     action_=Paint::Amplification;
     this->update();
 }

 event->accept();
}

void Paint::paintEvent(QPaintEvent *event)
{
    QPainter paintRecter(this);

    paintRecter.setRenderHints(QPainter::SmoothPixmapTransform|QPainter::Antialiasing|QPainter::TextAntialiasing);
    paintRecter.drawRect(paintRect_.x()-1,paintRect_.y()-1,paintRect_.width()+1,paintRect_.height()+1); //画框
    if(image_.isNull())
    {
     return;
    }

    int NowW = ratio_ *pix_width_;
    int NowH = ratio_ *pix_height_;

    if(action_==Paint::Shrink)           //缩小
    {
          ratio_+=0.05*ratio_;
        if(ratio_<0.018)
          ratio_ = 0.01;

        /*显示比例*/
        QString str;
        str.sprintf("%.0f%",ratio_*100);

        qDebug()<<"放大:"<<ratio_;
    }
    else  if(action_==Paint::Amplification)           //放大
    {

         ratio_-=0.05*ratio_;
       if(ratio_>4.5)
         ratio_ = 5.000;

        /*显示比例*/
        QString str;
        str.sprintf("%.0f%",ratio_*100);

        qDebug()<<"缩小:"<<ratio_;
    }


    if(action_==Paint::Amplification || action_==Paint::Shrink || action_==Paint::Reset)      //更新图片
    {
      NowW = ratio_ *pix_width_;
      NowH = ratio_ *pix_height_;


      crtPixmap_ = pixmap_.scaled(NowW, NowH,Qt::KeepAspectRatio,Qt::SmoothTransformation); //重新装载

      action_=Paint::None;
    }

    if(action_==Paint::Move)                    //移动
    {
        int offsetx=allOffset_.x()+offset_.x();
        allOffset_.setX(offsetx);

        int offsety=allOffset_.y()+offset_.y();
        allOffset_.setY(offsety);
        action_=Paint::None;
    }

    if(abs(allOffset_.x())>=(paintRect_.width()/2 + NowW/2 -10))    //限制X偏移值
    {
        if(allOffset_.x()>0)
            allOffset_.setX(paintRect_.width()/2 + NowW/2 -10);
        else
         allOffset_.setX(-paintRect_.width()/2 + -NowW/2 +10);

    }
    if(abs(allOffset_.y())>=(paintRect_.height()/2 + NowH/2 -10))    //限制Y偏移值
    {
        if(allOffset_.y()>0)
            allOffset_.setY(paintRect_.height()/2 + NowH/2 -10);
        else
         allOffset_.setY(-paintRect_.height()/2 + -NowH/2 +10);

    }

    int x = paintRect_.width()/2 + allOffset_.x() -NowW/2;
    if(x<0)
        x=0;

    int y = paintRect_.height()/2 + allOffset_.y() -NowH/2;
    if(y<0)
        y=0;

    int  sx = NowW/2 - paintRect_.width()/2 - allOffset_.x();
    if(sx<0)
        sx=0;

    int  sy = NowH/2 - paintRect_.height()/2 - allOffset_.y();
    if(sy<0)
        sy=0;

    int w =(NowW - sx)>paintRect_.width()? paintRect_.width() : (NowW - sx);
    if(w>(paintRect_.width()-x))
        w = paintRect_.width()-x;

    int h =(NowH - sy)>paintRect_.height()? paintRect_.height() : (NowH - sy);
    if(h>(paintRect_.height()-y))
        h = paintRect_.height()-y;



    paintRecter.drawTiledPixmap(x+paintRect_.x(),y+paintRect_.y(),w,h,crtPixmap_,sx,sy);             //绘画图形



}

void  Paint::onBigClicked()
{
  action_=Paint::Shrink;
  this->update();
}
void Paint::onUpClicked()
{
  action_=Paint::Move;
  offset_.setX(0);
  offset_.setY(-20);

  this->update();
}
void Paint::onDownClicked()
{
  action_=Paint::Move;
  offset_.setX(0);
  offset_.setY(20);
  this->update();
}
void Paint::onRotateClicked()
{

  this->update();
}

void Paint::onResetClicked()
{
  action_=Paint::Reset;
  allOffset_.setX(0);
  allOffset_.setY(0);
  ratio_ = 1.000;
  this->update();
}
void Paint::OnLeftClicked()
{
  action_=Paint::Move;
  offset_.setX(-20);
  offset_.setY(0);

  this->update();
}
void Paint::OnRightClicked()
{
  action_=Paint::Move;
  offset_.setX(20) ;
  offset_.setY(0) ;

  this->update();
}




void  Paint::onLittleClicked()
{
  action_=Paint::Amplification;
  this->update();
}

void Paint::onClearClicked()
{
  resetVirtualWallState();
  action_=Paint::Clear;
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
void Paint::onLineClicked()
{
    resetVirtualWallState();
    action_=Paint::Line;
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
void Paint::onVirtualWallClicked()
{
    virtual_wall_x1_ = 0;
    virtual_wall_y1_ = 0;
    virtual_wall_x2_ = 0;
    virtual_wall_y2_ = 0;
    action_=Paint::VirtualWall;
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
void Paint::resetVirtualWallState(){
    virtual_wall_x1_ = 0;
    virtual_wall_y1_ = 0;
    virtual_wall_x2_ = 0;
    virtual_wall_y2_ = 0;
    virtual_wall_flag_ = 0;
    QApplication::setOverrideCursor(Qt::ArrowCursor);
}

void Paint::drawLine(std::vector<int> line_xs, std::vector<int> line_ys)
{
    for (int i = 0; i < line_xs.size(); i++)
    {
        for(int j = -1; j <= 1; j++)
        {
            image_.setPixel(line_xs[i+j], line_ys[i], qRgb(0, 0, 0));
        }
    }
    pixmap_ = pixmap_.fromImage(image_);
    action_ = Paint::Reset;
    this->update();
}
void Paint::addPointOfInterest(int x, int y)
{
    qDebug()<<image_.depth();
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
            image_.setPixel(x+i, y+j, qrgb);
        }


    }
    pixmap_ = pixmap_.fromImage(image_);
    action_ = Paint::Reset;
    this->update();
}

void Paint::setPaintRect(int width, int height)
{
    qDebug()<<width;
    qDebug()<<height;
    paintRect_ = QRect(0, 0, width, height);
}
void Paint::showImage(QString str)
{
    if(!str.isNull())
    {
       QImage frame;
       frame.load(str);
       qDebug()<<frame.depth()<<endl;
       image_ = frame.convertToFormat(QImage::Format_RGBA8888);
       pixmap_ = pixmap_.fromImage(image_);
       crtPixmap_ = pixmap_;
       pix_width_ = image_.width();            //图片宽
       pix_height_ = image_.height();           //图片高
       qDebug()<<str<<pix_width_<<pix_height_;
       //this->setWindowTitle("图片浏览器("+str+")");

       onResetClicked();
    }
}

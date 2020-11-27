
#include "widget.h"

Widget::Widget():
    Paint(10,10,810,810),
    clear_flag_(false),
    virtual_wall_flag_(false),
    BigButton("放大",this),
    LittleButton("缩小",this),
    LiftButton("向左",this),
    RightButton("向右",this),
    UpButton("向上",this),
    DownButton("向下",this),
    ResetButton("还原",this),
    ClearButton("清除", this),
    VirtualWallButton("虚拟墙", this),
    OpenButton("打开文件",this),

    Alloffset(0,0),
    label("100%",this)
{
    ratio= 1.0;             //初始化图片缩放比例
    action = Widget::None;




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

    VirtualWallButton.setGeometry(822,250,60,25);
    connect(&VirtualWallButton,SIGNAL(clicked()),this,SLOT(onVirtualWallClicked()));
    OpenButton.setGeometry(822,280,60,25);

    connect(&OpenButton,SIGNAL(clicked()),this,SLOT(onOpenClicked()));

    label.move(840,260);
    resize(890,850);

    this->setWindowTitle("图片浏览器(请打开文件)");
}

bool Widget::event(QEvent * event)
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

               if(virtual_wall_flag_)
               {
                   QApplication::setOverrideCursor(Qt::SizeBDiagCursor);
               }


               PreDot = mouse->pos();
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
            virtual_wall_flag_ = false;
        }
    }

     if(event->type() == QEvent::MouseMove)              //移动图片
     {
          if(press)
         {
            QMouseEvent *mouse = dynamic_cast<QMouseEvent* >(event);

            if(clear_flag_ or virtual_wall_flag_)
            {
                if(clear_flag_)
                {
                    for(int i=-2; i < 3; i++)
                    {
                        for(int j = -2; j < 3; j++)
                        {
                            image.setPixel((mouse->x()-Paint.x() - (Paint.width()/2-ratio*pixW/2))*ratio+i, ratio*(mouse->y()-Paint.y()-(Paint.height()/2-ratio*pixH/2))+j, qRgb(255, 255, 255));
                        }

                    }

                    pix = pix.fromImage(image);
                    action = Widget::Reset;
                }
                else
                {
                    for(int i=-1; i < 1; i++)
                    {
                        for(int j = -1; j < 1; j++)
                        {
                            image.setPixel((mouse->x()-Paint.x() - (Paint.width()/2-ratio*pixW/2))*ratio+i, ratio*(mouse->y()-Paint.y()-(Paint.height()/2-ratio*pixH/2))+j, qRgb(0, 0, 0));
                        }

                    }

                    pix = pix.fromImage(image);
                    action = Widget::Reset;
                }
            }
            else
            {
                offset.setX(mouse->x() - PreDot.x());
                offset.setY(mouse->y() - PreDot.y());
                PreDot = mouse->pos();
                action = Widget::Move;
            }
            this->update();
         }
     }
    return QWidget::event(event);
}

void Widget::wheelEvent(QWheelEvent* event)     //鼠标滑轮事件
{
 if (event->delta()>0) {      //上滑,缩小

    action=Widget::Shrink;
    this->update();
 } else {                    //下滑,放大
     action=Widget::Amplification;
     this->update();
 }

 event->accept();
}



void Widget::paintEvent(QPaintEvent *event)
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

    if(action==Widget::Shrink)           //缩小
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
    else  if(action==Widget::Amplification)           //放大
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


    if(action==Widget::Amplification || action==Widget::Shrink || action==Widget::Reset)      //更新图片
    {
      NowW = ratio *pixW;
      NowH = ratio *pixH;


      crtPix= pix.scaled(NowW, NowH,Qt::KeepAspectRatio,Qt::SmoothTransformation); //重新装载

      action=Widget::None;
    }

    if(action==Widget::Move)                    //移动
    {
        int offsetx=Alloffset.x()+offset.x();
        Alloffset.setX(offsetx);

        int offsety=Alloffset.y()+offset.y();
        Alloffset.setY(offsety);
        action=Widget::None;
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

void  Widget::onLittleClicked()
{
  action=Widget::Amplification;
  this->update();
}

void Widget::onClearClicked()
{
  action=Widget::Clear;
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
void Widget::onVirtualWallClicked()
{
    action=Widget::VirtualWall;
    if(virtual_wall_flag_)
    {
        virtual_wall_flag_ = false;
    }
    else
    {
        QApplication::setOverrideCursor(Qt::SizeBDiagCursor);
        virtual_wall_flag_ = true;

    }
    this->update();
}

void Widget::onOpenClicked()
{


    QString str = QFileDialog::getOpenFileName(this,
                                               "Please choose an image file",
                                               "",
                                               "Image Files(*.jpg *.png *.bmp *.pgm *.pbm);;All(*.*)");

    if(!str.isNull())
    {


       image.load(str);
       pix = pix.fromImage(image);

       crtPix = pix;
       pixW = image.width();            //图片宽
       pixH = image.height();           //图片高
       qDebug()<<str<<pixW<<pixH;
       this->setWindowTitle("图片浏览器("+str+")");
       onResetClicked();
    }
}

void  Widget::onBigClicked()
{
  action=Widget::Shrink;
  this->update();
}
void Widget::onUpClicked()
{
  action=Widget::Move;
  offset.setX(0);
  offset.setY(-20);

  this->update();
}
void Widget::onDownClicked()
{
  action=Widget::Move;
  offset.setX(0);
  offset.setY(20);
  this->update();
}
void Widget::onResetClicked()
{
  action=Widget::Reset;
  Alloffset.setX(0);
  Alloffset.setY(0);
  ratio = 1.000;
  label.setText("100%");
  this->update();
}
void Widget::OnLiftClicked()
{
  action=Widget::Move;
  offset.setX(-20);
  offset.setY(0);

  this->update();
}
void Widget::OnRightClicked()
{
  action=Widget::Move;
  offset.setX(20) ;
  offset.setY(0) ;

  this->update();
}

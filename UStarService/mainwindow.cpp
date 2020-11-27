#include "mainwindow.h"
#include "ui_mainwindow.h"

//MainWindow::MainWindow(QWidget *parent) :
//    QMainWindow(parent),
//    ui(new Ui::MainWindow)
//{
//    ui->setupUi(this);
//}


MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    Paint(10,10,810,810),
    BigButton("放大",ui),
    LittleButton("缩小",ui),
    LiftButton("向左",ui),
    RightButton("向右",ui),
    UpButton("向上",ui),
    DownButton("向下",ui),
    ResetButton("还原",ui),
    OpenButton("打开文件",ui),
    Alloffset(0,0),
    label("100%",ui)
{
    ui->setupUi(this);
    ratio= 1.0;             //初始化图片缩放比例
    action = MainWindow::None;




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

    OpenButton.setGeometry(822,220,60,25);
    connect(&OpenButton,SIGNAL(clicked()),this,SLOT(onOpenClicked()));

    label.move(840,260);
    resize(890,850);

    this->setWindowTitle("图片浏览器(请打开文件)");
}
MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::event(QEvent * event)
{
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
        }
    }

     if(event->type() == QEvent::MouseMove)              //移动图片
     {
          if(press)
         {
            QMouseEvent *mouse = dynamic_cast<QMouseEvent* >(event);

            offset.setX(mouse->x() - PreDot.x());
            offset.setY(mouse->y() - PreDot.y());
            PreDot = mouse->pos();
            action = MainWindow::Move;

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
          ratio-=0.05*ratio;
        if(ratio<0.018)
          ratio = 0.01;

        /*显示比例*/
        QString str;
        str.sprintf("%.0f%",ratio*100);
        label.setText(str) ;
        qDebug()<<"缩小:"<<ratio;
    }
    else  if(action==MainWindow::Amplification)           //放大
    {

         ratio+=0.05*ratio;
       if(ratio>4.5)
         ratio = 5.000;

        /*显示比例*/
        QString str;
        str.sprintf("%.0f%",ratio*100);
        label.setText(str);
        qDebug()<<"放大:"<<ratio;
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

void MainWindow::onOpenClicked()
{


    QString str = QFileDialog::getOpenFileName(this,
                                 "open",
                                 "D:",
                                 "img (*.png *.jpg, *.pgm)");

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

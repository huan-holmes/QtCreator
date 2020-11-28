#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtGui>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QApplication>
#include <QFileDialog>
#include <QImage>
#include <QMouseEvent>
#include "gridline.h"
class Widget : public QWidget
{
    Q_OBJECT

private :
    QPixmap  pix;
    QPixmap  crtPix;
    int action;          //动作(放大,缩小,移动...)
    int pixW;            //图片宽
    int pixH;            //图片高

    QRect Paint;         //绘画区域

    QImage image;        //打开的图片
    bool clear_flag_;
    bool virtual_wall_flag_;
    int double_click_;
    int double_click_x1_;
    int double_click_y1_;
    int double_click_x2_;
    int double_click_y2_;


    float ratio;              //缩放比例
    QPoint offset;           //一次的图片偏移值
    QPoint Alloffset;          //总偏移
    QLabel label;

    QPushButton  BigButton;
    QPushButton  LittleButton;
    QPushButton  LiftButton;
    QPushButton  RightButton;
    QPushButton  UpButton;
    QPushButton  DownButton;
    QPushButton  ResetButton;
    QPushButton  ClearButton;
    QPushButton  VirtualWallButton;
    QPushButton  DoubleClickButton;
    QPushButton  OpenButton;

    void AddComboItem(QComboBox* cmbo);
    bool event(QEvent * event);
    void wheelEvent(QWheelEvent* e);     //鼠标滑轮事件
    void drawLine(std::vector<int> line_xs, std::vector<int> line_ys);

private slots:
    void    onUpClicked();
    void    onDownClicked();
    void    onResetClicked();
    void    OnLiftClicked();
    void    OnRightClicked();
    void    onLittleClicked();
    void    onBigClicked();
    void    onClearClicked();
    void    onVirtualWallClicked();
    void    onDoubleClickClicked();
    void    onOpenClicked();

   void paintEvent(QPaintEvent *event);
public:
    explicit Widget();

    enum  Type {
        None          = 0,
        Amplification ,
        Shrink,
        Lift,
        Right,
        Up,
        Down,
        Move,
        Clear,
        VirtualWall,
        DoubleClick,
        Reset
    };

};
#endif // WIDGET_H


#ifndef WIDGET_H
#define WIDGET_H
#include <QMainWindow>
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
class UStarService : public QWidget
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
    bool line_flag_;
    int virtual_wall_flag_;
    int virtual_wall_x1_;
    int virtual_wall_y1_;
    int virtual_wall_x2_;
    int virtual_wall_y2_;

    QString button_style_;

    QLabel *tipLbl;  //"欢迎登录"标签




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
    QPushButton  LineButton;
    QPushButton  VirtualWallButton;
    QPushButton  OpenButton;
    QPushButton  CircularRedButton;
    QPushButton  CircularGreenButton;
    QPushButton  CircularBlueButton;

    void AddComboItem(QComboBox* cmbo);
    bool event(QEvent * event);
    void wheelEvent(QWheelEvent* e);     //鼠标滑轮事件
    void drawLine(std::vector<int> line_xs, std::vector<int> line_ys);
    void resetVirtualWallState();
    void addPointOfInterest(int x, int y);


private slots:
    void    onUpClicked();
    void    onDownClicked();
    void    onResetClicked();
    void    OnLiftClicked();
    void    OnRightClicked();
    void    onLittleClicked();
    void    onBigClicked();
    void    onClearClicked();
    void    onLineClicked();
    void    onVirtualWallClicked();
    void    onOpenClicked();
    void    onButtonRedClicked();
    void    onButtonGreenClicked();
    void    onButtonBlueClicked();
    void    paintEvent(QPaintEvent *event);
public:
    explicit UStarService();

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
        Line,
        VirtualWall,
        Reset,
        Style,
    };

};
#endif // USTARSERVICE_H


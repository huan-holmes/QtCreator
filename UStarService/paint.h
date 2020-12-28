#ifndef PAINT_H
#define PAINT_H
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include <QPaintEvent>
#include <QDebug>
#include <QPushButton>
#include "gridline.h"


class Paint : public QWidget
{
    Q_OBJECT
public:
    explicit Paint(QWidget *parent = 0);


    bool event(QEvent * event);
    void wheelEvent(QWheelEvent* e);     //鼠标滑轮事件
    void drawLine(std::vector<int> line_xs, std::vector<int> line_ys);

    void resetVirtualWallState();
    void addPointOfInterest(int x, int y);
    void setPaintRect(int width, int height);
    void showImage(QString str);
    //void onResetClicked();
public:
    enum  Type {
        None = 0,
        Amplification,
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
        ChooseRobot,
    };
public:
    QPushButton *BigButton;
    QPushButton *LittleButton;
    QPushButton *RotateButton;
    QPushButton *ResetButton;

private:
    QPixmap  pixmap_;
    QPixmap  crtPixmap_;
    QRect paintRect_;         //绘画区域
    QImage image_;        //打开的图片
    QPoint offset_;           //一次的图片偏移值
    QPoint allOffset_;          //总偏移

    float ratio_;              //缩放比例
    int action_;          //动作(放大,缩小,移动...)
    int pix_width_;            //图片宽
    int pix_height_;            //图片高
    bool clear_flag_;
    bool line_flag_;
    QString button_style_;
    int virtual_wall_flag_;
    int virtual_wall_x1_;
    int virtual_wall_y1_;
    int virtual_wall_x2_;
    int virtual_wall_y2_;
private slots:
    void    paintEvent(QPaintEvent *event);
    void    onUpClicked();
    void    onDownClicked();
    void    onRotateClicked();
    void    onResetClicked();
    void    OnLeftClicked();
    void    OnRightClicked();
    void    onLittleClicked();
    void    onBigClicked();
    void    onClearClicked();
    void    onLineClicked();
    void    onVirtualWallClicked();

};

#endif // PAINT_H


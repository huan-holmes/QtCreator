#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QtGui>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QApplication>
#include <QFileDialog>
#include <QImage>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    enum  Type {
        None          = 0,
        Amplification ,
        Shrink,
        Lift,
        Right,
        Up,
        Down,
        Move,
        Reset
    };

private slots:
    void    onUpClicked();
    void    onDownClicked();
    void    onResetClicked();
    void    OnLiftClicked();
    void    OnRightClicked();
    void    onLittleClicked();
    void    onBigClicked();

    void    onOpenClicked();

   void paintEvent(QPaintEvent *event);
private:
    Ui::MainWindow *ui;
    QPixmap  pix;
    QPixmap  crtPix;
    int action;          //动作(放大,缩小,移动...)
    int pixW;            //图片宽
    int pixH;            //图片高

    QRect Paint;         //绘画区域

    QImage image;        //打开的图片


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
    QPushButton  OpenButton;

    void AddComboItem(QComboBox* cmbo);
    bool event(QEvent * event);
    void wheelEvent(QWheelEvent* e);     //鼠标滑轮事件
};

#endif // MAINWINDOW_H

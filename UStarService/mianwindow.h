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
#include <QMouseEvent>
#include "gridline.h"
#include "robot.h"
#include "loginform.h"
#include <QDialog>
#include <QToolBar>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QFrame>
#include <QToolButton>
#include <QSpinBox>
#include <QStatusBar>
#include <QSplitter>
#include <QTextEdit>
#include <QObject>
#include <QHBoxLayout>
#include <QTimer>
#include <QVBoxLayout>
#include <cv.h>
#include <QTimeEdit>
#include <QDockWidget>
class MainWindow : public QMainWindow
{
    Q_OBJECT

enum ToolChoose
{
    MAPSET,
    MAPBAG,
    FUNCTION,
    POI,
    LOG,
};

private :
    QPixmap  Pixmap;
    QPixmap  CrtPixmap;
    QRect PaintRect;         //绘画区域
    QImage Image;        //打开的图片
    QPoint offset;           //一次的图片偏移值
    QPoint Alloffset;          //总偏移
    QLabel label;

    QSplitter *MainSplitter;
    QWidget *SplitterTopWidget;
    QWidget *SplitterBottomWidget;
    QVBoxLayout *MainVLayout;
    QWidget *TopWidget;
    QWidget *SecondWidget;
    QWidget *BottomWidget;


    QMenuBar *MainWindowMenuBar;
    QToolBar *MainWindowToolBar;
    QToolBar *SecondToolBar;
    QStatusBar *MainWindowStatusBar;
    QMenu *FileMenu;
    QMenu *EditMenu;
    QMenu *ToolMenu;
    QMenu *HelpMenu;
    QMenu *CameraMenu;

    QLabel *StateLabel;

    QLabel *OpencvLabel;

    QLabel *MvLabel;
    QLabel *PicLabel;

    QAction *FileCreateAction;
    QAction *FileSaveAction;
    QAction *BaseAction;
    QAction *BigAction;
    QAction *LittleAction;
    QAction *RightAction;
    QAction *LeftAction;
    QAction *UpAction;
    QAction *DownAction;
    QAction *VirtualWallAction;
    QAction *ClearAction;
    QAction *LineAction;
    QAction *SlamAction;
    QAction *ChooseAction;
    QAction *OpenCameraAction;
    QAction *CloseCameraAction;
    QAction *TakeCameraPictureAction;
    QToolButton *RedToolButton;
    QToolButton *GreenToolButton;
    QToolButton *BlueToolButton;


    QAction *NewMapAction;
    QAction *AddMapAction;
    QAction *DecorateAction;
    QAction *VirtualWallSetAction;
    QAction *LoaclCopyAction;
    QAction *ServerCopyAction;
    QAction *RobotAction;
    QAction *DrawerAction;
    QAction *CallAction;
    QAction *RouteAction;
    QAction *ContainerControlAction;
    QAction *OrderAction;
    QAction *LogAction;
    QLabel *ToolStoreyLable;
    QAction *RoomPointAction;
    QComboBox *StoreyComboBox;
    QAction *GoalPointAction;
    QAction *DeceleratePointAction;
    QAction *ChargePointAction;
    QAction *LiftPointAction;
    QLabel *UserNameLabel;
    QLineEdit *UserNameLineEdit;


    QString button_style_;
    float ratio_;              //缩放比例
    int action_;          //动作(放大,缩小,移动...)
    int pix_width_;            //图片宽
    int pix_height_;            //图片高
    bool clear_flag_;
    bool line_flag_;
    int virtual_wall_flag_;
    int virtual_wall_x1_;
    int virtual_wall_y1_;
    int virtual_wall_x2_;
    int virtual_wall_y2_;
    QTimer *timer_;

    void AddComboItem(QComboBox* cmbo);
    bool event(QEvent * event);
    void wheelEvent(QWheelEvent* e);     //鼠标滑轮事件
    void drawLine(std::vector<int> line_xs, std::vector<int> line_ys);
    void resetVirtualWallState();
    void addPointOfInterest(int x, int y);

    void InitSecondToolBarAction();


    ToolChoose choose_;

private slots:
    void    onUpClicked();
    void    onDownClicked();
    void    onResetClicked();
    void    OnLeftClicked();
    void    OnRightClicked();
    void    onLittleClicked();
    void    onBigClicked();
    void    onClearClicked();
    void    onLineClicked();
    void    onVirtualWallClicked();
    void    onOpenClicked();
    void    onRedClicked();
    void    onGreenClicked();
    void    onBlueClicked();
    void    paintEvent(QPaintEvent *event);
    void    onChooseRobotClicked();
    void    onMapSetClicked();
    void    onMapBagClicked();
    void    onFunctionClicked();
    void    onPOIClicked();
    void    onOperationClicked();

    //void    onOpenCameraClicked();
    //void    onCloseCameraClicked();
    //void    onTakePictureClicked();
    //void    readCameraFrame();

public:
    explicit MainWindow(QMainWindow *parent = 0);

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

};
#endif // MAINWINDOW_H


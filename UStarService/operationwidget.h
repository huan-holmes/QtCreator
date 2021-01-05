#ifndef OPERATIONWIDGET_H
#define OPERATIONWIDGET_H
#include <QWidget>
#include <QVBoxLayout>
#include <QToolBar>
#include <QToolButton>
#include <QAction>
#include <QDebug>
#include <QFileDialog>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QDate>
#include <QDateTimeEdit>
#include "paint.h"

class OperationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OperationWidget(QWidget *parent = 0);
    void InitToolBarAction();
    void InitPaint();
    void createView();


private slots:
    void    onMapBagClicked();
    void    onPOIClicked();
    void    onFunctionClicked();
    void    onOperationClicked();
    void    onLocalImportClicked();
    void    onRoomPointClicked();
    void    onGoalPointClicked();
    void    onDeceleratePointClicked();
    void    onChargePointClicked();
    void    onLiftPointClicked();
    void    onOtherPointClicked();

public:
    Paint *paint_;
    QString button_style_;

private:
    QVBoxLayout *MainVLayout;
    QWidget *MVLFirstWidget;
    QWidget *MVLSecondWidget;
    QWidget *MVLThirdWidget;
    QWidget *MVLFourthWidget;

    QToolBar *FirstToolBar;
    QToolBar *SecondToolBar;

    QLabel *ToolLogLable;
    QImage *LogImage;
    QToolButton *MapBagToolButton;
    QAction *LocalImportAction;
    QAction *ServerImportAction;
    QAction *LoaclCopyAction;
    QAction *ServerCopyAction;
    QToolButton *POIToolButton;
    QLabel *ToolStoreyLable;
    QAction *RoomPointAction;
    QComboBox *StoreyComboBox;
    QAction *GoalPointAction;
    QAction *DeceleratePointAction;
    QAction *ChargePointAction;
    QAction *LiftPointAction;
    QAction *OtherPointAction;
    QToolButton *FunctionToolButton;
    QAction *RobotAction;
    QAction *DrawerAction;
    QAction *CallAction;
    QAction *RouteAction;
    QAction *ContainerControlAction;
    QAction *OrderAction;
    QAction *LogAction;
    QAction *AbnormalPushAction;
    QToolButton *OperationLogToolButton;
    QLabel *UserNameLabel;
    QLineEdit *UserNameLineEdit;
    QLabel *StartTimeLabel;
    QLineEdit *StartTimeLineEdit;
    QLabel *EndTimeLabel;
    QLineEdit *EndTimeLineEdit;
};
#endif // OPERATIONWIDGET_H


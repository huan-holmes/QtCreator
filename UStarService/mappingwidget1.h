#ifndef MAPPINGWIDGET_H
#define MAPPINGWIDGET_H
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

class MappingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MappingWidget(QWidget *parent = 0);
    void InitToolBarAction();
    void InitPaint();
    void createView();

private slots:
    void    onMappingClicked();
    void    onMapBagClicked();
    void    onPOIClicked();
    void    onOperationLogClicked();
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

    QToolButton *MappingToolButton;
    QAction *NewMapAction;
    QAction *ModifyMappingAction;
    QAction *DecorateAction;
    QAction *VirtualWallAction;
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
    QToolButton *OperationLogToolButton;
    QLabel *UserNameLabel;
    QLineEdit *UserNameLineEdit;
    QLabel *StartTimeLabel;
    QLineEdit *StartTimeLineEdit;
    QLabel *EndTimeLabel;
    QLineEdit *EndTimeLineEdit;
    QToolButton *SearchToolButton;

};


#endif // MAPPINGWIDGET_H

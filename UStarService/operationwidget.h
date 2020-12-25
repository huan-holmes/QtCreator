#ifndef OPERATIONWIDGET_H
#define OPERATIONWIDGET_H
#include <QWidget>
#include <QVBoxLayout>
#include <QToolBar>
#include <QToolButton>
#include <QAction>
#include <QDebug>
#include <QFileDialog>
#include "paint.h"

class OperationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OperationWidget(QWidget *parent = 0);
    void InitToolBarAction();
    void InitPaint();

private slots:
    void    onMapBagClicked();
    void    onFunctionClicked();
    void    onLocalImportClicked();

public:
    Paint *paint_;
private:
    QVBoxLayout *MainVLayout;
    QWidget *MVLFirstWidget;
    QWidget *MVLSecondWidget;
    QWidget *MVLThirdWidget;
    QWidget *MVLFourthWidget;

    QToolBar *FirstToolBar;
    QToolBar *SecondToolBar;

    QToolButton *MapBagToolButton;
    QAction *LocalImportAction;
    QAction *ServerImportAction;
    QAction *LoaclCopyAction;
    QAction *ServerCopyAction;
    QToolButton *FunctionToolButton;
    QAction *RobotAction;
    QAction *DrawerAction;
    QAction *CallAction;
    QAction *RouteAction;
    QAction *ContainerControlAction;
    QAction *OrderAction;
    QAction *LogAction;
    QAction *AbnormalPushAction;




};
#endif // OPERATIONWIDGET_H


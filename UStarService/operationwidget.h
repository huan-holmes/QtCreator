#ifndef OPERATIONWIDGET_H
#define OPERATIONWIDGET_H
#include <QWidget>
#include <QVBoxLayout>
#include <QToolBar>
#include <QToolButton>
#include <QAction>
#include <QDebug>
#include "paint.h"

class OperationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OperationWidget(QWidget *parent = 0);
    void InitToolBarAction();

private slots:
    void    onMapBagClicked();
private:
    QVBoxLayout *MainVLayout;
    QWidget *MVLFirstWidget;
    QWidget *MVLSecondWidget;
    QWidget *MVLThirdWidget;
    QWidget *MVLFourthWidget;

    QToolBar *FirstToolBar;
    QToolBar *SecondToolBar;

    QToolButton *MapBagToolButton;
    QAction *LoaclCopyAction;
    QAction *ServerCopyAction;



};
#endif // OPERATIONWIDGET_H


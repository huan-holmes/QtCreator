#ifndef VIRTUALWALLDOCKWIDGET_H
#define VIRTUALWALLDOCKWIDGET_H
#include <QMainWindow>
#include <QTextEdit>
#include <QDockWidget>
#include <QWidget>
#include <QDebug>
#include <QLabel>

class VirtualWallDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit VirtualWallDockWidget(QWidget *parent = 0);
};
#endif // VIRTUALWALLDOCKWIDGET_H


#ifndef VIRTUALWALLDOCKWIDGET_H
#define VIRTUALWALLDOCKWIDGET_H
#include <QMainWindow>
#include <QTextEdit>
#include <QDockWidget>
#include <QWidget>
#include <QDebug>
#include <QLabel>
#include <QAction>
#include <QPushButton>
#include <QColor>
#include <QColorDialog>
#include "paint.h"

class VirtualWallDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit VirtualWallDockWidget(QWidget *parent = 0, Paint *paint = 0);

public:
    Paint *paint_;
    QLabel *ImageLabel;
    QImage *Img;
    QLabel *VirtualWallType;

    QPushButton *LineButton;
    QPushButton *CurveButton;
    QPushButton *SquareButton;
    QPushButton *AbnormalButton;
    QLabel *VirtualWallColor;
    QPushButton *ColorButton;
    QPalette *ColorPalette;
private slots:
    void onLineClicked();
    void onAbnormalClicked();
    void onColorClicked();
};
#endif // VIRTUALWALLDOCKWIDGET_H


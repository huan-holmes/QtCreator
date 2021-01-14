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
    QString converRGB16HexStr(QColor color);

public:
    Paint *paint_;
    QLabel *ImageLabel;
    QImage *Img;
    QLabel *VirtualWallType;
    QLabel *BrushSizeLabel;
    QPushButton *RevokeButton;
    QPushButton *CancelRevokeButton;
    QPushButton *EmptyButton;
    QPushButton *SaveButton;

    QPushButton *LineButton;
    QPushButton *CurveButton;
    QPushButton *SquareButton;
    QPushButton *AbnormalButton;
    QLabel *VirtualWallColor;
    QPushButton *ColorButton;
    QPushButton *OneSizeButton;
    QPushButton *TwoSizeButton;
    QPushButton *ThreeSizeButton;
    QPushButton *FourSizeButton;
    //QPalette *ColorPalette;
private slots:
    void onLineClicked();
    void onAbnormalClicked();
    void onColorClicked();
};
#endif // VIRTUALWALLDOCKWIDGET_H


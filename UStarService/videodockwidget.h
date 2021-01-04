#ifndef VIDEODOCKWIDGET_H
#define VIDEODOCKWIDGET_H
#include <QDockWidget>
#include <QWidget>
#include <QLabel>
#include <QDebug>
class VideoDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit VideoDockWidget(QWidget *parent = 0);

private:
    QLabel *VideoShowLabel;
    QImage *Img;

};
#endif // VIDEODOCKWIDGET_H


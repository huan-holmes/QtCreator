#ifndef VIDEODOCKWIDGET_H
#define VIDEODOCKWIDGET_H
#include <QDockWidget>
#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
class VideoDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit VideoDockWidget(QWidget *parent = 0);
    ~VideoDockWidget();

    void InitSocketInfo();
    void ReadSocketImage2Label();

public:
    QTcpSocket *socket_;

private:
    QLabel *VideoShowLabel;
    QImage Img;

};
#endif // VIDEODOCKWIDGET_H


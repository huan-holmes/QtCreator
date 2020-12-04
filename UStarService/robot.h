#ifndef ROBOT_H
#define ROBOT_H


#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDateTime>
#include <QDebug>
#include <QDir>

class RobotWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RobotWindow(QWidget *parent = 0);
    ~RobotWindow();
private:
    QLabel *ip_;         //"ip"标签
    QLabel *pwd_;              //"密码"标签
    QLineEdit *ip_edi_;      //ip编辑行
    QLineEdit *pwd_edi_;           //密码编辑行
    QPushButton *connetct_;       //连接按钮
};

#endif // ROBOT_H

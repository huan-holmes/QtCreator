#ifndef ROBOT_H
#define ROBOT_H


#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QDialog>
#include <QTcpSocket>

class RobotWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RobotWindow(QDialog *parent = 0);
    ~RobotWindow();

private slots:
    void onConnectClicked();

private:
    QLabel *ip_;         //"ip"标签
    QLabel *port_;
    QLabel *pwd_;              //"密码"标签
    QLineEdit *ip_edi_;      //ip编辑行
    QLineEdit *port_edi_;
    QLineEdit *pwd_edi_;           //密码编辑行
    QPushButton *connect_;       //连接按钮

    QTcpSocket *socket_;
};

#endif // ROBOT_H

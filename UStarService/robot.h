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
#include <QHostAddress>
#include <QMessageBox>
class RobotWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RobotWindow(QDialog *parent = 0);
    ~RobotWindow();

private slots:
    void onConnectClicked();
    void onReceivedData();

private:
    QLabel *IpLabel;         //"ip"标签
    QLabel *PortLabel;
    QLabel *PwdLabel;              //"密码"标签
    QLineEdit *IpLineEdit;      //ip编辑行
    QLineEdit *PortLineEdit;
    QLineEdit *PwdLineEdit;           //密码编辑行
    QPushButton *ConnectButton;       //连接按钮

    QTcpSocket *socket_;
    bool connect_flag_;
    bool write_flag_;
};

#endif // ROBOT_H

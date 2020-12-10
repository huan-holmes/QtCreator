#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPushButton"
#include "QLabel"
#include "QDockWidget"
#include "QTextEdit"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //调整窗口大小
    resize(600,400);
    //创建一个菜单栏




}

MainWindow::~MainWindow()
{
    delete ui;
}

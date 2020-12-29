#include "mianwindow.h"
#include "operationwidget.h"
#include "mappingwidget.h"
#include <QApplication>
#include "loginform.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //MainWindow mw;
    LoginForm login;
    MappingWidget mw;
    OperationWidget ow;
    int login_int = login.exec();
    if (login_int == 1)//调用login.exec()，阻塞主控制流，直到完成返回，继续执行主控制流
    {
        mw.show();
    }
    if (login_int == 2)//调用login.exec()，阻塞主控制流，直到完成返回，继续执行主控制流
    {
        ow.show();
    }
    return app.exec();
}

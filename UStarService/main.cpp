#include "ustarservice.h"
#include <QApplication>
#include "loginform.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    UStarService us;
    LoginForm login;
    if (login.exec() == QDialog::Accepted)//调用login.exec()，阻塞主控制流，直到完成返回，继续执行主控制流
    {
       us.show();
       return app.exec();
    }
    //us.show();

    return app.exec();
}

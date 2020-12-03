#include "ustarservice.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QFile qss("button_circle.qss");
//    if( qss.open(QFile::ReadOnly))
//    {
//        qDebug("open success");

//        QString style = QLatin1String(qss.readAll());

//        a.setStyleSheet(style);

//        qss.close();
//    }
//    else
//    {
//        qDebug("Open failed");

//     }
    UStarService us;
    us.show();

    return a.exec();
}

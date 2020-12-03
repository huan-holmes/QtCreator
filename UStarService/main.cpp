#include "ustarservice.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UStarService us;
    us.show();

    return a.exec();
}

#include <QApplication>

#include "widget.h"
#include "netinfo.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;
    w.show();

    return a.exec();
}

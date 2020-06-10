#include <QApplication>

#include "salverwidget.h"
#include "netinfo.h"
#include "allinfowidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;
    w.show();
    
    //AllInfoWidget hw;
    //hw.show();
    return a.exec();
}

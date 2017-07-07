#include "mainmap.h"
#include <QApplication>
#include "scenetypes.h"
#include "upointer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle("windows");
    MainMap w;
    w.showMaximized();
    return a.exec();

}

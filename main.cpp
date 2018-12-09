#include "eksixml.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EksiXML w;
    w.show();

    return a.exec();
}

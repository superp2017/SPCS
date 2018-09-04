#include <QCoreApplication>

#include "faceMap.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    faceMap t;
    t.radarFaceTo();

    return a.exec();
}

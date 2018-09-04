#include <QCoreApplication>
#include <QDebug>
#include "powerate.h"
#include <stdio.h>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Powerate prt("./config/20140705_5M.s2p");
    qDebug() << "avg = " << prt.get_avg();
    return a.exec();
}

#include <QApplication>
#include "hrectanglearray.h"
#include "htrianglearray.h"
#include "hgridcirclearray.h"
#include"hgenarray.h"
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HGenArray init;
    init.setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));

    init.show();
    return a.exec();
}

#ifndef FACEMAP_H
#define FACEMAP_H

//#include <QWidget>
#include <vector>
#include <QDebug>
#include <QTextStream>
#include <QFile>

#define ROW_OFFSET -15.1//x
#define COL_OFFSET 0//y
#define HEI_OFFSET 0//z

#define COL_WIDTH  14.85*2
#define ROW_HEIGHT 8.575

#include "TransForm.h"

typedef struct _data{
    short row;
    short col;
    int   id;
    double x;
    double y;
    double z;
}Data;

/*!
 * \brief The faceMap class
 *  阵面生成工具,只生成目前所里这一种格式
 */
class faceMap
{

public:
    explicit faceMap();

    void radarFaceTo();

private:
   void saveFile();
    void genarray(int xstart, int xend, int ystart, int yend, bool isonesection);


private:
    std::vector<Data> fileData;

signals:

public slots:

};

#endif // FACEMAP_H

#include "twoshorttoid.h"

TwoShortToId::TwoShortToId(QObject *parent):
    QObject(parent)
{
}


/*!
 * \将每个阵元的行,列值（行,列值为short类型）转化为一个int类型的id号
 */
int TwoShortToId::AddrToId(short row, short col)
{
    char *c_id = (char*)malloc(4);
    memset(c_id,0,4);
    memcpy(c_id,&col,2);
    memcpy(c_id+2,&row,2);
    int id = *((int*)c_id);
    delete c_id;
    c_id = 0;
    return id;
}


/*!
 *\ 已知阵元的id号（id号为int类型）转化为两个short类型的行,列号
 */
void TwoShortToId::IdToAddr(int id, short &row, short &col)
{
    char *c_id = (char*)&id;
    row = *((short*)c_id+1);
    col = *((short*)c_id);
}

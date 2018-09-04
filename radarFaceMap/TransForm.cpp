#include "TransForm.h"

#include <string.h>
#include <QDebug>
TransForm::TransForm()
{
}


/*!
 * \brief TransForm::AddreToId
 * \param row
 * \param col
 * \return
 *本阵面行号最多为40，列号最大为12
 *对于行号（列号）n为负数的情况:
 ** 转化为n = |n| + 40(12)
 */
int TransForm::AddreToId(short row, short col)
{
    //    int address = ((~0x0 >> 16) & row ) |(((~0x0 >>16)&col)<<16);
    if(row < 0)
    {
        row *= -1;
        row += 40;
    }
    if(col < 0)
    {
        col *= -1;
        col += 12;
    }
    int address = (((~0x0 >> 16) & row) << 16 ) | ((~0x0 >>16)&col);
    return address;
}

/*!
 * \brief TransForm::IdToAddre
 * \param id
 * \param row
 * \param col
 *本阵面行号最多为40，列号最大为12
 *对于行号（列号）n大于40(12)的情况:
 ** n -= 40;n = -n;
 **
 */
void TransForm::IdToAddre(int id, short &row, short &col)
{
    int mask = 0x0000FFFF;
    row= (~mask & id) >> 16;
    col = mask & id;
    if(row > 40)
    {
        row %= 40;
        row *= -1;
    }
    if(col > 12)
    {
        col %= 12;
        col *= -1;
    }
}


/*!
 * \brief TransForm::locationToId
 * \param row
 * \param col
 * \return
 *
 *通过行号和列号计算id;
 *行号和列号都为short类型
 *所以可以把行号作为高字节，列号作为低字节组成一个int变量作为id
 */
int TransForm::locationToId(short &row, short &col)
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

void TransForm::idToLocation(int id, short &row, short &col)
{
    char *c_id = (char*)&id;
    row = *((short*)c_id+1);
    col = *((short*)c_id);
}






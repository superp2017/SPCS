#include "twoshorttoid.h"

TwoShortToId::TwoShortToId(QObject *parent):
    QObject(parent)
{
}


/*!
 * \��ÿ����Ԫ����,��ֵ����,��ֵΪshort���ͣ�ת��Ϊһ��int���͵�id��
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
 *\ ��֪��Ԫ��id�ţ�id��Ϊint���ͣ�ת��Ϊ����short���͵���,�к�
 */
void TwoShortToId::IdToAddr(int id, short &row, short &col)
{
    char *c_id = (char*)&id;
    row = *((short*)c_id+1);
    col = *((short*)c_id);
}

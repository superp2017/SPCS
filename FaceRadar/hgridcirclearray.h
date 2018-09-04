#ifndef HGRIDCIRCLEARRAY_H
#define HGRIDCIRCLEARRAY_H
#include "harray.h"
#include<map>
#include<QString>
#include<vector>
#include <QDebug>
#include <QSettings>

#define PI  3.141592653
class HGridCircleArray : public HArray
{
public:
    HGridCircleArray(QString offset,QString path);
    virtual ~HGridCircleArray();
    void YScanning();                                              //Y��ɨ������
    void ArraySize (double D,int N,double R);                      //����������Χ
    std::map<int,QString>& EnsureCoordinate();                      //ȷ������
    void Creat_Array_Element_File();                              //������Ԫ�ļ�
    void  get_sb_se(double &sb,double &se);                         //����Sb,Se
    void  get_pb_pe(double &pb,double &pe);                         //����Pb,Pe
    double &get_Lx();                                                        //����LX��
private:
    double m_D;
    double m_N;
    double m_R;
    double Lx;
    double Ly;
    double Se1;
    double Sb1;
    double Pb;
    double Pe;
    double Sb;
    double Se;
    QString m_offset;
    int    m_num_in_line;
    QString m_path;
    std::map<int,QString>  m_radar_coordinate;
};

#endif // HGRIDCIRCLEARRAY_H

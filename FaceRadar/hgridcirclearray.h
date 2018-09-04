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
    void YScanning();                                              //Y向扫描点计算
    void ArraySize (double D,int N,double R);                      //重载天线阵范围
    std::map<int,QString>& EnsureCoordinate();                      //确定坐标
    void Creat_Array_Element_File();                              //生成阵元文件
    void  get_sb_se(double &sb,double &se);                         //返回Sb,Se
    void  get_pb_pe(double &pb,double &pe);                         //返回Pb,Pe
    double &get_Lx();                                                        //返回LX；
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

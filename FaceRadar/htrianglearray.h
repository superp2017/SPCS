#ifndef HTRIANGLEARRAY_H
#define HTRIANGLEARRAY_H
#include "harray.h"
#include <QDebug>
#include<QSettings>
#include<map>
#include<QString>
#include<vector>


class HTriangleArray : public HArray
{
public:
    HTriangleArray(QString offset,QString path);
    virtual ~HTriangleArray();
    void YScanning();                                                    //Y向扫描点计算
    void ArraySize(int Nx =0,int Ny =0,double Dx =0,double Dy = 0);      //天线阵范围
    std::map<int,QString>& EnsureCoordinate();                           //确定坐标
    void Creat_Array_Element_File();                                     //生成阵元文件
    void get_sb_se(double &sb,double &se);                               //返回Sb,Se
    void get_pb_pe(double &pb,double &pe);                               //返回Pb,Pe
    double &get_Lx();                                                    //返回LX；
private:
    double Lx;
    double Ly;
    double Se1;
    double Sb1;
    double m_Dx;
    double m_Dy;
    int m_Nx;
    int m_Ny;
    double Pb;
    double Pe;
    double Sb;
    double Se;
    QString m_offset;
    QString m_path;
    std::map<int,QString>  m_radar_coordinate;
};

#endif // HTRIANGLEARRAY_H

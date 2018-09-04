#ifndef HARRAY_H
#define HARRAY_H
#include <QObject>
#include <QString>
#include <vector>
#include <map>

/*!
 * \file harray.h
 */

/*!
 * \copyright Copyright (C), 2007-2013, Hollywell Electronic System Co.
 */

/*!
 * \author MP
 */

/*!
 * \version 1.0.0
 */

/*!
 * \date 2013-09-12
 */

/*!
 * \brief 阵列超类
 */

/*!
 *  阵列超类，完成天线的方位的确认，生成阵列映射文件
 *
 */

class HArray
{
public:
    HArray();
    virtual ~HArray()=0;
    void GenerateArrayMapFile();
    void ScanningRange(double Ly, double &Sb, double &Se);               //扫描架扫描范围
    void TestProbeGroup(double Lx,double &Pb,double &Pe);                //测试探头组计算
    void IsScanningOutRange(double &Sb, double &Se, double &left, double &right); //扫描是否越界
    void IsProbeOutRange(double &Lx,double &up, double &down);          //探头是否越界
    virtual void YScanning()=0;                                          //Y向扫描点计算
    virtual void ArraySize(int Nx ,int Ny,double Dx,double Dy);          //天线阵范围
    virtual void ArraySize (double D,int N,double R);                    //重载天线阵范围
    virtual void ArraySize(double Dx,double Dy,double R,bool isRect);    //重载天线阵范围
    virtual std::map<int,QString>& EnsureCoordinate()=0;                 //确定坐标
    virtual void Creat_Array_Element_File()=0;                           //生成阵元文件
    virtual void  get_sb_se(double &sb,double &se)=0;                    //返回Sb,Se
    virtual void  get_pb_pe(double &pb,double &pe)=0 ;                   //返回Pb,Pe
    virtual double &get_Lx()=0;                                           //返回LX；
};

#endif // HARRAY_H

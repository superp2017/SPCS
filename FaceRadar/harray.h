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
 * \brief ���г���
 */

/*!
 *  ���г��࣬������ߵķ�λ��ȷ�ϣ���������ӳ���ļ�
 *
 */

class HArray
{
public:
    HArray();
    virtual ~HArray()=0;
    void GenerateArrayMapFile();
    void ScanningRange(double Ly, double &Sb, double &Se);               //ɨ���ɨ�跶Χ
    void TestProbeGroup(double Lx,double &Pb,double &Pe);                //����̽ͷ�����
    void IsScanningOutRange(double &Sb, double &Se, double &left, double &right); //ɨ���Ƿ�Խ��
    void IsProbeOutRange(double &Lx,double &up, double &down);          //̽ͷ�Ƿ�Խ��
    virtual void YScanning()=0;                                          //Y��ɨ������
    virtual void ArraySize(int Nx ,int Ny,double Dx,double Dy);          //������Χ
    virtual void ArraySize (double D,int N,double R);                    //����������Χ
    virtual void ArraySize(double Dx,double Dy,double R,bool isRect);    //����������Χ
    virtual std::map<int,QString>& EnsureCoordinate()=0;                 //ȷ������
    virtual void Creat_Array_Element_File()=0;                           //������Ԫ�ļ�
    virtual void  get_sb_se(double &sb,double &se)=0;                    //����Sb,Se
    virtual void  get_pb_pe(double &pb,double &pe)=0 ;                   //����Pb,Pe
    virtual double &get_Lx()=0;                                           //����LX��
};

#endif // HARRAY_H

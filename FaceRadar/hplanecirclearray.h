#ifndef HPLANECIRCLEARRAY_H
#define HPLANECIRCLEARRAY_H
#include"harray.h"
#include<map>
#include<QString>
#include<vector>
#include<QSettings>
#include <QDebug>

class HPlaneCircleArray : public HArray
{
public:
    HPlaneCircleArray(QString offset,QString path);
    virtual ~HPlaneCircleArray();
    void YScanning();                                             //Y��ɨ������
    void ArraySize(double Dx, double Dy, double R, bool isRect);  //����������Χ
    std::map<int,QString>& EnsureCoordinate();                    //ȷ������
    void Creat_Array_Element_File();                              //������Ԫ�ļ�
    void  get_sb_se(double &sb,double &se);                       //����Sb,Se
    void  get_pb_pe(double &pb,double &pe);                       //����Pb,Pe
    double &get_Lx();                                                    //����LX��
    std::map<int, QString> &EnsureCoordinate_Rect();                      //���ηֲ�
    std::map<int, QString> &EnsureCoordinate_Trigle();                    //���Ƿֲ�
private:
    double m_Dx;
    double m_Dy;
    int m_Nx;
    int m_Ny;
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
    QString m_path;
    bool m_isRect;
    int id;
    std::map<int,QString>  m_radar_coordinate;
};

#endif // HPLANECIRCLEARRAY_H

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
    void YScanning();                                             //Y向扫描点计算
    void ArraySize(double Dx, double Dy, double R, bool isRect);  //重载天线阵范围
    std::map<int,QString>& EnsureCoordinate();                    //确定坐标
    void Creat_Array_Element_File();                              //生成阵元文件
    void  get_sb_se(double &sb,double &se);                       //返回Sb,Se
    void  get_pb_pe(double &pb,double &pe);                       //返回Pb,Pe
    double &get_Lx();                                                    //返回LX；
    std::map<int, QString> &EnsureCoordinate_Rect();                      //矩形分布
    std::map<int, QString> &EnsureCoordinate_Trigle();                    //三角分布
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

#include "hgridcirclearray.h"

HGridCircleArray::HGridCircleArray(QString offset, QString path)
{
    m_D = 0;m_N = 0; m_R = 0;
    Lx = 0;Ly = 0;Se1 = 0;
    Sb1 = 0;Pb = 0; Pe = 0;
    m_offset = offset;
    m_path = path;
}

HGridCircleArray::~HGridCircleArray()
{

}

void HGridCircleArray::YScanning()
{
    double sb2 = (int)(Sb/63);
    double sb3 = Sb/63 ;
    double se2 = (int)(Sb/63);
    double se3 = Se/63;
    if(sb2 == sb3)
        Sb1 = sb2;
    else
        Sb1 = sb2 - 1 ;
    if(se2 == se3)
        Se1 = se2;
    else
        Se1 = se2 + 1 ;
}

void HGridCircleArray::ArraySize(double D,int N,double R)
{
    m_D = D ;
    m_N = N ;
    m_R = R;
    Lx = 2*R ;
    Ly = 2*R ;
    m_num_in_line =(int)(R/D);
    this->ScanningRange(Ly,Sb,Se);
    this->TestProbeGroup(Lx,Pb,Pe);
}

//第M串上的第m个单元的坐标计算：
//X = cos(2*pi*(M-1)/N)*(m-1)*D
//Y = sin(2*pi*(M-1)/N)*(m-1)*D
//Z = 0

std::map<int, QString> &HGridCircleArray::EnsureCoordinate()
{
    int t_=0;
    for(int i=0;i<m_N;++i)
    {
        for(int j =0;j<m_num_in_line;++j)
        {
            int id = i*m_num_in_line +j+1-t_;
            double x_c = cos(2*PI*i/m_N)*j*m_D;
            double y_c = sin(2*PI*i/m_N)*j*m_D;
            double z_c =    0;
            if(i >0)
            {
                if(x_c==0&&y_c==0)
                {
                    t_+=1;
                    continue;
                }
            }
            QString m_coordinate = QString("%1,%2,%3").arg(x_c).arg(y_c).arg(z_c);
            if(!m_radar_coordinate.count(id))
                m_radar_coordinate[id] = m_coordinate;
        }
    }
    return m_radar_coordinate;
}

void HGridCircleArray::Creat_Array_Element_File()
{
  //  QString m_path = "./config/coordinate.ini";
    QSettings settings(m_path,QSettings::IniFormat);
    settings.beginGroup("COORDINATE");
    std::map<int,QString> ::iterator iter = m_radar_coordinate.begin();
    while(iter != m_radar_coordinate.end())
    {
        QString key = QString("%1").arg((*iter).first);
        settings.setValue(key,(*iter).second);
        ++iter;
    }
    settings.endGroup();
    settings.beginGroup("OFFSET");
    settings.setValue("offset",m_offset);
    settings.endGroup();
}

void HGridCircleArray::get_sb_se(double &sb, double &se)
{
    sb= Sb;
    se= Se;
}

void HGridCircleArray::get_pb_pe(double &pb, double &pe)
{
    pb = Pb;
    pe = Pe;
}

double &HGridCircleArray::get_Lx()
{
    return Lx;
}


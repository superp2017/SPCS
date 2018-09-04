#include "hplanecirclearray.h"

HPlaneCircleArray::HPlaneCircleArray(QString offset, QString path)
{
    m_Dx = 0;m_Dy = 0; m_R = 0;
    Lx = 0;Ly = 0;Se1 = 0;
    Sb1 = 0;Pb = 0; Pe = 0;
    m_offset = offset;
    m_path = path ;
    m_isRect = true;
    id= 0;
}

HPlaneCircleArray::~HPlaneCircleArray()
{
}

void HPlaneCircleArray::YScanning()
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

void HPlaneCircleArray::ArraySize(double Dx,double Dy,double R,bool isRect)
{
    m_Dx = Dx ;
    m_Dy = Dy ;
    m_R = R;
    m_Nx = (2*R)/Dx;
    m_Ny = (2*R)/Dy;
    Lx = (m_Nx-1)*Dx;
    Ly = (m_Ny-1)*Dy;
    this->ScanningRange(Ly,Sb,Se);
    this->TestProbeGroup(Lx,Pb,Pe);
    m_isRect = isRect;
}

std::map<int, QString> &HPlaneCircleArray::EnsureCoordinate()
{
    m_radar_coordinate.clear();
    if(m_isRect)
        return EnsureCoordinate_Rect();
    else
        return EnsureCoordinate_Trigle();
}

void HPlaneCircleArray::Creat_Array_Element_File()
{
    // QString m_path = "./config/coordinate.ini";
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

void HPlaneCircleArray::get_sb_se(double &sb, double &se)
{
    sb =  Sb;
    se = Se;
}

void HPlaneCircleArray::get_pb_pe(double &pb, double &pe)
{
    pb = Pb;
    pe = Pe;
}

double &HPlaneCircleArray::get_Lx()
{
    return Lx;
}

std::map<int, QString> &HPlaneCircleArray::EnsureCoordinate_Rect()
{
    double x_c = -Lx/2;
    id =0;
    for(int i=0;i<m_Nx;++i)
    {
        double y_c = Sb;
        for(int j =0;j<m_Ny;++j)
        {
            QString m_coordinate = QString("%1,%2,%3").arg(x_c).arg(y_c).arg(0);
            double far = sqrt(x_c*x_c+y_c*y_c);
            if(far < m_R)
            {
                ++id;
                if(!m_radar_coordinate.count(id))
                    m_radar_coordinate[id] = m_coordinate;
            }
            y_c += m_Dy;
        }
        x_c += m_Dx;
    }
    return m_radar_coordinate;
}

std::map<int, QString> &HPlaneCircleArray::EnsureCoordinate_Trigle()
{
    double x_c = -Lx/2;
    double y_c;
    id =0;
    for(int i=0;i<m_Nx;++i)
    {
        if(i%2 == 0)
            y_c = Sb;
        else
            y_c = Sb +0.5*m_Dy;
        for(int j =0;j<m_Ny;++j)
        {
            QString m_coordinate = QString("%1,%2,%3").arg(x_c).arg(y_c).arg(0);
            double far = sqrt(x_c*x_c+y_c*y_c);
            if(far < m_R)
            {
                ++id;
                if(!m_radar_coordinate.count(id))
                    m_radar_coordinate[id] = m_coordinate;
            }
            y_c += m_Dy;
        }
        x_c += m_Dx;
    }
    return m_radar_coordinate;
}



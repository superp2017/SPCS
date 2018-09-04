#include "hrectanglearray.h"

HRectangleArray::HRectangleArray(QString offset, QString path)
{
    Lx = 0;Ly = 0; Se1 = 0;Sb1 = 0;
    m_Dx = 0; m_Dy = 0;m_Nx= 0;
    m_Ny = 0;Pb = 0; Pe = 0;
    m_offset = offset;
    m_path = path;
}

HRectangleArray::~HRectangleArray()
{

}

void HRectangleArray::YScanning()
{
    double sb2 = (int)((Sb + 31.5)/63);
    double sb3 = (Sb + 31.5)/63 ;
    double se2 = (int)((Se - 31.5)/63);
    double se3 = (Sb - 31.5)/63;
    if(sb2 == sb3)
        Sb1 = sb2;
    else
        Sb1 = sb2 - 1 ;
    if(se2 == se3)
        Se1 = se2;
    else
        Se1 = se2 + 1 ;
}

void HRectangleArray::ArraySize(int Nx, int Ny, double Dx, double Dy)
{
    m_Nx = Nx;
    m_Ny = Ny;
    m_Dx = Dx;
    m_Dy = Dy;
    Lx = (Nx-1)*Dx;
    Ly = (Ny-1)*Dy;
    this->ScanningRange(Ly,Sb,Se);
    this->TestProbeGroup(Lx,Pb,Pe);
}

std::map<int, QString> &HRectangleArray::EnsureCoordinate()
{
    double x_c = -Lx/2;
    for(int i=0;i<m_Nx;++i)
    {
        double y_c = Sb;
        for(int j =0;j<m_Ny;++j)
        {
            int id = i*m_Nx +j+1;
            QString m_coordinate = QString("%1,%2,%3").arg(x_c).arg(y_c).arg(0);
            if(!m_radar_coordinate.count(id))
                m_radar_coordinate[id] = m_coordinate;
            y_c += m_Dy;
        }
        x_c += m_Dx;
    }
    return m_radar_coordinate;
}

void HRectangleArray::Creat_Array_Element_File()
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

void HRectangleArray::get_sb_se(double &sb, double &se)
{
    sb = Sb;
    se = Se;
}

void HRectangleArray::get_pb_pe(double &pb, double &pe)
{
    pb = Pb;
    pe = Pe;
}

double &HRectangleArray::get_Lx()
{
    return Lx;
}



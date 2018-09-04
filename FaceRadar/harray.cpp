#include "harray.h"

HArray::HArray()
{
}

HArray::~HArray()
{

}



void HArray::ScanningRange(double Ly, double &Sb, double &Se)
{
    Sb = -Ly/2;
    Se = Ly/2;
}

void HArray::TestProbeGroup(double Lx, double &Pb, double &Pe)
{
    Pb = (int)((-Lx/2)/105) + 9;
    Pe = (int)((Lx/2)/105)  + 9;
}

void HArray::IsScanningOutRange(double &Sb, double &Se, double &left, double &right)
{
//    if( Sb <= -750 || Se>= 750)
//        return true ;
//    else
//        return false;
    left = -750 -Sb;
    right = Se -750;
}

void HArray::IsProbeOutRange(double &Lx, double &up, double &down)
{
//    if(Pb < 1 || Pe > 16)
//        return true;
//    else
//        return false;
    up   = Lx/2 - 8*105;
    down =  -8*105  + Lx/2 ;
}


void HArray::ArraySize(int Nx, int Ny, double Dx, double Dy)
{
}

void HArray::ArraySize(double D, int N, double R)
{
}

void HArray::ArraySize(double Dx, double Dy, double R,bool isRect)
{
}

#ifndef OPERACMD_H
#define OPERACMD_H

#include "hserialport.h"
#include "sweepshelf_global.h"
using namespace std;
class OperaCmd
{
public:
    OperaCmd();
    bool   S_OpenCOM(QString com);
    void   S_CloseCOM();
    void   S_serveon();
    void   S_serveoff();
    double S_position();
    bool   S_movedone();
    void   S_clearwarn();
    bool   M_origin();
    bool   M_move(double distance);
    void   S_SetMoveSpeed(MOVESPEESD speed);
    double S_Calc_PUU(double curp,double dis);
    void   initdata();
private:
    HSerialPort               m_SerialPort;
    std::vector<double>       m_segment_point;
    std::map<int,double>      m_effic;
};

#endif // OPERACMD_H

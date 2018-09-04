#ifndef HSERIALPORT_H
#define HSERIALPORT_H

#include <QSerialPort>
#include <string>
#include <vector>
#include <QDebug>
#include "Windows.h"

using namespace std;

#define NOPOSITION      20000
#define REDEBUFFERSIZE  8192

class HSerialPort
{
public:
    HSerialPort();
    bool    f_OpenSerialPort(QString name);
    void    f_CloseSerialPort();
    void    f_Send(char *command, int len);
    int     f_GetReadbuffer(uchar *&buf);
    int     get_readbuf(uchar * &buf);
protected:
    int     f_hexToStr(uchar *pHex, qint64 size, uchar *&buf);
    int     f_Str2Hex(const char *str, int len, vector<uchar> &buf);
    int     F_HexChar(char c);
    int     f_Str2Hexcode(char *cmdcode , int len, uchar * &sendbuffer);
    void    f_CrcCode(vector<uchar> &Origin_data, uchar &lowbyte, uchar &highbyte);

private:
    uchar        m_readBuffer[REDEBUFFERSIZE];
    uchar        m_rece_Right;
    qint64       m_readreallysize;
    QSerialPort  *m_serialPort;
    
};

#endif // HSERIALPORT_H

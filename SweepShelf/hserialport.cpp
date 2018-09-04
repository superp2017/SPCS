#include "hserialport.h"

HSerialPort::HSerialPort()
{
    m_serialPort = 0;
    m_readreallysize = 0;
}

bool HSerialPort::f_OpenSerialPort(QString name)
{
    m_serialPort = new QSerialPort(name);
    if(!m_serialPort->open(QSerialPort::ReadWrite))
    {
        qDebug() << "open serialport failed!";
        return false;
    }
    if (!m_serialPort->setBaudRate(QSerialPort::Baud9600)) {
        qDebug() << QString("Can't set baud rate 9600 baud to port %1, error code %2")
                    .arg("portName").arg(m_serialPort->error());
        return false;
    }

    if (!m_serialPort->setDataBits(QSerialPort::Data8)) {
        qDebug() << QString("Can't set 8 data bits to port %1, error code %2")
                    .arg("portName").arg(m_serialPort->error());
        return false;
    }

    if (!m_serialPort->setParity(QSerialPort::NoParity)) {
        qDebug() << QString("Can't set no patity to port %1, error code %2")
                    .arg("portName").arg(m_serialPort->error());
        return false;
    }

    if (!m_serialPort->setStopBits(QSerialPort::OneStop)) {
        qDebug() << QString("Can't set 1 stop bit to port %1, error code %2")
                    .arg("portName").arg(m_serialPort->error());
        return false;
    }

    if (!m_serialPort->setFlowControl(QSerialPort::NoFlowControl)) {
        qDebug() << QString("Can't set no flow control to port %1, error code %2")
                    .arg("portName").arg(m_serialPort->error());
        return false;
    }
    return true;
}

void HSerialPort::f_CloseSerialPort()
{
    if(m_serialPort)
        m_serialPort->close();
}

void HSerialPort::f_Send(char *command, int len)
{
    uchar *sendbuffer=0 ;
    int size = f_Str2Hexcode(command,len,sendbuffer);
    ::Sleep(20);

    m_serialPort->flush();
    m_serialPort->clear(QSerialPort::Input);
    m_serialPort->write(reinterpret_cast<char *>(sendbuffer), size);
    m_serialPort->flush();

    if (m_serialPort->waitForBytesWritten(1000))
    {
        if (m_serialPort->waitForReadyRead(1000))
        {
            QByteArray responseData = m_serialPort->readAll();
            while (m_serialPort->waitForReadyRead(10))
                responseData += m_serialPort->readAll();

            memcpy(m_readBuffer, responseData.data(), responseData.size());
            m_readreallysize = responseData.size();
        } else
        {
            qDebug() << QString("Wait read response timeout ..1");
        }
    } else
    {
        qDebug() << QString("Wait write request timeout..2");
    }
}


int HSerialPort::f_GetReadbuffer(uchar *&buf)
{
    return f_hexToStr(m_readBuffer, m_readreallysize,buf);
}

int HSerialPort::get_readbuf(uchar *&buf)
{
    buf = m_readBuffer;
    return m_readreallysize;
}

int HSerialPort::f_hexToStr(uchar *pHex, qint64 size, uchar *&buf)
{
    buf = new uchar[1024];
    int bufsize = 0;
    for(qint64 iIndex = 0; iIndex < size; iIndex++)
    {
        unsigned char iValueHigh = pHex[iIndex] / 16;
        switch(iValueHigh)
        {
        case 0:   buf[bufsize] =  '0'; bufsize++; break;
        case 1:   buf[bufsize] =  '1' ;bufsize++; break;
        case 2:   buf[bufsize] =  '2'; bufsize++; break;
        case 3:   buf[bufsize] =  '3'; bufsize++; break;
        case 4:   buf[bufsize] =  '4'; bufsize++; break;
        case 5:   buf[bufsize] =  '5'; bufsize++; break;
        case 6:   buf[bufsize] =  '6'; bufsize++; break;
        case 7:   buf[bufsize] =  '7'; bufsize++; break;
        case 8:   buf[bufsize] =  '8'; bufsize++; break;
        case 9:   buf[bufsize] =  '9'; bufsize++; break;
        case 10:  buf[bufsize] =  'A'; bufsize++; break;
        case 11:  buf[bufsize] =  'B'; bufsize++; break;
        case 12:  buf[bufsize] =  'C'; bufsize++; break;
        case 13:  buf[bufsize] =  'D'; bufsize++; break;
        case 14:  buf[bufsize] =  'E'; bufsize++; break;
        case 15:  buf[bufsize] =  'F'; bufsize++; break;
        }

        uchar iValueLow = pHex[iIndex] % 16;
        switch(iValueLow)
        {
        case 0:   buf[bufsize] =  '0'; bufsize++; break;
        case 1:   buf[bufsize] =  '1' ;bufsize++; break;
        case 2:   buf[bufsize] =  '2'; bufsize++; break;
        case 3:   buf[bufsize] =  '3'; bufsize++; break;
        case 4:   buf[bufsize] =  '4'; bufsize++; break;
        case 5:   buf[bufsize] =  '5'; bufsize++; break;
        case 6:   buf[bufsize] =  '6'; bufsize++; break;
        case 7:   buf[bufsize] =  '7'; bufsize++; break;
        case 8:   buf[bufsize] =  '8'; bufsize++; break;
        case 9:   buf[bufsize] =  '9'; bufsize++; break;
        case 10:  buf[bufsize] =  'A'; bufsize++; break;
        case 11:  buf[bufsize] =  'B'; bufsize++; break;
        case 12:  buf[bufsize] =  'C'; bufsize++; break;
        case 13:  buf[bufsize] =  'D'; bufsize++; break;
        case 14:  buf[bufsize] =  'E'; bufsize++; break;
        case 15:  buf[bufsize] =  'F'; bufsize++; break;
        }
    }
    return bufsize;
}

int HSerialPort::f_Str2Hexcode( char *cmdcode, int len, uchar *&sendbuffer)
{
    int ls_len = len / 2;
    sendbuffer = new uchar[ls_len+2];
    vector<uchar> command(ls_len);

    f_Str2Hex(cmdcode,len,command);

    for(int i = 0;i < ls_len;i++)
    {
        sendbuffer[i] = command[i];
    }

    uchar send_crc_code[2];
    f_CrcCode(command,send_crc_code[0],send_crc_code[1]);

    sendbuffer[ls_len]   = send_crc_code[0];
    sendbuffer[ls_len+1] = send_crc_code[1];
    return ls_len+2;
}



int HSerialPort::f_Str2Hex(const char *str, int len, vector<uchar> &buf)
{
    int heigh, low;
    int rlen = 0;
    for (int i = 0; i < len; )
    {
        unsigned char cur_l, cur_h = str[i];

        if (cur_h ==32)
        {
            i++;
            continue;
        }
        i++;
        if (i >= len)
            break;

        cur_l = str[i];
        heigh = F_HexChar(cur_h);
        low    =F_HexChar(cur_l);

        if ((heigh == 16) || (low == 16))
            break;
        else
            heigh = heigh * 16 + low;

        i++;
        buf[rlen] = (unsigned char)heigh;
        rlen++;
    }
    return rlen;
}

int HSerialPort::F_HexChar(char c)
{
    if ((c >= '0') && (c <= '9'))
        return c - 0x30;
    else if ((c >= 'A') && (c <= 'F'))
        return c - 'A' + 10;
    else if ((c >= 'a') && (c <= 'f'))
        return c - 'a' + 10;
    else
        return 0x10;
}


void HSerialPort::f_CrcCode(vector<uchar> &Origin_data, uchar &lowbyte, uchar &highbyte)
{
    int i = 0;
    unsigned int reg_crc = 0xFFFF;
    int size = Origin_data.size();
    while(size--)
    {
        reg_crc ^= Origin_data[i++];
        for(int j=0;j<8;j++)
        {
            if(reg_crc&0x01)
                reg_crc = (reg_crc >>1 )^0xA001;
            else
                reg_crc = (reg_crc >> 1);
        }
    }

    highbyte = reg_crc / 256;
    lowbyte = reg_crc % 256;
}

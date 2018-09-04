#include "afgadapter.h"
#include <QDebug>
#include <Windows.h>
#include "_global.h"
#define BUFFER_SIZE 102400

AFGAdapter::AFGAdapter() :
    m_serial_port(AFG_COM)
{
    m_buff = new char[BUFFER_SIZE];
    m_source = 1;
}

AFGAdapter::~AFGAdapter()
{
    delete [] m_buff;
}

void AFGAdapter::switch_source(int source)
{
    m_source = source;
}

bool AFGAdapter::connect()
{
    m_serial_port.setBaudRate(QSerialPort::Baud9600);
    m_serial_port.setStopBits(QSerialPort::OneStop);
    m_serial_port.setDataBits(QSerialPort::Data8);
    m_serial_port.setParity(QSerialPort::NoParity);
    m_serial_port.setFlowControl(QSerialPort::NoFlowControl);
    if(!m_serial_port.open(QIODevice::ReadWrite))
    {
        qDebug() << "serial port open failed!";
        return false;
    }
    ::Sleep(5000);
    return true;
}

void AFGAdapter::idn()
{
    m_serial_port.write("*IDN?\n", strlen("*IDN?\n"));
    while(m_serial_port.waitForReadyRead(1000))
    {
        qDebug() << "waiting for read...";
    }
    qDebug() << m_serial_port.readAll();
    ::Sleep(5000);
}

void AFGAdapter::turn_on()
{
    sprintf(m_buff, "OUTP%d ON\n", m_source);
    wait_for_write(m_buff);
}

void AFGAdapter::turn_off()
{
    sprintf(m_buff, "OUTP%d OFF\n", m_source);
    wait_for_write(m_buff);
}

void AFGAdapter::set_square()
{
    sprintf(m_buff, "SOURce%d:APPLy:SQUare\n", m_source);
    wait_for_write(m_buff);
}

void AFGAdapter::set_ext_trigger()
{
    sprintf(m_buff, "SOURce%d:BURSt:TRIGger:SOURce EXT\n", m_source);
    wait_for_write(m_buff);
}

void AFGAdapter::set_int_trigger()
{
    sprintf(m_buff, "SOURce%d:BURSt:TRIGger:SOURce INT\n", m_source);
    wait_for_write(m_buff);
}

void AFGAdapter::set_freq(double freq)
{
    sprintf(m_buff, "SOURce%d:FREQuency %fHz\n", m_source, freq);
    wait_for_write(m_buff);
}

void AFGAdapter::set_duty_dcyc(double duty)
{
    sprintf(m_buff, "SOUR%d:SQU:DCYC %f\n", m_source, duty);
    wait_for_write(m_buff);
}


void AFGAdapter::set_trigger_delay(double delay)
{
    sprintf(m_buff, "SOURce%d:BURSt:TRIGger:DELay %f\n", m_source, delay);
    wait_for_write(m_buff);
}

void AFGAdapter::set_phase(double degree)
{
    sprintf(m_buff, "SOURce%d:BURSt:PHASe %f\n", m_source, degree);
    wait_for_write(m_buff);
}

void AFGAdapter::wait_for_write(char *buff)
{
    m_serial_port.write(m_buff, strlen(buff));
    while(m_serial_port.waitForBytesWritten(1000))
    {
        qDebug() << "waiting for write...";
    }
    ::Sleep(5000);
}

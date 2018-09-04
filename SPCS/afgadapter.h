#ifndef AFGADAPTER_H
#define AFGADAPTER_H

#include <QObject>
#include <QtSerialPort/QSerialPort>


enum RF{RISE, FALL};
/*!
 * \brief The AFGAdapter class
 * 配置R&S的脉冲（函数信号发生器）
 */
class AFGAdapter
{
public:
    explicit AFGAdapter();
    ~AFGAdapter();

public:
    void switch_source(int source);
    bool connect();
    void idn();
    void turn_on();
    void turn_off();
    void set_square();
    void set_ext_trigger();
    void set_int_trigger();
    void set_freq(double freq);
    void set_duty_dcyc(double duty);
    void set_trigger_delay(double delay);
    void set_phase(double degree);

private:
    void wait_for_write(char *buff);
private:
    QSerialPort     m_serial_port;
    char*           m_buff;
    int             m_source;
};

#endif // AFGADAPTER_H

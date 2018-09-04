#ifndef ELESWITCH_H
#define ELESWITCH_H

#include <QObject>
#include <vector>

/*!
 * \brief The EleSwitch class
 * 电子开关的一个控制类
 */
class EleSwitch : public QObject
{
    Q_OBJECT
protected:
    explicit EleSwitch(QObject *parent = 0);
    ~EleSwitch();
public:
    static EleSwitch *instance()
    {
        static EleSwitch *switch_ = new EleSwitch();
        return switch_;
    }
    static void destory()
    {
        delete instance();
    }
    void reset();
    bool &get_status();
    void set_status(bool isopen);
public slots:
    void open_all();
    void close_all();

private:
    bool        m_isopen;
    
};

#endif // ELESWITCH_H

#ifndef ENV_CONFIG_H
#define ENV_CONFIG_H

#include <QObject>

/*!
 * \brief The ENV_config class
 * 用来配置失网类型 IP等信息
 */
class ENV_config : public QObject
{
    Q_OBJECT
public:
protected:
    explicit ENV_config(QObject *parent = 0);

public:
    static ENV_config* instance()
    {
        static ENV_config* env = new ENV_config();
        return env;
    }

    static void destroy()
    {
        delete instance();
    }

    QString get_r_s_ip() const           {return m_rs_ip;}
    QString get_Aglient_ip() const       {return m_Aglient_ip;}
    bool use_s11s22()                    {return m_use_s11_s22;}
    bool collect_s11()                   {return m_collect_s11;}
    bool real_cal()                      {return m_real_cal;}
    
protected:
    void init();
signals:
    
public slots:
    
private:
    QString             m_Aglient_ip;
    QString             m_rs_ip;
    bool                m_collect_s11;
    bool                m_use_s11_s22;
    bool                m_real_cal;
};

#endif // ENV_CONFIG_H

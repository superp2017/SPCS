#ifndef NIPARSER_H
#define NIPARSER_H

#include <QObject>
#include <map>
#include <vector>
#include <complex>


class NIParser : public QObject
{
    Q_OBJECT
protected:
    explicit NIParser(QObject *parent = 0);

public:
    typedef std::map<int, std::map<int, float> >   MMD;

    static NIParser* instance()
    {
        static NIParser *Np = new NIParser;
        return Np;
    }

    static void destroy()
    {
        delete instance();
    }

    void parse(const QString &path);
    int get_N(){return m_N;}
    int get_N_num(){return m_N_num;}
    float get_I(){return m_I;}
    float get_I_step(){return m_I_step;}
    int get_I_num(){return m_I_num;}
    int get_S_min(){return m_S_min;}
    int get_S_max(){return m_S_max;}

    float get_N_data(int x, int y){return m_mmd[x][y];}
    const MMD* get_MMD(){return &m_mmd;}

    std::vector<std::vector<std::complex<double> > >& get_S1();
    std::vector<std::vector<std::complex<double> > >& get_S2();



signals:
    
public slots:

private:
    int         m_N;
    int         m_N_num;
    float       m_I;
    float       m_I_step;
    int         m_I_num;
    MMD         m_mmd;
    int         m_S_min;
    int         m_S_max;
    std::vector<std::vector<std::complex<double> > > m_res_S1;
    std::vector<std::vector<std::complex<double> > > m_res_S2;
};

#endif // NIPARSER_H

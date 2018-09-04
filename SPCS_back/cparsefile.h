#ifndef CPARSEFILE_H
#define CPARSEFILE_H

#include <QObject>
#include <QSettings>
#include <map>
#include <QString>
#include<vector>

/*!
 * \brief The CParsefile class
 *  解析声望直接生成的.s2p文件
 *
 */
class CParsefile : public QObject
{
    Q_OBJECT
public:
    explicit CParsefile(QObject *parent = 0);
    void   load_cal_data(QString p_path,QString pname);
    std::map<int,std::map<QString,std::pair<double,double> > > &get_cal_s11() {return m_s11_cal;}
    std::map<int,std::map<QString,std::pair<double,double> > > &get_cal_s12() {return m_s12_cal;}
    std::map<int,std::map<QString,std::pair<double,double> > > &get_cal_s21() {return m_s21_cal;}
    std::map<int,std::map<QString,std::pair<double,double> > > &get_cal_s22() {return m_s22_cal;}
    std::vector<QString>                                       &get_ferq_key(){return m_freq_key;}


    void combine_data(std::map<QString,std::map<QString, std::vector<std::pair<QString,QString> > > > &p_data,\
                      std::vector<QString>& m_freq,QString path ,bool issave = false);

    void get_s2p(std::map<QString,std::pair<QString,QString> > &p_data,\
                 std::vector<QString> &m_freq,QString path,bool issave = true);
protected:

    double genLinMag(double real, double imag);
    double genPhase(double real, double imag);
    double gendB(double magn);

private:
    
    std::map<int,std::map<QString,std::pair<double,double> > >  m_s11_cal;
    std::map<int,std::map<QString,std::pair<double,double> > >  m_s12_cal;
    std::map<int,std::map<QString,std::pair<double,double> > >  m_s21_cal;
    std::map<int,std::map<QString,std::pair<double,double> > >  m_s22_cal;
    std::vector<QString>                                        m_freq_key;
};

#endif // CPARSEFILE_H

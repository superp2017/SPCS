#ifndef DATAMANAGE_H
#define DATAMANAGE_H

#include <map>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "_global.h"
#include <qmath.h>

#define FREQUENCE   "Freq "
using namespace CVTS;


/*!
 * \brief The DataManage class
 * 用于保存和读取 Task_Res Task_Cmp 文件，即保存的.org和.mp文件
 *
 */
class DataManage
{
public:
    DataManage();
    void SaveToFile(std::map<QString, std::map<int, QString > > &pdata\
                    ,std::vector<QString> &p_freq,QString p_path);

    void SaveToFile(Task_Cmp &p_cmp,std::vector<QString> &p_freq, QString p_path);

    void SaveToFile_dB(std::map<QString, std::map<int, QString> > &pdata,\
                       std::vector<QString> &p_freq, QString p_path);

    void SavePhase1(std::map<QString,std::map<int,double> > p_data,\
                    std::vector<QString> &p_freq,QString path);

    std::map<QString,std::map<int,double> > &ReadformPhase1(QString path);

    void clear_buf();

    Task_Cmp ReadFromFile_cmp(QString p_path);
    Task_Res ReadFromFile_org(QString &p_path);
    std::vector<Curvedata>& ReadMAXFile(QString &p_path, \
                                        std::vector<QString> &p_freq, \
                                            bool ismp);
protected:
    void StrToDouble(std::map<QString, std::map<int, QString > > &pdata,\
                     Task_Cmp &cmp,bool isdb);

    double genMagn_w(double real, double imag);
    double genMagn(double real, double imag);
    double genPhase(double real, double imag);
private:
    Task_Cmp                                  m_result_cmp;
    Task_Res                                  m_resule_res;
    std::vector<Curvedata>                    m_curves;
    std::map<QString, std::map<int, double> > m_phase_1;
    bool                                      m_once;
};

#endif // DATAMANAGE_H

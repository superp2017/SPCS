#ifndef M_PARSECURVEDATA_H
#define M_PARSECURVEDATA_H

#include <QObject>
#include <QVector>
#include <map>
#include <QFile>
#include "_global.h"
#include <QMessageBox>
#include <QDebug>
#include <QSettings>
using  namespace CVTS ;

class Compare_id
{
public:
    bool operator()(const QString &L_, const QString &R_)
    {
        double ls_R = R_.toDouble();
        double ls_L = L_.toDouble();
        return ls_L < ls_R;
    }
};


/*!
 * \brief The M_ParseCurveData class
 * 数据解析类，用来解析导出来曲线文件.curve
 */
class M_ParseCurveData : public QObject
{
    Q_OBJECT
protected:
    explicit M_ParseCurveData(QObject *parent = 0);
    ~M_ParseCurveData();

public:
    static M_ParseCurveData *instance()
    {
        static M_ParseCurveData *phase = new M_ParseCurveData();
        return phase;
    }
    static void destory()
    {
        delete instance();
    }

    void parse(QString p_path, bool isdb, bool is360);
    void gen_file(QString &p_path, Curvedata &p_data);
    void gen_list(QString &filename,std::map<QString,QString>&p_filelist);
    Curvedata& get_curve_data();
signals:
protected:
    void clean();
private:
    std::map<QString, std::map<int, std::vector<QString> > >    m_curve_map;
    Curvedata                                                   m_curve_data;
};

#endif // M_PARSECURVEDATA_H

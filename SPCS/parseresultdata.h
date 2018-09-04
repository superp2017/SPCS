#ifndef PARSERESULTDATA_H
#define PARSERESULTDATA_H

#include <QObject>
#include <QString>
#include <vector>
#include <map>
#include "_global.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>

using namespace  CVTS;

#define FREQUENCE   "Freq "


/*!
 * \brief The ParseResultData class
 *  文件的读存，目前没有使用
 */
class ParseResultData : public QObject
{
    Q_OBJECT
protected:
    explicit ParseResultData(QObject *parent = 0);
    ~ParseResultData();
public:
    static ParseResultData *instance()
    {
        static ParseResultData * data = new ParseResultData();
        return data;
    }
    static void destory()
    {
        delete instance();
    }
    Task_Cmp &Parse(QString p_path);
    void Save(QString p_path,Task_Cmp p_cmp);
signals:
    
public slots:
private:
    Task_Cmp            m_result_map;
};

#endif // PARSERESULTDATA_H

#ifndef CONFIGEREXCEL_H
#define CONFIGEREXCEL_H

#include "_global.h"
#include <QObject>
#include <QMessageBox>
#include "libxl.h"

using namespace CVTS;

#define  REPORT_SUCCEED  QMessageBox::information(NULL,\
    CVTS::GBKToUnicode::toUnicode("提示"),CVTS::GBKToUnicode::toUnicode("出表成功"));

#define  FILE_IS_OPEN  QMessageBox::information(NULL,\
    CVTS::GBKToUnicode::toUnicode("提示"),CVTS::GBKToUnicode::toUnicode("请关闭已打开的文件"));

using namespace libxl;
/*!
 * \brief The ConfigerExcel class
 *  校准文件导出到excle
 */
class ConfigerExcel : public QObject
{
    Q_OBJECT
public:
    explicit ConfigerExcel(QObject *parent = 0);
    void    Export_Excel(QString Path, Task_Cmp &p_CmpData, std::vector<QString> &p_freq,std::vector<int> &p_id);
signals:
    
private:
    
};

#endif // CONFIGEREXCEL_H

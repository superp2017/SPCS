#ifndef CONFIGEREXCEL_H
#define CONFIGEREXCEL_H

#include "_global.h"
#include <QObject>
#include <QMessageBox>
#include "libxl.h"

using namespace CVTS;

#define  REPORT_SUCCEED  QMessageBox::information(NULL,\
    CVTS::GBKToUnicode::toUnicode("��ʾ"),CVTS::GBKToUnicode::toUnicode("����ɹ�"));

#define  FILE_IS_OPEN  QMessageBox::information(NULL,\
    CVTS::GBKToUnicode::toUnicode("��ʾ"),CVTS::GBKToUnicode::toUnicode("��ر��Ѵ򿪵��ļ�"));

using namespace libxl;
/*!
 * \brief The ConfigerExcel class
 *  У׼�ļ�������excle
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

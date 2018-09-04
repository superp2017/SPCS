#ifndef COMBINETOOLS_H
#define COMBINETOOLS_H

#include <QWidget>
#include "cparsefile.h"
#include "_global.h"

namespace Ui {
class CombineTools;
}
/*!
 * \brief The CombineTools class
 * 数据合并界面
 */
class CombineTools : public QWidget
{
    Q_OBJECT
    
public:
    explicit CombineTools(QWidget *parent = 0);
    ~CombineTools();
protected:
   void init_tablewidget();
   void add_item(QString path);
    
private slots:
   void on_pushButton_combine_clicked();

   void on_pushButton_seclect_clicked();

   void on_pushButton_delall_clicked();

   void on_pushButton_del_clicked();

   void on_pushButton_add_clicked();

private:
    Ui::CombineTools *ui;
    CParsefile      m_parse;

};

#endif // COMBINETOOLS_H

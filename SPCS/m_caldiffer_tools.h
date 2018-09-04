#ifndef M_CALDIFFER_TOOLS_H
#define M_CALDIFFER_TOOLS_H

#include <QWidget>
#include <QHBoxLayout>
#include <QHBoxLayout>
#include "stableplotview.h"
#include "caldiffercontrolpane.h"
#include "cparsefile.h"

/*!
 * \brief The M_CalDiffer_tools class
 *
 * 数据比较类，在工具菜单栏下
 */

class M_CalDiffer_tools : public QWidget
{
    Q_OBJECT
public:
    explicit M_CalDiffer_tools(QWidget *parent = 0);
    
signals:
    
public slots:
    void compare(QString path1, QString path2);
    void ParseFile(QString path, std::map<QString,std::pair<double,double> > &pdata, \
                   std::vector<QString> &p_freqs, \
                   bool save =false);
    void add_curve(QString path);
    void add_s2p(QString path);
    void clear_view();
private:
    QHBoxLayout                                 m_layout;
    StablePlotView                              m_view;
    CalDifferControlPane                        m_pane;
    CParsefile                                  m_parse;
};

#endif // M_CALDIFFER_TOOLS_H

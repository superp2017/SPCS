#ifndef M_STABLETOOLS_H
#define M_STABLETOOLS_H

#include <QWidget>
#include "stablecontrolpane.h"
#include <QHBoxLayout>
#include "stableplotview.h"


/*!
 * \brief The M_StableTools class
 * 稳定性比较类，工具菜单下的稳定性比较
 *
 */
class M_StableTools : public QWidget
{
    Q_OBJECT
public:
    explicit M_StableTools(QWidget *parent = 0);
    void clear_data();
    void reset_view();
    void reset();
signals:
    
public slots:
    void CheckoutData(QString freq,QString type,bool isto0);
    void LoadData(QString path);
private:
    QHBoxLayout                                 m_layout;
    StablePlotView                              m_view;
    StableControlPane                           m_pane;
    std::set<QString>                           m_freqs;
    QString                                     m_path;
    std::map<QString,std::vector<std::pair<double,double> > > m_s11;
    std::map<QString,std::vector<std::pair<double,double> > > m_s21;
    std::map<QString,std::vector<std::pair<double,double> > > m_s12;
    std::map<QString,std::vector<std::pair<double,double> > > m_s22;
};

#endif // M_STABLETOOLS_H

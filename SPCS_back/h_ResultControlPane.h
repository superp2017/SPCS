#ifndef H_RESULTCONTROLPANE_H
#define H_RESULTCONTROLPANE_H

#include <QWidget>
#include <QLabel>
#include <QGroupBox>
#include <QGridLayout>
#include <QRadioButton>
#include <QPushButton>
#include <QComboBox>
#include <QPainter>
#include "_global.h"
#include <QCheckBox>
using namespace CVTS;
class h_ResultControlPane : public QWidget

{
    Q_OBJECT
public:
    h_ResultControlPane(QWidget *parent = 0);

signals:
    void    on_import();
    void    on_add ();
    void    clear_all();
    void    on_export();
    void    on_fullscreen();
    void    on_show_normal();
    void    show_chart(bool &show_magn,bool &show_phase);
    void    selectChange(QString,QString,QString);
    void    DataType(bool is360, bool isdB);
public slots:
    void  clearItem();
    void  curSelectChange();
    void  addFreqItem(std::vector<QString> pFreq);
    void  change_btn_full();
    void  change_btn_normal();
    void  full_or_normal();
    void  check_radio();
    void  data_export();

protected:
    void initWidget();
    void paintEvent(QPaintEvent *e);
private:
    QRadioButton                  *L_Liner;
    QRadioButton                  *m_DB;
    QRadioButton                  *m_360;
    QRadioButton                  *m_180;
    QCheckBox                     *m_magn;
    QCheckBox                     *m_Phase;
    QPushButton                   *btn_5;
    bool                           isfull;
    QGroupBox                     *leftGroup;
    QGroupBox                     *RightGroup;
    QComboBox                     *m_stageComb;
    QComboBox                     *m_typeComb;
    QComboBox                     *m_freqComb;
};


#endif // H_RESULTCONTROLPANE_H

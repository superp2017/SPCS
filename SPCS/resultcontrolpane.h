#ifndef RESULTCONTROLPANE_H
#define RESULTCONTROLPANE_H

#include <QWidget>
#include "_global.h"
#include <QDebug>

namespace Ui {
class ResultControlPane;
}


/*!
 * \brief The ResultControlPane class
 * 测试结果界面的控制面板
 */
class ResultControlPane : public QWidget
{
    Q_OBJECT

protected:
    explicit ResultControlPane(QWidget *parent = 0);
      ~ResultControlPane();
public:
    static ResultControlPane * instance()
    {
        static ResultControlPane *_m = new ResultControlPane();
        return _m;
    }
    static void destory()
    {
        delete instance();
    }
    void addFreqItem(std::vector<QString> &tFreq);
    void addTimesItem(int t_mpTimes, int t_m_mpTimes);

    bool isDB();
    bool is360();

signals:
    void full_screen(bool isFullScreen);
    void show_MagnPhase(bool showmagn,bool showphase);
    void SelectChanged(QString,QString,QString,QString,bool,bool);
    void export_data();
    void load_data();
    void add_data();
    void clear_data();
protected slots:
    void currentSelectChanged();
    void viewChanged();
    void fullScreen_slot();
    void add_time_item(QString stage);
public slots:
    void checkbox_checked();
    void enable_combox(bool enable, bool isdb = false);
    void Clear();

private:
    void InitWidget();
    void createConnection();
private:
    Ui::ResultControlPane *ui;

    bool   m_isFullScreen;
    int    m_mpTimes;
    int    m_m_mpTimes;
};

#endif // RESULTCONTROLPANE_H

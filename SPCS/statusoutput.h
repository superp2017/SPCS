#ifndef STATUSOUTPUT_H
#define STATUSOUTPUT_H

#include <QtWidgets>
#include "_global.h"
using namespace CVTS;

/*!
 * \brief The StatusTitle class
 * 主界面的状态窗口
 */

class StatusTitle : public QWidget
{
    Q_OBJECT
public:
    explicit StatusTitle(QWidget *parent = 0)
    {

    }

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *)
    {
        QPainter painter(this);
        QRectF rt_top(rect().left(), rect().top(), rect().width(), rect().height()*2/5);
        QRectF rt_bottom(rect().left(), rect().top() + rect().height()*2/5, rect().width(), rect().height()*3/5);
        painter.fillRect(rt_top, QBrush(QColor(115,120,120)));
        painter.fillRect(rt_bottom, QBrush(QColor(110,110,110)));
        QRectF rt(rect().left(), rect().top(), 200, rect().height());
        painter.drawText(rt, Qt::AlignLeft | Qt::AlignVCenter, CVTS::GBKToUnicode::toUnicode(" 当前状态"));
    }
};

class StatusOutput : public QWidget
{
    Q_OBJECT
protected:
    explicit StatusOutput(QWidget *parent = 0);
public :
    static StatusOutput *instance()
    {
        static StatusOutput * output = new StatusOutput();
        return output;
    }
    static void destory()
    {
        delete instance();
    }
signals:
    
public slots:
    void update_value();
    void update_proj_name(QString& p_name);
    void update(OUTPUT_STATUS_DATA &data);
    void updata_freq(double start, double end, double step);
    void reset();
    void setenable(bool enable);

protected:
    //    virtual void paintEvent(QPaintEvent *event);
    //    virtual void resizeEvent(QResizeEvent *event);
    void to_freq_string(double value, char (&str_data)[1024]);
    void init_data();

private:
    StatusTitle         m_staTitle;
    QListView           m_listView;
    QStandardItemModel  m_listModel;
    QGridLayout         m_grid_layout;
    double              m_begin_freq;

    QStandardItem       *m_Proj_title_item;
    QStandardItem       *m_Proj_name_item;

    QStandardItem       *m_item_1;
    double              m_end_freq;
    QStandardItem       *m_item_2;
    double              m_step_freq;
    QStandardItem       *m_item_3;

    int                 m_begin_detector;
    QStandardItem       *m_item_4;
    int                 m_end_detector;
    QStandardItem       *m_item_5;

    int                 m_begin_sweep;
    QStandardItem       *m_item_6;
    int                 m_end_sweep;
    QStandardItem       *m_item_7;

    int                 m_antenna_count;
    OUTPUT_STATUS_DATA  m_default_data;
    QString             m_Proj_name;
};

#endif // STATUSOUTPUT_H

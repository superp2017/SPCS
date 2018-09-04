#ifndef TESTRESULT_H
#define TESTRESULT_H

#include <QtWidgets>
#include "h_TestOutArea.h"
#include "datamanage.h"

class TesTitle : public QWidget
{
    Q_OBJECT
public:
    explicit TesTitle(QWidget *parent = 0)
    {

    }

protected:
    void paintEvent(QPaintEvent *e)
    {
        QPainter painter(this);

        QRectF rts(rect().left(), rect().top(), rect().width() -1, rect().height() -1);
        painter.setPen(QPen(QColor(100,100,100), 0));
        painter.drawRect(rts);

        QRectF rt_top(rect().left()+1, rect().top()+1, rect().width()-2, rect().height()*2/5);
        QRectF rt_bottom(rect().left()+1, rect().top() + rect().height()*2/5, rect().width()-2, rect().height()*3/5);
        painter.fillRect(rt_top, QBrush(QColor(115,220,220)));
        painter.fillRect(rt_bottom, QBrush(QColor(110,210,210)));
        QRectF rt(rect().left(), rect().top(), 200, rect().height());
        painter.drawText(rt, Qt::AlignLeft | Qt::AlignVCenter, CVTS::GBKToUnicode::toUnicode(" 测 试 结 果"));
    }
};

/*!
 * \brief The TestResult class
 *  测试结果界面
 */
class TestResult : public QWidget
{
    Q_OBJECT
protected:
    explicit TestResult(QWidget *parent = 0);
public:
    static TestResult* instance();
    static void destroy();

    void initData(H_ORG &t_org, H_CFG_MP &t_cfg_mp,H_CFG_MP &t_cfg_m_mp,\
                  H_CFG_FINAL &t_cfg_final,std::vector<int> &t_Id,\
                  std::vector<QString> &t_freq);
signals:
    void  on_fullscreen();
    void  on_show_normal();
    void  change_btn_full();
    void  change_btn_normal();

public slots:
    void createConnection();
    void reset();
    void on_import();
    void on_add ();
    void on_clear();
    void on_export();
    void fullScreen(bool isFullScreen);
    void show_chart(bool show_magn, bool show_phase);
    void selectChange(QString pStage, QString pTimes, QString pType, QString pFreq,bool isDB,bool is360);
protected:
    void paintEvent(QPaintEvent *e);
    void keyPressEvent(QKeyEvent *e);
    void import(bool isadd,QString &fileName);
    bool creat_curve(Curvedata &m_data, bool ishowmagn = true);
    void parse_data(QString &p_filename, Curvedata &data);
    void import_MaxFile(QString& p_path);
    void import_MP_Files(QString& p_path);
    void clear();
    bool Clear_data();
private:
    QHBoxLayout                  m_grid_layout;
    TesTitle                     m_title;
    h_TestOutArea                m_out_area;
    std::vector<QString>         m_id;
    std::vector<Curvedata>       m_import_data_org;
    std::vector<Curvedata>       m_import_data_db;
    DataManage                   m_manage;
    bool                         m_rang_360;
    bool                         m_isDB;

    H_ORG                        m_org;
    H_CFG_MP                     m_cfg_mp;
    H_CFG_MP                     m_cfg_m_mp;
    H_CFG_FINAL                  m_cfg_final;
};

#endif // TESTRESULT_H


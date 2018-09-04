#ifndef RADARANALY_H
#define RADARANALY_H

#include <QtWidgets>
#include "radarview.h"
#include "radarscene.h"
#include "_global.h"

using namespace CVTS;

/*!
 * \brief The RadarAnaly class
 * ’Û√Ê∑÷Œˆ
 */
class RadarAnaly : public QWidget
{
    Q_OBJECT
protected:
    explicit RadarAnaly(QWidget *parent = 0);
    ~RadarAnaly();
public:
    static RadarAnaly* instance()
    {
        static RadarAnaly *s_face = new RadarAnaly();
        return s_face;
    }

    static void destroy()
    {
        delete instance();
    }

signals:

public slots:
    void init(QRect &rt);
    void full_screen(bool full);

    void load_face(H_ORG t_org, \
                   H_CFG_MP &t_cfg_mp, \
                   H_CFG_MP &t_cfg_m_mp, \
                   H_CFG_FINAL &t_cfg_final, \
                   std::map<int,Radar *> &t_radars_map, \
                   std::vector<int> &t_radar_id, \
                   std::vector<QString> &t_freq);


    void selectChanged();
    void savePic();
    void updateView();
    void clear_updown();
    void reset();
    void addTimesItem();
protected:
    void check_error();
    void addItemFreq();
    void paintEvent(QPaintEvent *e);
    void Convert_color(double t_phase,double up,double down ,double &red,double &gre,double &blue);
    void error_msg();
private:
    RadarView                *m_view;
    std::string               m_title;
    QRect                     m_rt;
    int                       m_view_w;
    int                       m_view_h;
    QScrollArea              *m_area;
    RadarScene               *m_scene;

    QPushButton              *m_update;
    QPushButton              *m_screenshot_btn;
    QComboBox                *m_stageComb;
    QComboBox                *m_TimesComb;
    QComboBox                *m_typeComb;
    QComboBox                *m_freqComb;
    QComboBox                *m_range;
    QLineEdit                *m_up;
    QLineEdit                *m_down;
    QRadioButton             *m_magn;
    QRadioButton             *m_phase;

    std::vector<int>          m_radars_id;
    std::map<int, Radar*>     m_radars_map;
    std::map<int, QString>    m_radars;
    std::vector<QString>      m_freq;



    H_ORG                    m_org;
    H_CFG_MP                 m_cfg_mp;
    H_CFG_MP                 m_cfg_m_mp;
    H_CFG_FINAL              m_cfg_final;
};

#endif // RADARANALY_H

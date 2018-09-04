#ifndef RADARSCENE_H
#define RADARSCENE_H

#include "radarwnd_global.h"
#include <QGraphicsScene>
#include "radar.h"
#include <map>
#include <QVector>
#include "detector.h"
#include "sweepline.h"
#include <QMutex>

class RADARWNDSHARED_EXPORT RadarScene : public QGraphicsScene
{
    Q_OBJECT
public:
    RadarScene(qreal x, qreal y, qreal width, qreal height);

    void init_scene();
    void reset();
    void fill_radars(std::map<int, QString> &pts, QString offset);
    void gen_map();
    void save_map();
    QPointF get_radar_pos(int id);
    CVTS::map_st& get_map();
    void load_map(const QString &file);
    std::map<int, Radar *> &get_map_radars();
    void fill_map_radars(std::map<int, Radar *> &radars);
    std::vector<int>& get_radars_id();
signals:
    void map_finish();
public slots:
    void sweep_rect(QRectF &rt);
    void sweep_pos(QPointF &pt);
    void sweep_neg(QPointF &pt);
    void check_radar(QRectF *rt, int cd, int pos);
    void detector_finish_counter();
    void finish();


private:
    QList<Radar*>                   m_radars;
    QVector<Detector*>              m_detectors;
    std::map<int, CVTS::_SPoint>    m_org_pts;
    double                          m_org_w;
    double                          m_org_h;
    double                          m_scene_center_x;
    double                          m_scene_center_y;
    double                          m_scene_w;
    double                          m_scene_h;
    double                          m_scene_x;
    double                          m_scene_y;
    double                          m_face_center_x;
    double                          m_face_center_y;
    double                          m_dw;
    double                          m_dh;
    int                             m_finish_count;
    SweepLine                       *m_sweep_line;
    std::map<int, Radar*>           m_map_radars;
    CVTS::map_st                    m_maps;
    std::vector<int>                m_radars_id;
    QMutex                          m_mutex;
    int                             m_map_width;
    int                             m_map_height;
    int                             m_scene_width;
    int                             m_scene_height;
};

#endif // RADARSCENE_H

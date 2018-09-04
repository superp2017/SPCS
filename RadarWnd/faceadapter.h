#ifndef FACEADAPTER_H
#define FACEADAPTER_H
#include <QPointF>
#include <QTextStream>
#include <QMap>

class FaceAdapter
{
public:
    FaceAdapter();

    FaceAdapter& operator <<(QTextStream&);

    FaceAdapter& operator >>(QTextStream&);

    QPointF& get_org_pt();
    QMap<int, QPointF>& get_radar_map();

protected:
    QPointF                 m_org;
    QMap<int, QPointF>      m_radar_map;
};

#endif // FACEADAPTER_H

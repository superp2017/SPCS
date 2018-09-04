#include "faceadapter.h"

FaceAdapter::FaceAdapter()
{
}

FaceAdapter &FaceAdapter::operator <<(QTextStream &)
{
    return *this;
}

FaceAdapter &FaceAdapter::operator >>(QTextStream &)
{
    return *this;
}

QPointF &FaceAdapter::get_org_pt()
{
    return m_org;
}

QMap<int, QPointF> &FaceAdapter::get_radar_map()
{
    return m_radar_map;
}

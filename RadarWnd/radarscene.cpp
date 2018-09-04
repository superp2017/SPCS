#include "radarscene.h"
#include <stdlib.h>
#include <QtWidgets>
#include <QFileDialog>
#include "_global.h"
#include "bkarea.h"

RadarScene::RadarScene(qreal x, qreal y, qreal width, qreal height)
    : QGraphicsScene(x, y, width, height)
{
    m_sweep_line = 0;
    m_dw = width / (Grid_width + 2);
    m_dh = height / (Grid_height + 2);
    m_scene_x = x + m_dw;
    m_scene_y = y + m_dh;
    m_scene_w = width - m_dw * 2;
    m_scene_h = height - m_dh * 2;

    m_scene_center_x = x + m_scene_w/2 + m_dw;
    m_scene_center_y = y + m_scene_h/2 + m_dh;

    m_map_width = width;
    m_map_height = height;

    m_scene_width = width;
    m_scene_height = height;
    reset();
}



void RadarScene::init_scene()
{
    QList<Radar*>::iterator iter = m_radars.begin();
    while(iter != m_radars.end())
    {
        int n = ((*iter)->rect().width() +(*iter)->rect().height())/4;
        QRadialGradient gradient((*iter)->rect().left()+n, (*iter)->rect().top()+n, \
                                 ((*iter)->rect().width() + (*iter)->rect().height())/2, \
                                 (*iter)->rect().left()+n, (*iter)->rect().top()+n);
        gradient.setColorAt(0, QColor::fromRgbF(0, 1, 0, 1));
        gradient.setColorAt(1, QColor::fromRgbF(0, 0, 0, 0));
        gradient.setRadius(n);
        (*iter)->setBrush(QBrush(gradient));
        QPen pen(QColor(0,0,0,0));
        (*iter)->setPen(pen);
        (*iter)->setZValue(1);
        (*iter)->hide();
        addItem((*iter));
        iter++;
    }
}

void RadarScene::reset()
{
    QList<Radar*>::iterator iter = m_radars.begin();
    while(iter != m_radars.end())
    {
        removeItem(*iter);
        if(*iter)
            delete *iter;
        iter++;
    }
    m_radars.clear();

    QVector<Detector*>::iterator dter = m_detectors.begin();
    while(dter != m_detectors.begin())
    {
        removeItem(*dter);
        if(*dter)
            delete *dter;
        dter++;
    }

    delete m_sweep_line;
    m_sweep_line = 0;

    m_detectors.clear();

    m_org_pts.clear();

    m_org_w = Grid_step_w * Grid_width;

    m_org_h = Grid_step_h * Grid_height;

    m_detectors.clear();

    m_map_radars.clear();
    m_radars_id.clear();

    m_maps.clear();

}

void RadarScene::sweep_rect(QRectF &rt)
{
    QList<Radar*>::iterator iter = m_radars.begin();
    while(iter != m_radars.end())
    {
        QPointF pt = (*iter)->center_pt();
        if(pt.x() >= rt.left() && pt.x() <= rt.right() \
                && pt.y() >= rt.top() && pt.y() <= rt.bottom())
        {
            (*iter)->turn_on();

        }else if((*iter)->status() == Radar::TurnOn)
        {
            (*iter)->to_high_light();
        }

        iter++;
    }
}

void RadarScene::sweep_pos(QPointF &pt)
{
    std::map<int, Radar*>::iterator iter = m_map_radars.begin();
    while(iter != m_map_radars.end())
    {
        QPointF it = iter->second->center_pt();
        qreal w = pt.x() - it.x();
        if(w <= 3 && w >= 0)
        {
            iter->second->turn_on();
        }else if(iter->second->status() == Radar::TurnOn)
        {
            iter->second->to_high_light();
        }

        iter++;
    }
}

void RadarScene::sweep_neg(QPointF &pt)
{
    std::map<int, Radar*>::iterator iter = m_map_radars.begin();
    while(iter != m_map_radars.end())
    {
        QPointF it = iter->second->center_pt();
        qreal w = pt.x() - it.x();
        if(w >= -3 && w <= 0)
        {
            iter->second->turn_on_forever();
        }

        iter++;
    }
}

void RadarScene::check_radar(QRectF *rt, int cd, int pos)
{
    //m_mutex.lock();
    QList<Radar*>::iterator iter = m_radars.begin();
    while(iter != m_radars.end())
    {
        QPointF pt = (*iter)->center_pt();
        if(pt.x() >= rt->left()-1 && pt.x() <= rt->right()+1 \
                && pt.y() >= rt->top()-1 && pt.y() <= rt->bottom()+1)
        {
            (*iter)->turn_on();
            if(m_map_radars.find((*iter)->id()) == m_map_radars.end())
            {
                m_detectors[cd-1]->push_back(pos+1, (*iter)->id());
                m_map_radars[(*iter)->id()] = *iter;
            }
        }else if((*iter)->status() == Radar::TurnOn)
        {
            (*iter)->to_high_light();
        }

        iter++;
    }
    //m_mutex.unlock();

}

void RadarScene::detector_finish_counter()
{
    m_finish_count++;
    if(m_finish_count == Detector_num)
    {
        m_sweep_line->begin_sweep(m_dw, m_dh, m_scene_w + m_dw, m_dh);
    }
}

void RadarScene::finish()
{
    int min_d = 1000000, max_d = -1000000;
    int min_decetor = -1, max_decetor = 0;
    int sum = 0;
    for(int i=0; i<Detector_num; i++)
    {
        std::map<int, std::set<int> >::iterator iter = m_detectors[i]->radars().begin();

        while(iter != m_detectors[i]->radars().end())
        {
            sum += iter->second.size();

            if(iter->second.size() > 0)
            {
                if(min_d > iter->first) min_d = iter->first;
                if(max_d < iter->first) max_d = iter->first;
                if(min_decetor == -1) min_decetor = i+1;
                max_decetor = i+1;
            }
            iter++;
        }
    }

    m_maps.min_d = min_decetor;
    m_maps.max_d = max_decetor;
    m_maps.min_p = min_d;// + SweepShelf_Base;
    m_maps.max_p = max_d;// + SweepShelf_Base;
    m_maps.count = sum;

    for(int j=-Grid_half_w; j<=Grid_half_w; j++)
        for(int i=0; i<Detector_num; i++)
        {
            if(m_detectors[i]->radars()[j].size() != 0)
            {
                CVTS::map_item_st ls_item;
                ls_item.item_p = j;
                ls_item.item_d = i+1;
                ls_item.item_count = m_detectors[i]->radars()[j].size();
                std::set<int>::iterator iter = m_detectors[i]->radars()[j].begin();
                while(iter != m_detectors[i]->radars()[j].end())
                {
                    QPointF pt = get_radar_pos(*iter);
                    ls_item.items[*iter].x = pt.x();
                    ls_item.items[*iter].y = pt.y();
                    ls_item.items[*iter].z = 0.0;
                    iter++;
                }
                m_maps.map_vec.push_back(ls_item);
            }
        }
}

std::vector<int> &RadarScene::get_radars_id()
{
    return m_radars_id;
}


void RadarScene::fill_radars(std::map<int, QString> &pts, QString offset)
{
    m_map_radars.clear();
    QStringList ls_offset_list = offset.split(QRegExp(QChar(',')));
    if(ls_offset_list.size() != 3) return;
    m_face_center_x = ls_offset_list.at(0).toDouble();
    m_face_center_y = ls_offset_list.at(1).toDouble();


    std::map<int, QString>::iterator iter = pts.begin();
    while(iter != pts.end())
    {
        QStringList ls_list = iter->second.split(QRegExp(QChar(',')));
        if(ls_list.size() == 3)
        {

            m_org_pts[iter->first].x = ls_list.at(0).toDouble()/**(205*5)/Radar_face_width  \*/
                    - m_face_center_x/**(205*5)/Radar_face_width*/;
            m_org_pts[iter->first].y = ls_list.at(1).toDouble()/**(65*24)/Radar_face_height \*/
                    - m_face_center_y/**(65*24)/Radar_face_height*/;
            m_org_pts[iter->first].z = ls_list.at(2).toDouble();
        }
        iter++;
    }

    double x_off = m_org_w/2;
    double y_off = m_org_h/2;


    std::map<int, CVTS::_SPoint>::iterator pter = m_org_pts.begin();
    while(pter != m_org_pts.end())
    {
        CVTS::SPoint sp;
        sp.x = (pter->second.y + y_off)/m_org_h * m_scene_w + m_scene_x;
        sp.y = (pter->second.x + x_off)/m_org_w * m_scene_h + m_scene_y;

        sp.z = 0;
        Radar *r = new Radar(pter->first, sp);
        r->setZValue(5);

        char *c_id = (char*)&(pter->first);
        int  row = *((short*)c_id+1);
        int  col = *((short*)c_id);
        r->set_tip_text(QString("ID:%1(%2,%3)").arg(pter->first).arg(row).arg(col));

//        if(pter->first == 65537)
//        {
//            qDebug() << "face import x = " << sp.x << "y = " << sp.y << "z = " << sp.z;
//        }

        addItem(r);
        m_radars.push_back(r);
        pter++;
    }

    m_detectors.resize(Detector_num);
    for(int i=0; i<Detector_num; i++)
    {
        m_detectors[i] = new Detector(i+1, QRectF(m_dw, (i+1)*m_dh, m_dw, m_dh));
        connect(m_detectors[i], SIGNAL(check_radar(QRectF*,int,int)), this, SLOT(check_radar(QRectF*,int,int)));
        m_detectors[i]->setPen(QPen(QColor(0,255,255)));
        m_detectors[i]->setBrush(QBrush(QColor(0,255,255,20)));
        m_detectors[i]->setZValue(10);
        m_detectors[i]->hide();
        addItem(m_detectors[i]);
        //connect(m_detectors[i], SIGNAL(check_radar(QRectF&,int,int)), this, SLOT(check_radar(QRectF&,int,int)));
        connect(m_detectors[i], SIGNAL(next()), this, SLOT(detector_finish_counter()));
    }

    m_sweep_line = new SweepLine();
    m_sweep_line->setLine(0,0,0, m_scene_h);
    m_sweep_line->setPen(QPen(QColor(255,255,0), 2));
    m_sweep_line->hide();
    m_sweep_line->setZValue(11);
    connect(m_sweep_line, SIGNAL(current_pos(QPointF&)), this, SLOT(sweep_pos(QPointF&)));
    connect(m_sweep_line, SIGNAL(current_neg(QPointF&)), this, SLOT(sweep_neg(QPointF&)));
    addItem(m_sweep_line);
    connect(m_sweep_line, SIGNAL(finish()), this, SLOT(finish()));
    connect(m_sweep_line, SIGNAL(finish()), this, SIGNAL(map_finish()));
}

void RadarScene::gen_map()
{
    m_map_radars.clear();
    for(int i=0; i<Detector_num; i++)
    {
        m_detectors[i]->begin_map();
    }
    m_finish_count = 0;
}

void RadarScene::save_map()
{
    QString fileName = QFileDialog::getSaveFileName(NULL, tr("Save File"),
                                                    "",
                                                    tr("Maps (*.map)"));
    if(fileName.isEmpty()) return ;

    FILE *f = fopen(fileName.toLocal8Bit().data(), "w");


    fprintf(f, "%d %d %d %d %d %d %d\n", \
            m_maps.min_d, m_maps.max_d, \
            m_maps.min_p, m_maps.max_p, m_maps.count,\
            m_map_width, m_map_height);
    for(int i=0; i<m_maps.map_vec.size(); i++)
    {
        fprintf(f, "%d %d %d,", m_maps.map_vec[i].item_p, m_maps.map_vec[i].item_d, m_maps.map_vec[i].item_count);
        std::map<int, CVTS::SPoint>::iterator iter = m_maps.map_vec[i].items.begin();
        while(iter != m_maps.map_vec[i].items.end())
        {
            ///modified by mzfeng 2013-11-27
            if(iter->first == 65537)
            {
//                qDebug() << "save map x = " << iter->second.x \
//                         << "y = " << iter->second.y \
//                         << "z = " << iter->second.z;
            }
            fprintf(f, " %d %f %f %f", iter->first, iter->second.x, iter->second.y, iter->second.z);
            //fprintf(f, " %d", iter->first);
            iter++;
        }
        fprintf(f, "\n");
    }

    fclose(f);
}

QPointF RadarScene::get_radar_pos(int id)
{
    QList<Radar*>::iterator iter = m_radars.begin();
    while(iter != m_radars.end())
    {
        if(id == (*iter)->id())
        {
            return (*iter)->origin_pt();
        }
        iter++;
    }
    return QPointF(0,0);
}

CVTS::map_st &RadarScene::get_map()
{
    return m_maps;
}



void RadarScene::load_map(const QString &file)
{
    m_map_radars.clear();
    QFile f(file);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    if(!f.atEnd())
    {
        QByteArray line = f.readLine().trimmed();
        QStringList list = QString(line).split(QRegExp(QChar(' ')));
        if(list.size() < 7) return;
        m_maps.min_d = list.at(0).toInt();
        m_maps.max_d = list.at(1).toInt();
        m_maps.min_p = list.at(2).toInt();
        m_maps.max_p = list.at(3).toInt();
        m_maps.count = list.at(4).toInt();
        m_map_width = list.at(5).toInt();
        m_map_height = list.at(6).toInt();
        m_maps.map_vec.clear();
    }

    while (!f.atEnd()) {
        QByteArray line = f.readLine().trimmed();
        QStringList list = QString(line).split(QRegExp(QChar(',')));
        if(list.size() != 2) return ;
        QStringList list_first = list.at(0).trimmed().split(QRegExp(QChar(' ')));
        if(list_first.size() != 3) return ;
        CVTS::map_item_st   ls_item;
        ls_item.item_p = list_first.at(0).toInt();
        ls_item.item_d = list_first.at(1).toInt();
        ls_item.item_count = list_first.at(2).toInt();

        QStringList list_second = list.at(1).trimmed().split(QRegExp(QChar(' ')));
        if(list_second.size() % 4 != 0) return ;
        int n = list_second.size() / 4;
        for(int i=0; i<n; i++)
        {
            int T = list_second.at(4 * i + 0).toInt();
            m_radars_id.push_back(T);
            ls_item.items[T].x = list_second.at(4 * i + 1).toDouble() * m_scene_width/m_map_width;
            ls_item.items[T].y = list_second.at(4 * i + 2).toDouble() * m_scene_height/m_map_height;
            ls_item.items[T].z = list_second.at(4 * i + 3).toDouble();
            Radar *r = new Radar(T, ls_item.items[T]);
            r->setZValue(5);
            r->to_flicker();

            char *c_id = (char*)&T;
            int row = *((short*)c_id+1);
            int  col = *((short*)c_id);
            r->set_tip_text(QString("ID:%1(%2,%3)").arg(T).arg(row).arg(col));
            addItem(r);
            m_map_radars[T] = r;

            m_radars.push_back(r);
        }
    }
}

std::map<int, Radar *> &RadarScene::get_map_radars()
{
    return m_map_radars;
}

void RadarScene::fill_map_radars(std::map<int, Radar *> &radars)
{
    reset();
    std::map<int, Radar *>::iterator iter = radars.begin();
    while(iter != radars.end())
    {
        Radar *r = new Radar(iter->second);
        r->setZValue(5);
        addItem(r);
        m_map_radars[iter->first] = r;
        m_radars.push_back(r);

        iter++;
    }
}

#include "tarray.h"
#include "bkarea.h"
#include "taskcenter_607.h"

TArray::TArray(QWidget *parent) :
    QDialog(parent),
    m_title("ÕóÃæ")
{
    m_view  =  0;
    m_scene =  0;
    m_area  =  0;
    this->setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
}

void TArray::reset()
{
    if(m_scene)
        m_scene->reset();
    m_radars_map.clear();
    m_radars_id.clear();
}



void TArray::init(QRect &rt)
{
    if(m_view != 0) return ;
    m_rt = rt;

    double dw = QApplication::desktop()->availableGeometry().width() - 240;;
    double dh = dw/(Grid_step_w * Grid_width) * (Grid_step_h * Grid_height);

    m_view_w = dw;
    m_view_h = dh;
    double rate = dw/(Grid_step_w * Grid_width);
    m_view = new RadarView(m_scene = new RadarScene(0,0,dw-200, dh));

    BkArea *area = new BkArea(NULL,rate*Grid_step_w*5.5,Grid_step_h*rate*4.4);
    area->has_text(true);
    area->setRect(0,0,dw-200,  dh);
    area->setZValue(0);
    m_scene->addItem(area);


    m_view->setParent(this);

    m_view->setGeometry(-rate*Grid_step_w*5.5,-Grid_step_h*rate*4.4,(dw-200),dh);
    m_view->show();

    qDebug()<<rate;
    QString ls_sheet = QString::fromUtf8("font: 10pt \"\346\245\267\344\275\223\";");
    this->setStyleSheet(ls_sheet);
    QString title = CVTS::GBKToUnicode::toUnicode("ÕóÃæ");
    this->setWindowTitle(title);
    this->setFixedSize(rate*(15*Grid_step_w-228),rate*(7*Grid_step_h));
    update();
}

void TArray::init_data(std::map<int, Radar *> &p_radars,std::vector<int> &p_radar_id)
{
    m_radars_map.clear();
    m_radars_id.clear();
    if(p_radar_id.size() == p_radars.size() && p_radar_id.size()>0)
    {
        for(size_t i =0;i<p_radar_id.size();++i)
        {
            int id = p_radar_id.at(i);
            if(p_radars.count(id)>0)
            {
                CVTS::SPoint sp;
                Radar *de    =  p_radars[id];
                CVTS::SPoint cur = de->get_default_point();
                if(!m_radars_map.count(id))
                {
                    sp.x     =   cur.x * m_scene->width()/TaskCenter_607::instance()->get_map_width();
                    sp.y     =   cur.y* m_scene->height()/TaskCenter_607::instance()->get_map_height();
                    sp.z     =   cur.z;
                    Radar *r = new Radar(id, sp);
                    m_radars_id.push_back(id);
                    m_radars_map[id] = r;
                    r->setZValue(5);
                    QColor red = QColor(100,100,100);
                    r->set_color(red);
                    r->turn_on_forever();
                    m_scene->addItem(r);
                }
            }
        }
    }

//    double x = -280/(m_scene->height()/TaskCenter_607::instance()->get_map_height());
//    double y = -370/(m_scene->height()/TaskCenter_607::instance()->get_map_height());
//    qDebug()<<x<<y;
//    m_view->setGeometry(x,y,m_view->width(),m_view->height());

}

void TArray::update_radars(int id)
{
    if(m_radars_map.count(id) >0)
    {
        QColor yellow(0,255,0);
        m_radars_map[id]->set_color(yellow);
        m_radars_map[id]->turn_on_forever();
    }
    update();
    repaint();
}

void TArray::resetView()
{
    for(size_t i =0;i<m_radars_id.size();++i)
    {
        int id = m_radars_id.at(i);
        if(m_radars_map.count(id)>0)
        {
            Radar *r = m_radars_map[id];
            QColor red = QColor(100,100,100);
            r->set_color(red);
            r->turn_on_forever();
        }
    }
}

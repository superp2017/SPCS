#include "radaranaly.h"
#include "bkarea.h"
#include "taskcenter_607.h"

RadarAnaly::RadarAnaly(QWidget *parent) :
    QWidget(parent),
    m_title("阵面分析")
{
    m_view  =  0;
    m_scene =  0;
    m_area  =  0;

    m_stageComb = 0;
    m_TimesComb = 0;////
    m_typeComb  = 0;
    m_freqComb  = 0;
       this->setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
}

RadarAnaly::~RadarAnaly()
{

}



void RadarAnaly::init(QRect &rt)
{
    if(m_view != 0) return ;
    m_rt = rt;
    m_area = new QScrollArea();
    double dw = QApplication::desktop()->availableGeometry().width() - 240;;
    double dh = dw/(Grid_step_w * Grid_width) * (Grid_step_h * Grid_height);

    m_view_w = dw;
    m_view_h = dh;
    m_view = new RadarView(m_scene = new RadarScene(0,0,dw - 200, dh));
    connect(m_view, SIGNAL(full_screen(bool)), this, SLOT(full_screen(bool)));
    m_area->setParent(this);
    m_view->setGeometry(0,0,dw - 200,dh);
    m_area->setWidget(m_view);
    m_area->setGeometry(80,50,dw - 260, rt.height()-80);
    m_area->showNormal();


    ///MP 2014/4/3
    int mp_h = (rt.height()-80)/10;
    m_stageComb = new QComboBox(this);
    connect(m_stageComb, SIGNAL(currentTextChanged(QString)), this, SLOT(addTimesItem()));
    connect(m_stageComb, SIGNAL(currentTextChanged(QString)), this, SLOT(selectChanged()));
    m_stageComb->setGeometry(rt.width() - 140, 50, 105, /*30*/25);

    ////////////////
    int hr = 1;
    m_TimesComb = new QComboBox(this);
    connect(m_TimesComb,SIGNAL(currentTextChanged(QString)),this,SLOT(selectChanged()));
    m_TimesComb->setGeometry(rt.width() - 140,/*50+mp_h*/50+mp_h*hr - hr*10, 105, /*30*/25);
    hr++;///////


    m_typeComb  = new QComboBox(this);
    connect(m_typeComb, SIGNAL(currentTextChanged(QString)), this, SLOT(selectChanged()));
    m_typeComb->setGeometry(rt.width() - 140, /*50+mp_h*/50+mp_h*hr - hr*10, 105, /*30*/25);
    hr++;///////

    m_freqComb  = new QComboBox(this);
    connect(m_freqComb, SIGNAL(currentTextChanged(QString)), this, SLOT(selectChanged()));
    m_freqComb->setGeometry(rt.width() - 140, /*50+mp_h*2*/50+mp_h*hr - hr*10, 105, /*30*/25);
    hr++;///////

    m_range = new QComboBox(this);
    m_range->setGeometry(rt.width() - 140, /*50+mp_h*3*/50+mp_h*hr - hr*10, 105, /*30*/25);
    connect(m_range,SIGNAL(currentIndexChanged(int)),this,SLOT(clear_updown()));
    connect(m_range, SIGNAL(currentIndexChanged(int)), this, SLOT(selectChanged()));

    QGroupBox *ls_box = new QGroupBox(CVTS::GBKToUnicode::toUnicode("类型"),this);
    m_magn  = new QRadioButton(CVTS::GBKToUnicode::toUnicode("幅度"),ls_box);
    m_phase = new QRadioButton(CVTS::GBKToUnicode::toUnicode("相位"),ls_box);
    m_magn->setChecked(true);
    m_phase->setChecked(false);
    ls_box->setGeometry(rt.width() - 140, 50 + mp_h*4, 105, 77);
    m_magn->setGeometry(23,17,75,30);
    m_phase->setGeometry(23,46,75,30);
    connect(m_magn,SIGNAL(clicked()),this,SLOT(clear_updown()));
    connect(m_phase,SIGNAL(clicked()),this,SLOT(clear_updown()));
    connect(m_magn,SIGNAL(clicked()),this,SLOT(selectChanged()));
    connect(m_phase,SIGNAL(clicked()),this,SLOT(selectChanged()));

    QLabel *ls_up = new QLabel("Up:",this);
    QLabel *ls_down = new QLabel("Down:",this);

    ls_up->setGeometry(rt.width() - 140, 50 + mp_h*6, 60, 26);
    ls_down->setGeometry(rt.width() - 140, 50 + mp_h*7, 60, 26);

    m_up  = new QLineEdit(this);
    m_up->setGeometry(rt.width()   - 93, 50 + mp_h*6, 55, 26);
    m_down  = new QLineEdit(this);
    m_down->setGeometry(rt.width() - 93, 50 + mp_h*7, 55, 26);

    m_update =new QPushButton(CVTS::GBKToUnicode::toUnicode("更新"), this);
    connect(m_update, SIGNAL(clicked()), this, SLOT(updateView()));
    m_update->setGeometry(rt.width() - 140, 50 + mp_h*8, 105, 30);

    m_screenshot_btn =new QPushButton(CVTS::GBKToUnicode::toUnicode("截图"), this);
    connect(m_screenshot_btn, SIGNAL(clicked()), this, SLOT(savePic()));
    m_screenshot_btn->setGeometry(rt.width() - 140, 50 + mp_h*9, 105, 30);

    m_stageComb->clear();
    m_typeComb->clear();
    m_freqComb->clear();


    m_stageComb->addItem(ORG_MP);
    m_stageComb->addItem(CFG_MP);
    m_stageComb->addItem(CFG_M);
    m_stageComb->addItem(FINAL_CFG);

  //  m_typeComb->addItem(S_1_1);
    m_typeComb->addItem(S_2_1);
   // m_typeComb->addItem(S_2_2);

    m_typeComb->addItem(TYPE_CFG);
    m_typeComb->addItem(TYPE_MP_1);
    //////////////////////////////////////

    m_range->addItem(P_0_360);
    m_range->addItem(P180180);


    BkArea *area = new BkArea();
    QColor character(255,255,255);
    QColor back(0,0,250);
    area->set_color(back,character);
    area->has_text(true);
    area->setRect(0,0,dw - 200, dh);
    area->setZValue(0);
    m_scene->addItem(area);

    QString ls_sheet = QString::fromUtf8("font: 11pt \"\346\245\267\344\275\223\";");

    this->setStyleSheet(ls_sheet);
}



void RadarAnaly::reset()
{
    m_scene->reset();
    m_radars.clear();
    m_radars_id.clear();
    m_radars_map.clear();

    m_freq.clear();
    m_magn->setChecked(true);
    m_phase->setChecked(false);

    m_org.clear();
    m_cfg_mp.clear();
    m_cfg_m_mp.clear();
    m_cfg_final.clear();
    m_freqComb->clear();
}


//////加载数据
void RadarAnaly::load_face(H_ORG t_org, H_CFG_MP &t_cfg_mp,\
                           H_CFG_MP &t_cfg_m_mp, H_CFG_FINAL &t_cfg_final, \
                           std::map<int, Radar *> &t_radars_map, std::vector<int> &t_radar_id,\
                           std::vector<QString> &t_freq)
{
    m_org         = t_org;
    m_cfg_mp      = t_cfg_mp;
    m_cfg_m_mp    = t_cfg_m_mp;
    m_cfg_final   = t_cfg_final;
    m_freq        = t_freq;

    if(t_radar_id.size() == t_radars_map.size() && t_radar_id.size()>0)
    {
        for(size_t i =0;i<t_radar_id.size();++i)
        {
            int id = t_radar_id.at(i);
            if(t_radars_map.count(id))
            {
                CVTS::SPoint sp;
                Radar *de    =  t_radars_map[id];
                CVTS::SPoint cur = de->get_default_point();
                if(!m_radars_map.count(id))
                {
                    sp.x     =   cur.x * m_scene->width()/TaskCenter_607::instance()->get_map_width();
                    sp.y     =   cur.y * m_scene->height()/TaskCenter_607::instance()->get_map_height();
                    sp.z     =   cur.z;
                    Radar *r = new Radar(id, sp);
                    m_radars_id.push_back(id);
                    m_radars_map[id] = r;
                    r->setZValue(5);
                    r->turn_on_forever();
                    m_scene->addItem(r);
                }
            }
        }
    }

    addItemFreq();
    selectChanged();
}




/*!
 * \brief RadarAnaly::selectChanged
 *changed 2014/2/25
 * 动态响应的槽。更新曲线
 */
void RadarAnaly::selectChanged()
{
    check_error();
    QString t_stage = m_stageComb->currentText();
    QString t_type  = m_typeComb->currentText();
    QString t_freq  = m_freqComb->currentText();

    int t_times = m_TimesComb->currentText().toInt();


    std::map<int, std::pair<QString,QString> > tmp ;
    if(t_stage == ORG_MP)
    {
        m_typeComb->setEnabled(true);

        if(m_org.count(t_type)>0 &&m_org[t_type].count(t_freq))
            tmp = m_org[t_type][t_freq];
    }
    if(t_stage == CFG_MP)
    {
        m_typeComb->setEnabled(true);
        t_times -=1;
        if(m_cfg_mp.count(t_times)>0 &&m_cfg_mp[t_times].count(t_type) >0 && m_cfg_mp[t_times][t_type].count(t_freq)>0)
            tmp = m_cfg_mp[t_times][t_type][t_freq];
    }
    if(t_stage == CFG_M)
    {
        m_typeComb->setEnabled(true);
        t_times -=1;
        if(m_cfg_m_mp.count(t_times)>0 &&m_cfg_m_mp[t_times].count(t_type) >0 && m_cfg_m_mp[t_times][t_type].count(t_freq)>0)
            tmp = m_cfg_m_mp[t_times][t_type][t_freq];
    }
    if(t_stage == FINAL_CFG)
    {
        m_typeComb->setCurrentIndex(1);
        m_typeComb->setEnabled(false);

        if(m_cfg_final.count(t_freq)>0)
            tmp = m_cfg_final[t_freq];
    }


    for(size_t i = 0; i < m_radars_id.size(); ++i)
    {
        int id = m_radars_id.at(i);
        Radar * t_r = m_radars_map[id];
        QString db ;
        double  phase;
        if(tmp.size() != 0)
        {
            if(t_stage != FINAL_CFG && t_type != TYPE_CFG &&t_type != TYPE_CFG )
                db = QString::number(SPCS_dB::dB(tmp[id].first.toDouble()),'f');
            else
                db = QString::number(tmp[id].first.toDouble(),'f');

            double c_up =  m_up->text().toDouble();
            double c_down = m_down->text().toDouble();

            phase  = tmp[id].second.toDouble();
            double  pdb =  db.toDouble();
            QColor white(255,255,255);
            QColor back(0,0,0);
            t_r->set_color(white);
            if(m_magn->isChecked())
            {
                if(!m_down->text().isEmpty()&& m_up->text().isEmpty())
                {
                    if(pdb < c_down)
                        t_r->set_color(back);
                }
                if(!m_up->text().isEmpty()&&m_down->text().isEmpty())
                {
                    if(pdb > c_up)
                        t_r->set_color(white);
                }
                if(m_down->text().isEmpty() && m_up->text().isEmpty())
                {
                    t_r->set_color(white);
                }
                if(!m_down->text().isEmpty() && !m_up->text().isEmpty())
                {
                    if(pdb < c_down)
                        t_r->set_color(back);
                    if(pdb >c_up)
                        t_r->set_color(white);
                    if(pdb >= c_down && pdb <= c_up)
                    {
                        double r,g,b;
                        Convert_color(pdb,c_up,c_down,r,g,b);
                        QColor ls_color((int)r,(int)g,(int)b);
                        t_r->set_color(ls_color);
                    }
                }
            }else
            {
                if(m_range->currentText() == P_0_360)
                {
                    //                        p_up   = 360;
                    //                        p_down = 0;
                    if(phase < 0)
                        phase += 360;
                }else
                {
                    if(phase>180)
                        phase -=360;
                    if(phase<-180)
                        phase +=360;
                }

                if(!m_down->text().isEmpty()&&m_up->text().isEmpty())
                {
                    if(phase < c_down)
                        t_r->set_color(back);
                }

                if(!m_up->text().isEmpty()&&m_down->text().isEmpty())
                {
                    if(phase > m_up->text().toDouble())
                        t_r->set_color(white);
                }

                if(m_up->text().isEmpty()&& m_down->text().isEmpty())
                {
                    t_r->set_color(white);
                }

                if(!m_up->text().isEmpty()&&!m_down->text().isEmpty())
                {
                    if(phase < c_down)
                        t_r->set_color(back);
                    if(phase > c_up)
                        t_r->set_color(white);
                    if(phase >=c_down && phase <= c_up)
                    {
                        double r,g,b;
                        Convert_color(phase,c_up,c_down,r,g,b);
                        QColor ls_color((int)r,(int)g,(int)b);
                        t_r->set_color(ls_color);
                    }
                }
            }
        }
        else{
            db = "0";
            phase =0;
        }
        QString str =CVTS::GBKToUnicode::toUnicode("阵元编号:")+QString("%1").arg(id)\
                + CVTS::GBKToUnicode::toUnicode(" 幅值:") +db\
                + CVTS::GBKToUnicode::toUnicode(",")\
                + CVTS::GBKToUnicode::toUnicode("相位:") + QString::number(phase,'f',3)\
                + CVTS::GBKToUnicode::toUnicode("°");
        t_r->set_tip_text(str);
        t_r->turn_on_forever();
    }
}

/*!
 * \brief RadarAnaly::addItemFreq
 * \param pFreq
 *changed 2014/2/25
 */
void RadarAnaly::addItemFreq()
{
    if(!m_freqComb) return;
    m_freqComb->clear();
    for(size_t i = 0; i < m_freq.size(); ++i)
    {
        QString key ;
        DoubleFre_TO_QStringFreq::Double_TO_QString(m_freq[i].toDouble(),key);
        m_freqComb->addItem(key);
    }
    m_freqComb->setCurrentIndex(0);
}


void RadarAnaly::addTimesItem()
{
    m_TimesComb->clear();
    QString t_stage = m_stageComb->currentText();
    int times  =0;
    if(t_stage == ORG_MP )
        times = 1;
    if(t_stage == CFG_MP )
        times = m_cfg_mp.size();
    if(t_stage == CFG_M )
        times = m_cfg_m_mp.size();
    if(t_stage == FINAL_CFG )
        times = 1;

    for(int i = 0;i < times; ++i)
    {
        m_TimesComb->addItem(QString("%1").arg(i+1));
    }
}


void RadarAnaly::savePic()
{
    QPixmap result = QPixmap();
    result = QPixmap::grabWidget(m_view);
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Pic"),
                                                    "./",
                                                    tr("Images (*.png *.bmp *.jpg)"));
    result.save(fileName);
}


void RadarAnaly::check_error()
{
    double down =  m_down->text().toDouble();
    double up   =  m_up->text().toDouble();

    double p_up   = 180;
    double p_down = -180;
    if(m_range->currentText() == P_0_360)
    {
        p_up   = 360;
        p_down = 0;
    }else
    {
        p_up   =  180;
        p_down = -180;
    }
    if(m_magn->isChecked())
    {
        p_up   =  200;
        p_down = -200;
    }

    if(!m_down->text().isEmpty() )
    {
        if(down < p_down || down > up)
        {
            error_msg();
            return ;
        }
    }
    if(!m_up->text().isEmpty())
    {
        if(up > p_up || up < p_down)
        {
            error_msg();
            return ;
        }
    }

    if(!m_down->text().isEmpty() &&!m_up->text().isEmpty())
    {
        if(down >up || down < p_down||down >p_up|| up >p_up || up < p_down)
        {
            error_msg();
            return ;
        }
    }
}


/////
/// \brief RadarAnaly::updateView
///点击更新按钮后。。。
void RadarAnaly::updateView()
{
    check_error();
    selectChanged();
    update();
    repaint();
}

void RadarAnaly::error_msg()
{
    QMessageBox msgBox;
    QString title = CVTS::GBKToUnicode::toUnicode("警告");
    QString str = CVTS::GBKToUnicode::toUnicode("下限上限设置错误！");
    msgBox.setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
    msgBox.setIconPixmap(QPixmap(".\\image\\607logo-6464.png"));
    msgBox.setWindowTitle(title);
    msgBox.setText(str);
    msgBox.exec();
}


void RadarAnaly::clear_updown()
{
    m_up->clear();
    m_down->clear();
}

void RadarAnaly::Convert_color(double t_phase,double up,double down ,double &red,double &gre,double &blue)
{
    t_phase -= down;
    double cur = (t_phase/(up-down)) * 255.0 *3;
    if(cur>=0 && cur<256)
    {
        blue  = cur;
        gre  = 0;
        red = 0;
    }else if(cur<512)
    {
        blue =0;
        gre = cur-256;
        red = 0;
    }else
    {
        blue = 0;
        gre = 0;
        red = cur - 256-256;
    }
}



void RadarAnaly::full_screen(bool full)
{
    if(full)
    {
        m_view->setParent(NULL);
        m_view->showFullScreen();
    }
    else
    {
        m_view->setParent(m_area);
        m_view->setGeometry(0,0,m_view_w-200, m_view_h);
        m_view->showNormal();
    }
}


void RadarAnaly::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QRectF rts(rect().left(), rect().top(), rect().width() -1, rect().height() -1);
    painter.setPen(QPen(QColor(155,155,155), 0));
    painter.drawRect(rts);

    QRectF rt(rect().left()-110, rect().top(), rect().width(), 50);
    QFont font(CVTS::GBKToUnicode::toUnicode("楷体"), 15, QFont::Bold);

    painter.setFont(font);
    painter.drawText(rt, Qt::AlignCenter, CVTS::GBKToUnicode::toUnicode(m_title.c_str()));

    QRectF ret(45,65, 20, 410);

    QLinearGradient Lbrush;

    QRectF r_up(18, 80, 35, 12);
    QRectF r_down (15, 420, 35, 12);
    Lbrush.setStart(-60,10);
    Lbrush.setFinalStop(-60, 370);

    QFont dfont(CVTS::GBKToUnicode::toUnicode("楷体"), 8, QFont::Bold);
    painter.setFont(dfont);

    if(m_down->text().isEmpty() && m_up->text().isEmpty())
    {
        Lbrush.setColorAt(0, QColor(0,0,0));
        Lbrush.setColorAt(1, QColor(255,255,255));
    }
    if(!m_down->text().isEmpty() && m_up->text().isEmpty())
    {
        Lbrush.setColorAt(0, QColor(255,0,0));
        Lbrush.setColorAt(0.9, QColor(0,0,255));
        Lbrush.setColorAt(1, QColor(0,0,0));

        painter.fillRect(ret, Lbrush);
        painter.drawText(r_down, Qt::AlignCenter, CVTS::GBKToUnicode::toUnicode(m_down->text()));
    }

    if(m_down->text().isEmpty() && !m_up->text().isEmpty())
    {
        Lbrush.setColorAt(0, QColor(255,255,255));
        Lbrush.setColorAt(0.2, QColor(255,0,0));
        Lbrush.setColorAt(1, QColor(0,0,255));

        painter.fillRect(ret, Lbrush);
        painter.drawText(r_up, Qt::AlignCenter, CVTS::GBKToUnicode::toUnicode(m_up->text()));
    }

    if(!m_down->text().isEmpty() && !m_up->text().isEmpty())
    {
        Lbrush.setColorAt(0.1, QColor(255,0,0));
        Lbrush.setColorAt(0.9, QColor(0,0,255));
        painter.fillRect(ret, Lbrush);
        painter.drawText(r_up, Qt::AlignCenter, CVTS::GBKToUnicode::toUnicode(m_up->text()));
        painter.drawText(r_down, Qt::AlignCenter, CVTS::GBKToUnicode::toUnicode(m_down->text()));
    }
}


#include "radarface.h"
#include "delaytask.h"
#include "radarscene.h"
#include <QSettings>
#include "searchunit.h"
#include "projectmanager.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QVBoxLayout>
#include "mainwindow.h"


RadarFace::RadarFace(QWidget *parent) :
    QWidget(parent),
    m_title("相控阵阵面")
{
    m_view = 0;
       this->setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
}

void RadarFace::set_title(std::string &title)
{
    m_title = title;
}

void RadarFace::reset()
{
    m_load_id.clear();
    m_scene->reset();
    m_radars_id.clear();
}



void RadarFace::init(QRect &rt)
{
    if(m_view != 0) return ;
    m_rt = rt;

    m_area = new QScrollArea();
    //    double dw = rt.width()-200;
    //    double dh = dw/(Grid_step_w * Grid_width) * (Grid_step_h * Grid_height);
    double dw = QApplication::desktop()->availableGeometry().width() - 240;
    double dh = dw/(Grid_step_w * Grid_width) * (Grid_step_h * Grid_height);

    m_view_w = dw;
    m_view_h = dh;
    m_view = new RadarView(m_scene = new RadarScene(0,0,dw-200, dh));

    connect(m_view, SIGNAL(full_screen(bool)), this, SLOT(full_screen(bool)));
    m_area->setParent(this);
    m_area->setWidget(m_view);
    m_area->setGeometry(0,50,dw-180, rt.height()-80);
    m_view->setGeometry(0,0,dw-200,dh);
    m_area->showNormal();

    m_search_btn =  new QPushButton(CVTS::GBKToUnicode::toUnicode("搜索单元"), this);
    connect(m_search_btn, SIGNAL(clicked()), this, SLOT(Search_unit()));

    m_gen_tools_btn = new QPushButton(CVTS::GBKToUnicode::toUnicode("阵面生成"), this);
    connect(m_gen_tools_btn, SIGNAL(clicked()), this, SLOT(gen_tools()));

    m_face_import_btn = new QPushButton(CVTS::GBKToUnicode::toUnicode("阵面文件"), this);
    connect(m_face_import_btn, SIGNAL(clicked()), this, SLOT(face_import()));
    m_map_import_btn = new QPushButton(CVTS::GBKToUnicode::toUnicode("映射文件"), this);
    connect(m_map_import_btn, SIGNAL(clicked()), this, SLOT(map_import()));
    // m_map_btn = new QPushButton(CVTS::GBKToUnicode::toUnicode("映射"), this);
    // connect(m_map_btn, SIGNAL(clicked()), this, SLOT(map()));
    // m_map_btn->setEnabled(false);
    m_save_btn = new QPushButton(CVTS::GBKToUnicode::toUnicode("保存"), this);
    connect(m_save_btn, SIGNAL(clicked()), this, SLOT(save()));
    m_save_btn->setEnabled(false);


    QWidget *btn_pane = new QWidget(this);
    QVBoxLayout *m_vBox_layout = new QVBoxLayout(this);
    m_search_btn->setFixedHeight(55);
    m_vBox_layout->addWidget(m_search_btn);
    m_gen_tools_btn->setFixedHeight(55);
    m_vBox_layout->addWidget(m_gen_tools_btn);
    m_face_import_btn->setFixedHeight(55);
    m_vBox_layout->addWidget(m_face_import_btn);
    m_map_import_btn->setFixedHeight(55);
    m_vBox_layout->addWidget(m_map_import_btn);
    m_save_btn->setFixedHeight(55);
    m_vBox_layout->addWidget(m_save_btn);
    btn_pane->setGeometry(QRect(dw-180,50, 170, rt.height()-50));
    btn_pane->setLayout(m_vBox_layout);
    btn_pane->showNormal();



    connect(m_scene, SIGNAL(map_finish()), this, SLOT(map_finish()));
    connect(&m_tools, SIGNAL(finished(int)), this, SLOT(gen_finished(int)));

    BkArea *area = new BkArea();
    area->has_text(true);
    area->setRect(0,0,dw-200, dh);
    area->setZValue(0);
    m_scene->addItem(area);


    m_outdata.t_begin_freq     = 0;
    m_outdata.t_end_freq       = 0;
    m_outdata.t_step_freq      = 0;
    m_outdata.t_begin_detector = 0;
    m_outdata.t_end_detector   = 0;
    m_outdata.t_begin_sweep    = 0;
    m_outdata.t_end_sweep      = 0;
    m_outdata.t_antenna_count  = 0;
    QString ls_sheet = QString::fromUtf8("font: 10pt \"\346\245\267\344\275\223\";");
    this->setStyleSheet(ls_sheet);
    connect(SearchUnit::instance(),SIGNAL(showUnit(int)),this,SLOT(update_unit_id(int)));
    connect(SearchUnit::instance(),SIGNAL(close_all()),this,SLOT(close_all()));
    connect(SearchUnit::instance(),SIGNAL(showIDs(QString)),this,SLOT(search_ids(QString)));

}

void RadarFace::update_radars(const QString &file)
{
    m_radars_id.clear();
    QSettings iniSets(file, QSettings::IniFormat);
    iniSets.beginGroup("COORDINATE");
    QStringList list = iniSets.allKeys();
    QStringList::iterator iter = list.begin();
    while(iter != list.end())
    {
        m_radars[iter->toInt()] = iniSets.value(*iter).toString();
        int id = (*iter).toInt();
        m_radars_id.push_back(id);
        iter++;
    }
    iniSets.endGroup();

    iniSets.beginGroup("OFFSET");
    list = iniSets.allKeys();
    iter = list.begin();
    QString offset;
    while(iter != list.end())
    {
        offset = iniSets.value(*iter).toString();
        iter++;
    }
    iniSets.endGroup();
    m_scene->fill_radars(m_radars, offset);
    // m_map_btn->setEnabled(true);
    m_map_import_btn->setEnabled(false);
    map();
}

//////////
/// \brief RadarFace::map_radars
/// \param file
///
void RadarFace::map_radars(const QString &file)
{
    m_scene->load_map(file);
}

void RadarFace::map()
{
    m_scene->gen_map();
    //  m_map_btn->setEnabled(false);
}


/////阵面导入
void RadarFace::face_import()
{
    QString path = QApplication::applicationDirPath() + DATA_PATH;
    QString fileName = QFileDialog::getOpenFileName(MainWindow::instance(), tr("Open File"),
                                                    path,
                                                    tr("Array (*.array)"));
    QFile ls_file(fileName);
    if(ls_file.exists())
    {
        m_scene->reset();
        m_radars.clear();
        update_radars(fileName);
    }else
        qDebug()<<"selected  Array file is not exist !";

}


/////
/// \brief RadarFace::map_import
/// 映射导入
void RadarFace::map_import()
{
    QString path = QApplication::applicationDirPath() + DATA_PATH;
    QString fileName = QFileDialog::getOpenFileName(MainWindow::instance(), tr("Open File"),path,tr("Map (*.map)"));
    QFile ls_file(fileName);
    if(ls_file.exists())
    {
        m_scene->reset();
        m_radars.clear();
        m_radars_id.clear();
        map_radars(fileName);
        m_radars_id = m_scene->get_radars_id();
    }else
        qDebug()<<"Selected map is not exist !";
    map_finish();
}



/////
/// \brief RadarFace::save
/// 保存
void RadarFace::save()
{
    m_scene->save_map();
}



//////映射完成后
void RadarFace::map_finish()
{
    m_save_btn->setEnabled(true);
    m_map_import_btn->setEnabled(true);
    update_status_output();
}

void RadarFace::full_screen(bool bl)
{
    if(bl)
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

///////////
/// \brief RadarFace::gen_tools
///调用阵面文件生成工具
void RadarFace::gen_tools()
{
    m_tools.startDetached("FaceRadar.exe");
    // m_gen_tools_btn->setEnabled(false);
}



void RadarFace::gen_finished(int code)
{
    m_gen_tools_btn->setEnabled(true);
}


/////////////
/// \brief RadarFace::update_status_output
/// 更新状态栏
void RadarFace::update_status_output()
{
    CVTS::map_st map = m_scene->get_map();
    std::vector<QString> ls_freq = M_SetFreqdlg::instance()->get_freq();
    if(ls_freq.size()==0)
    {
        m_outdata.t_begin_freq = 0;
        m_outdata.t_end_freq = 0;
        m_outdata.t_step_freq = 0;
    }
    if(ls_freq.size()>1)
    {
        m_outdata.t_begin_freq = ls_freq.at(0).toDouble();
        m_outdata.t_end_freq   = ls_freq.at(ls_freq.size()-1).toDouble();
        m_outdata.t_step_freq  = (m_outdata.t_end_freq - m_outdata.t_begin_freq)/(ls_freq.size()-1);
    }
    if(ls_freq.size() == 1)
    {
        m_outdata.t_begin_freq = ls_freq.at(0).toDouble();
        m_outdata.t_end_freq   = ls_freq.at(0).toDouble();
        m_outdata.t_step_freq  = 0;
    }
    m_outdata.t_begin_detector = map.min_d;
    m_outdata.t_end_detector   = map.max_d;
    m_outdata.t_begin_sweep    = map.min_p;
    m_outdata.t_end_sweep      = map.max_p;
    m_outdata.t_antenna_count  = map.count;

    StatusOutput::instance()->update(m_outdata);
}


OUTPUT_STATUS_DATA &RadarFace::get_outputdata()
{
    return m_outdata;
}

std::map<int, Radar *> &RadarFace::get_map_radars()
{
    return m_scene->get_map_radars();
}

std::vector<int> &RadarFace::get_radars_id()
{
    return m_radars_id;
}

void RadarFace::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QRectF rts(rect().left(), rect().top(), rect().width() -1, rect().height() -1);
    painter.setPen(QPen(QColor(155,155,155), 0));
    painter.drawRect(rts);

    QRectF rt(rect().left(), rect().top(), rect().width(), 50);
    QFont font(CVTS::GBKToUnicode::toUnicode("楷体"), 20, QFont::Bold);
    painter.setFont(font);
    painter.drawText(rt, Qt::AlignCenter, CVTS::GBKToUnicode::toUnicode(m_title.c_str()));
}

void RadarFace::Search_unit()
{
    SearchUnit::instance()->setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
    SearchUnit::instance()->showNormal();
}
void RadarFace::close_all()
{
    m_load_id.clear();
    std::map<int, Radar *>  ls_map = get_map_radars();
    if(ls_map.size() == 0) return;
    QColor def = QColor::fromRgbF(0, 1, 1, 1);
    std::map<int, Radar *>::iterator iter = ls_map.begin();
    while(iter!= ls_map.end())
    {
        iter->second->set_color(def);
        iter->second->turn_on_forever();
        ++iter;
    }
    update();
    repaint();
}

void RadarFace::update_unit_id(int id)
{
    std::map<int, Radar *>  ls_map = get_map_radars();
    if(ls_map.size() == 0) return;
    QColor red(255,0,0);
    if(ls_map.count(id)>0)
    {
        ls_map[id]->set_color(red);
        ls_map[id]->turn_on_forever();
    }
    update();
    repaint();
}


//////////////
/// \brief RadarFace::search_ids
/// \param p_path
///点击搜索功能后。。
void RadarFace::search_ids(QString p_path)
{
    std::map<int, Radar *>  ls_map = get_map_radars();
    if(ls_map.size() == 0) return;
    QColor red(255,255,0);
    QString path = p_path;
    QFile file(path);
    if(!file.open(QFile::ReadOnly | QIODevice::Text))
        qDebug()<< path << "open failed!";
    while(!file.atEnd())
    {
        QString line = file.readLine();
        line = line.trimmed();
        if(line.isEmpty()){
            continue;
        }
        int id = line.toInt();
        if(ls_map.count(id)>0)
        {
            if(m_load_id.count(id) > 0) continue;
            m_load_id[id] = id;
            ls_map[id]->set_color(red);
            ls_map[id]->turn_on_forever();
        }
    }
    update();
    repaint();
}

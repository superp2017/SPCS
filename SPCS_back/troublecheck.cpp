#include "troublecheck.h"

TroubleCheck::TroubleCheck(QWidget *parent) :
    QWidget(parent)
{
    m_view = 0;
    m_area = 0;
    m_scene = 0;
    m_export_btn =0;
}

TroubleCheck::~TroubleCheck()
{
    reset();
}

void TroubleCheck::init(QRect &rt)
{
    if(m_view != 0) return ;
    m_rt = rt;

    m_area = new QScrollArea();
    double dw = rt.width()-200;
    double dh = dw/(Grid_step_w * Grid_width) * (Grid_step_h * Grid_height);

    m_view_w = dw;
    m_view_h = dh;
    m_view = new RadarView(m_scene = new RadarScene(0,0,/*rt.width() - 200*/dw, dh/*rt.height()-100*/));
    connect(m_view, SIGNAL(full_screen(bool)), this, SLOT(full_screen(bool)));
    m_area->setParent(this);
    m_view->setGeometry(0,0,dw,dh);
    m_area->setWidget(m_view);
    m_area->setGeometry(80,50,/*rt.width()-200*/dw+20, rt.height()-100);
    m_area->showNormal();

    m_export_btn = new QPushButton(CVTS::GBKToUnicode::toUnicode("µ¼³öµ½Excle"), this);
    connect(m_export_btn, SIGNAL(clicked()), this, SLOT(export_excle()));
    m_export_btn->setGeometry(rt.width() - 90, rt.height() - 250, 90, 32);

    BkArea *area = new BkArea();
    QColor character(0,0,0);
    QColor back(100,205,225);
    area->set_color(back,character);
    area->has_text(true);
    area->setRect(0,0,dw, dh);
    area->setZValue(0);
    m_scene->addItem(area);

    QString ls_sheet = QString::fromUtf8("font: 10pt \"\346\245\267\344\275\223\";");
    this->setStyleSheet(ls_sheet);
       this->setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
}

void TroubleCheck::load_face(std::map<int,Radar *> &p_radars_map,std::vector<int> &p_radar_id,QString p_path)
{
    reset();
    m_save_path = p_path;
    if(p_radar_id.size() == p_radars_map.size() && p_radar_id.size()>0)
    {
        m_default_radars_map = p_radars_map;
        for(size_t i =0;i<p_radar_id.size();++i)
        {
            int id = p_radar_id.at(i);
            if(m_default_radars_map.count(id))
            {
                CVTS::SPoint sp;
                Radar *de    =  m_default_radars_map[id];
                CVTS::SPoint cur = de->get_default_point();
                int id       = de->id();
                int badnumn  = de->get_bad_num();
                bool bad     = de->isbad();
                if(!m_radars_map.count(id))
                {
                    m_trouble_table[id] = badnumn;
                    sp.x     =   cur.x;
                    sp.y     =   cur.y;
                    sp.z     =   cur.z;
                    Radar *r = new Radar(id, sp);
                    m_radars_id.push_back(id);
                    m_radars_map[id] = r;
                    r->setZValue(5);
                    QString str =CVTS::GBKToUnicode::toUnicode("ÕóÔª±àºÅ:")+QString("%1").arg(id) + \
                            CVTS::GBKToUnicode::toUnicode(" ¹ÊÕÏ±àºÅ:")+ QString("%1").arg(badnumn);
                    QColor red(255,0,0);
                    QColor green(0,255,0);
                    if(bad)
                        r->set_color(red);
                    else
                        r->set_color(green);
                    r->set_tip_text(str);
                    r->turn_on_forever();
                    m_scene->addItem(r);
                }
            }
        }
    }
}


void TroubleCheck::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QRectF rts(rect().left(), rect().top(), rect().width() -1, rect().height() -1);
    painter.setPen(QPen(QColor(155,155,155), 0));
    painter.drawRect(rts);

    QRectF rt(rect().left(), rect().top(), rect().width(), 50);
    QFont font(CVTS::GBKToUnicode::toUnicode("¿¬Ìå"), 20, QFont::Bold);
    painter.setFont(font);
    painter.drawText(rt, Qt::AlignCenter, CVTS::GBKToUnicode::toUnicode("µ¥Ôª¹ÊÕÏ¼ì²â"));
}

void TroubleCheck::reset()
{
    m_save_path.clear();
    m_scene->reset();
    m_radars_id.clear();
    m_radars_map.clear();
    m_trouble_table.clear();
    m_default_radars_map.clear();
}
void TroubleCheck::set_title(QString title)
{
    m_title = title;
}

void TroubleCheck::full_screen(bool full)
{
    if(full)
    {
        m_view->setParent(NULL);
        m_view->showFullScreen();
    }
    else
    {
        m_view->setParent(m_area);
        m_view->setGeometry(0,0,m_view_w, m_view_h);
        m_view->showNormal();
    }
}


void TroubleCheck::export_excle()
{
    QString t_filename ;
    if(m_save_path.isEmpty())t_filename = ProjectManager::instance()->get_path() + DATA_PATH + "/"+ UNIT_TROUBLE + ".xls";
    else t_filename = m_save_path + "/"+ UNIT_TROUBLE + ".xls";
    QString t_sheetname = CVTS::GBKToUnicode::toUnicode("µ¥Ôª¹ÊÕÏ±í");
    Book * book = xlCreateBook();
    if(book)
    {
        Format* format_title1 = book->addFormat();
        Font* font = book->addFont();
        font->setSize(14);
        font->setBold(true);
        format_title1->setAlignH(ALIGNH_CENTER);
        format_title1->setAlignV(ALIGNV_CENTER);
        format_title1->setNumFormat(NUMFORMAT_TEXT);
        format_title1->setBorder(BORDERSTYLE_THIN);
        format_title1->setFont(font);

        Format* format_title2 = book->addFormat();
        Font* fonttitle2 = book->addFont();
        fonttitle2->setSize(13);
        fonttitle2->setItalic(true);
        fonttitle2->setBold(true);
        format_title2->setAlignH(ALIGNH_CENTER);
        format_title2->setAlignV(ALIGNV_CENTER);
        format_title2->setNumFormat(NUMFORMAT_TEXT);
        format_title2->setBorder(BORDERSTYLE_THIN);
        format_title2->setFont(fonttitle2);

        Format* format_num = book->addFormat();
        Font* font1 = book->addFont();
        font1->setSize(12);
        format_num->setAlignH(ALIGNH_CENTER);
        format_num->setAlignV(ALIGNV_CENTER);
        format_num->setNumFormat(NUMFORMAT_NUMBER);
        format_num->setBorder(BORDERSTYLE_THIN);
        format_num->setFont(font1);

        Format* format_num2 = book->addFormat();
        Font* font11 = book->addFont();
        font11->setSize(12);
        font11->setColor(COLOR_RED);
        format_num2->setBorderColor(COLOR_RED);
        format_num2->setAlignH(ALIGNH_CENTER);
        format_num2->setAlignV(ALIGNV_CENTER);
        format_num2->setNumFormat(NUMFORMAT_NUMBER);
        format_num2->setBorder(BORDERSTYLE_THIN);
        format_num2->setFont(font11);



        Format* format_str = book->addFormat();
        Font* font2 = book->addFont();
        font2->setSize(12);
        format_str->setAlignH(ALIGNH_CENTER);
        format_str->setAlignV(ALIGNV_CENTER);
        format_str->setNumFormat(NUMFORMAT_TEXT);
        format_str->setBorder(BORDERSTYLE_THIN);
        format_str->setFont(font2);

        Format* format_str2 = book->addFormat();
        Font* font22 = book->addFont();
        font22->setSize(12);
        font22->setColor(COLOR_RED);
        format_str2->setBorderColor(COLOR_RED);
        format_str2->setAlignH(ALIGNH_CENTER);
        format_str2->setAlignV(ALIGNV_CENTER);
        format_str2->setNumFormat(NUMFORMAT_TEXT);
        format_str2->setBorder(BORDERSTYLE_THIN);
        format_str2->setFont(font22);



        Format* format_com = book->addFormat();
        format_com->setAlignH(ALIGNH_CENTER);
        format_com->setAlignV(ALIGNV_CENTER);
        format_com->setBorder(BORDERSTYLE_THIN);

        Format* format_background = book->addFormat();
        format_background->setAlignH(ALIGNH_CENTER);
        format_background->setAlignV(ALIGNV_CENTER);
        format_background->setFillPattern(FILLPATTERN_SOLID);
        format_background->setPatternForegroundColor(COLOR_LIGHTGREEN);

        Sheet* sheet = book->addSheet(t_sheetname.toLocal8Bit().data());
        if(sheet)
        {
            QString  tro_all = Trouble_all;
            QString  tro_0   = Trouble_0;
            QString  tro_1   = Trouble_1;
            QString  tro_2   = Trouble_2;
            QString  tro_3   = Trouble_3;
            QString  tro_4   = Trouble_4;
            QString  tro_5   = Trouble_5;
            QString  unit_num        = CVTS::GBKToUnicode::toUnicode("ÕóÔª±àºÅ");
            QString  istrouble       = CVTS::GBKToUnicode::toUnicode("ÊÇ·ñ¹ÊÕÏ");
            QString  troublenum      = CVTS::GBKToUnicode::toUnicode("¹ÊÕÏ±àºÅ");
            QString  trouble_table   = CVTS::GBKToUnicode::toUnicode("¹ÊÕÏ¶ÔÕÕ±í");
            QString  trouble_explain = CVTS::GBKToUnicode::toUnicode("¹ÊÕÏËµÃ÷");
            QString  p_is            = CVTS::GBKToUnicode::toUnicode("ÊÇ");
            QString  p_no            = CVTS::GBKToUnicode::toUnicode("·ñ");

            sheet->setMerge(0,0,0,2);
            sheet->setMerge(0,0,4,5);
            sheet->setCol(0,0,25);
            sheet->setCol(1,1,25);
            sheet->setCol(2,2,25);
            sheet->setCol(3,3,5);
            sheet->setCol(4,4,25);
            sheet->setCol(5,5,55);
            sheet->setCellFormat(0,1,format_com);
            sheet->setCellFormat(0,2,format_com);
            sheet->setCellFormat(0,5,format_com);

            sheet->writeStr(0,0,t_sheetname.toLocal8Bit().data(),format_title1);
            sheet->writeStr(1,0,unit_num.toLocal8Bit().data(),format_title2);
            sheet->writeStr(1,1,istrouble.toLocal8Bit().data(),format_title2);
            sheet->writeStr(1,2,troublenum.toLocal8Bit().data(),format_title2);
            sheet->writeStr(0,4,trouble_table.toLocal8Bit().data(),format_title1);
            sheet->writeStr(1,4,troublenum.toLocal8Bit().data(),format_title2);
            sheet->writeStr(1,5,trouble_explain.toLocal8Bit().data(),format_title2);
            if(m_radars_id.size()>0)
            {
                double size = m_radars_id.size();
                for(int i =0;i<size;++i)
                {
                    int id = m_radars_id.at(i);
                    if(m_trouble_table.size()>0)
                    {
                        if(m_trouble_table.count(id))
                        {
                            int num = m_trouble_table[id];
                            if(num ==1)
                            {
                                sheet->writeStr(i+2,1,p_no.toLocal8Bit().data(),format_str);
                                sheet->writeNum(i+2,0,id,format_num);
                                sheet->writeNum(i+2,2,num,format_num);
                            }
                            else
                            {
                                sheet->writeStr(i+2,1,p_is.toLocal8Bit().data(),format_str2);
                                sheet->writeNum(i+2,0,id,format_num2);
                                sheet->writeNum(i+2,2,num,format_num2);
                            }
                        }
                    }
                    sheet->setRow(i,25);
                }
                sheet->setRow(size,25);
                sheet->setRow(size+1,25);

                for(int i =0;i<64;++i)
                {
                    QString str;
                    if(i ==0)
                        str = tro_all;
                    if(i == 1)
                        str =  tro_0 ;
                    if(i>=2 && i<=7)
                        str = tro_1;
                    if(i>=8&&i<=13)
                        str = tro_5;
                    if(i>=14&&i<=28)
                        str = tro_2;
                    if(i>=29&&i<=43)
                        str = tro_4;
                    if(i>=44&&i<=63)
                        str = tro_3;
                    sheet->writeNum(i+2,4,i,format_num);
                    sheet->writeStr(i+2,5,str.toLocal8Bit().data(),format_str);
                }
                for(int i =0;i<66;++i)
                {
                    sheet->setCellFormat(i,3,format_background);
                }

                bool ret = book->save(t_filename.toLocal8Bit().data());
                if(!ret)
                {
                    FILE_IS_OPEN;
                    goto P_release;
                }
                system((QString("")+"start "  + t_filename).toLocal8Bit().data());
            }else
                goto P_release;
        }
        else
            goto P_release;
    }

P_release:
    book->release();
    return;
}

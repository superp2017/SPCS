#include "buziwidget.h"
#include "_global.h"
#include "mainwindow.h"
#include "tarray.h"
///
/// \brief BuziWidget::BuziWidget
/// \param parent 这里的许多做法是不好的，后面一定不要用
///

BuziWidget::BuziWidget(BuziScene *parent) :
    QGraphicsView(parent)
{
    setScene(m_sence = new BuziScene(0,0,400,400));
    connect(this, SIGNAL(muti_switch(int)), m_sence, SIGNAL(muti_switch(int)), Qt::QueuedConnection);
    connect(this, SIGNAL(switch_on(int)), m_sence, SLOT(switch_on(int)), Qt::QueuedConnection);
    connect(this, SIGNAL(switch_off(int)), m_sence, SLOT(switch_off(int)), Qt::QueuedConnection);
    connect(this, SIGNAL(detector_on(int)), m_sence, SLOT(detector_on(int)), Qt::QueuedConnection);
    connect(this, SIGNAL(detector_off(int)), m_sence, SLOT(detector_on(int)), Qt::QueuedConnection);
    connect(this, SIGNAL(scanner_pos(double)), m_sence, SLOT(scanner_pos(double)), Qt::QueuedConnection);
    connect(m_sence,SIGNAL(show_array()),this,SIGNAL(show_array()), Qt::QueuedConnection);
    setBackgroundBrush(QBrush(QColor(0,0,0)));

    showNormal();
}

BuziWidget::~BuziWidget()
{
    qDebug() << "BuziWidget::~BuziWidget()";
}

BuziWidget *BuziWidget::instance()
{
    static BuziWidget* bw = new BuziWidget;
    return bw;
}


BuziScene::BuziScene(qreal x, qreal y, qreal width, qreal height)
{
    m_x = x;
    m_y = y;
    m_w = width;
    m_h = height;

    init();

    //    connect(this, SIGNAL(switch_on_1()), m_electronic_switch_1, SLOT(switch_on()));
    //    connect(this, SIGNAL(switch_on_2()), m_electronic_switch_2, SLOT(switch_on()));
    //    connect(this, SIGNAL(switch_off_1()), m_electronic_switch_1, SLOT(switch_off()));
    //    connect(this, SIGNAL(switch_off_2()), m_electronic_switch_2, SLOT(switch_off()));
    connect(this, SIGNAL(muti_switch(int)), m_muti_switch, SLOT(muti_switch(int)));
}

void BuziScene::init()
{
    m_last_det_id = -1;
    m_last_ele_id = -1;
    for(int i=0; i<16; i++)
    {
        m_ele_id[i] = false;
    }

    QTextCodec *codec = QTextCodec::codecForName("GBK");

    ///////////////////////////////////////////////////////////////////////////////////////////
    //!


    QString string = codec->toUnicode("控制计算机");
    m_radar = new BuziUnit(string, QRectF(-600,190,100,50), BuziUnit::RoundRect);
    m_radar->show();
    m_radar->setZValue(5);
    addItem(m_radar);

    BuziLine *line = new BuziLine;
    line->push_back(QPointF(-500, 215));
    line->push_back(QPointF(-480, 215));
    line->valid_line();
    line->show();
    line->setZValue(5);
    addItem(line);

    string = codec->toUnicode("矢网");
    m_vna = new BuziUnit(string, QRectF(-480,190,100,50), BuziUnit::RoundRect);
    m_vna->show();
    m_vna->setZValue(5);
    addItem(m_vna);

    line = new BuziLine;
    line->push_back(QPointF(-380, 215));
    line->push_back(QPointF(-360, 215));
    line->set_line_color(QColor(125,255, 0));
    line->set_line_width(2);
    line->valid_line();
    line->show();
    line->setZValue(5);
    addItem(line);

    string = codec->toUnicode("");

    //    m_muti_switch = new BuziUnit(string, QRectF(-360,190,100,50), BuziUnit::MutiSwitch);
    //changed 2014/2/24   zhangbingyi
    //    m_muti_switch = new BuziUnit(string, QRectF(-360,140,100,150), BuziUnit::MutiSwitch);
    //    m_muti_switch->show();
    //    m_muti_switch->setZValue(16);//////////
    //    addItem(m_muti_switch);

    m_scanner = new BuziUnit(string, QRectF(-580,300,300,40), BuziUnit::Scanner);
    m_scanner->show();
    m_scanner->setZValue(5);
    addItem(m_scanner);

    string = codec->toUnicode("阵面");
    m_near_detector = new BuziUnit(string, QRectF(30,12,50,400), BuziUnit::RoundRect);
    m_near_detector->show();
    m_near_detector->setZValue(5);
    addItem(m_near_detector);
    connect(m_near_detector,SIGNAL(pressed()),this,SIGNAL(show_array()), Qt::QueuedConnection);
    string = codec->toUnicode("衰减器");
    m_attenuator = new BuziUnit(string, QRectF(-360,205,60,20), BuziUnit::RoundRect);
    m_attenuator->show();
    m_attenuator->setZValue(5);
    addItem(m_attenuator);

    line = new BuziLine;
    line->push_back(QPointF(-300, 215));
    line->push_back(QPointF(-270, 215));
    line->set_line_color(QColor(125,255, 0));
    line->set_line_width(2);
    line->valid_line();
    line->show();
    line->setZValue(5);
    addItem(line);

    string = codec->toUnicode("");
    m_muti_switch = new BuziUnit(string, QRectF(-270,35,100,360), BuziUnit::MutiSwitch);
    m_muti_switch->show();
    m_muti_switch->setZValue(5);
    addItem(m_muti_switch);

    string = codec->toUnicode("");
    m_electronic_switch[0] = new BuziUnit(string, QRectF(-170,10,100,50), BuziUnit::EleSwitch);
    m_electronic_switch[0]->set_id(1);
    m_electronic_switch[0]->show();
    m_electronic_switch[0]->setZValue(5);
    addItem(m_electronic_switch[0]);

    m_detector[0] = new BuziUnit(string, QRectF(-70,25,50,20), BuziUnit::Detector);
    m_detector[0]->show();
    m_detector[0]->setZValue(5);
    addItem(m_detector[0]);

    string = codec->toUnicode("");
    m_electronic_switch[1] = new BuziUnit(string, QRectF(-170,34,100,50), BuziUnit::EleSwitch);
    m_electronic_switch[1]->set_id(2);
    m_electronic_switch[1]->show();
    m_electronic_switch[1]->setZValue(5);
    addItem(m_electronic_switch[1]);

    m_detector[1] = new BuziUnit(string, QRectF(-70,49,50,20), BuziUnit::Detector);
    m_detector[1]->show();
    m_detector[1]->setZValue(5);
    addItem(m_detector[1]);

    string = codec->toUnicode("");
    m_electronic_switch[2] = new BuziUnit(string, QRectF(-170,58,100,50), BuziUnit::EleSwitch);
    m_electronic_switch[2]->set_id(3);
    m_electronic_switch[2]->show();
    m_electronic_switch[2]->setZValue(5);
    addItem(m_electronic_switch[2]);

    m_detector[2] = new BuziUnit(string, QRectF(-70,73,50,20), BuziUnit::Detector);
    m_detector[2]->show();
    m_detector[2]->setZValue(5);
    addItem(m_detector[2]);

    string = codec->toUnicode("");
    m_electronic_switch[3] = new BuziUnit(string, QRectF(-170,82,100,50), BuziUnit::EleSwitch);
    m_electronic_switch[3]->set_id(4);
    m_electronic_switch[3]->show();
    m_electronic_switch[3]->setZValue(5);
    addItem(m_electronic_switch[3]);

    m_detector[3] = new BuziUnit(string, QRectF(-70,97,50,20), BuziUnit::Detector);
    m_detector[3]->show();
    m_detector[3]->setZValue(5);
    addItem(m_detector[3]);

    string = codec->toUnicode("");
    m_electronic_switch[4] = new BuziUnit(string, QRectF(-170,106,100,50), BuziUnit::EleSwitch);
    m_electronic_switch[4]->set_id(5);
    m_electronic_switch[4]->show();
    m_electronic_switch[4]->setZValue(5);
    addItem(m_electronic_switch[4]);

    m_detector[4] = new BuziUnit(string, QRectF(-70,121,50,20), BuziUnit::Detector);
    m_detector[4]->show();
    m_detector[4]->setZValue(5);
    addItem(m_detector[4]);

    string = codec->toUnicode("");
    m_electronic_switch[5] = new BuziUnit(string, QRectF(-170,130,100,50), BuziUnit::EleSwitch);
    m_electronic_switch[5]->set_id(6);
    m_electronic_switch[5]->show();
    m_electronic_switch[5]->setZValue(5);
    addItem(m_electronic_switch[5]);

    m_detector[5] = new BuziUnit(string, QRectF(-70,145,50,20), BuziUnit::Detector);
    m_detector[5]->show();
    m_detector[5]->setZValue(5);
    addItem(m_detector[5]);

    string = codec->toUnicode("");
    m_electronic_switch[6] = new BuziUnit(string, QRectF(-170,154,100,50), BuziUnit::EleSwitch);
    m_electronic_switch[6]->set_id(7);
    m_electronic_switch[6]->show();
    m_electronic_switch[6]->setZValue(5);
    addItem(m_electronic_switch[6]);

    m_detector[6] = new BuziUnit(string, QRectF(-70,169,50,20), BuziUnit::Detector);
    m_detector[6]->show();
    m_detector[6]->setZValue(5);
    addItem(m_detector[6]);

    string = codec->toUnicode("");
    m_electronic_switch[7] = new BuziUnit(string, QRectF(-170,178,100,50), BuziUnit::EleSwitch);
    m_electronic_switch[7]->set_id(8);
    m_electronic_switch[7]->show();
    m_electronic_switch[7]->setZValue(5);
    addItem(m_electronic_switch[7]);

    m_detector[7] = new BuziUnit(string, QRectF(-70,193,50,20), BuziUnit::Detector);
    m_detector[7]->show();
    m_detector[7]->setZValue(5);
    addItem(m_detector[7]);

    string = codec->toUnicode("");
    m_electronic_switch[8] = new BuziUnit(string, QRectF(-170,202,100,50), BuziUnit::EleSwitch);
    m_electronic_switch[8]->set_id(9);
    m_electronic_switch[8]->show();
    m_electronic_switch[8]->setZValue(5);
    addItem(m_electronic_switch[8]);

    m_detector[8] = new BuziUnit(string, QRectF(-70,217,50,20), BuziUnit::Detector);
    m_detector[8]->show();
    m_detector[8]->setZValue(5);
    addItem(m_detector[8]);

    string = codec->toUnicode("");
    m_electronic_switch[9] = new BuziUnit(string, QRectF(-170,226,100,50), BuziUnit::EleSwitch);
    m_electronic_switch[9]->set_id(10);
    m_electronic_switch[9]->show();
    m_electronic_switch[9]->setZValue(5);
    addItem(m_electronic_switch[9]);

    m_detector[9] = new BuziUnit(string, QRectF(-70,241,50,20), BuziUnit::Detector);
    m_detector[9]->show();
    m_detector[9]->setZValue(5);
    addItem(m_detector[9]);

    string = codec->toUnicode("");
    m_electronic_switch[10] = new BuziUnit(string, QRectF(-170,250,100,50), BuziUnit::EleSwitch);
    m_electronic_switch[10]->set_id(11);
    m_electronic_switch[10]->show();
    m_electronic_switch[10]->setZValue(5);
    addItem(m_electronic_switch[10]);

    m_detector[10] = new BuziUnit(string, QRectF(-70,265,50,20), BuziUnit::Detector);
    m_detector[10]->show();
    m_detector[10]->setZValue(5);
    addItem(m_detector[10]);

    string = codec->toUnicode("");
    m_electronic_switch[11] = new BuziUnit(string, QRectF(-170,274,100,50), BuziUnit::EleSwitch);
    m_electronic_switch[11]->set_id(12);
    m_electronic_switch[11]->show();
    m_electronic_switch[11]->setZValue(5);
    addItem(m_electronic_switch[11]);

    m_detector[11] = new BuziUnit(string, QRectF(-70,289,50,20), BuziUnit::Detector);
    m_detector[11]->show();
    m_detector[11]->setZValue(5);
    addItem(m_detector[11]);

    string = codec->toUnicode("");
    m_electronic_switch[12] = new BuziUnit(string, QRectF(-170,298,100,50), BuziUnit::EleSwitch);
    m_electronic_switch[12]->set_id(13);
    m_electronic_switch[12]->show();
    m_electronic_switch[12]->setZValue(5);
    addItem(m_electronic_switch[12]);

    m_detector[12] = new BuziUnit(string, QRectF(-70,313,50,20), BuziUnit::Detector);
    m_detector[12]->show();
    m_detector[12]->setZValue(5);
    addItem(m_detector[12]);

    string = codec->toUnicode("");
    m_electronic_switch[13] = new BuziUnit(string, QRectF(-170,322,100,50), BuziUnit::EleSwitch);
    m_electronic_switch[13]->set_id(14);
    m_electronic_switch[13]->show();
    m_electronic_switch[13]->setZValue(5);
    addItem(m_electronic_switch[13]);

    m_detector[13] = new BuziUnit(string, QRectF(-70,337,50,20), BuziUnit::Detector);
    m_detector[13]->show();
    m_detector[13]->setZValue(5);
    addItem(m_detector[13]);

    string = codec->toUnicode("");
    m_electronic_switch[14] = new BuziUnit(string, QRectF(-170,346,100,50), BuziUnit::EleSwitch);
    m_electronic_switch[14]->set_id(15);
    m_electronic_switch[14]->show();
    m_electronic_switch[14]->setZValue(5);
    addItem(m_electronic_switch[14]);

    m_detector[14] = new BuziUnit(string, QRectF(-70,361,50,20), BuziUnit::Detector);
    m_detector[14]->show();
    m_detector[14]->setZValue(5);
    addItem(m_detector[14]);

    string = codec->toUnicode("");
    m_electronic_switch[15] = new BuziUnit(string, QRectF(-170,370,100,50), BuziUnit::EleSwitch);
    m_electronic_switch[15]->set_id(16);
    m_electronic_switch[15]->show();
    m_electronic_switch[15]->setZValue(5);
    addItem(m_electronic_switch[15]);

    m_detector[15] = new BuziUnit(string, QRectF(-70,385,50,20), BuziUnit::Detector);
    m_detector[15]->show();
    m_detector[15]->setZValue(5);
    addItem(m_detector[15]);


    line = new BuziLine;
    line->push_back(QPointF(-600, 215));
    line->push_back(QPointF(-620, 215));
    line->push_back(QPointF(-620, 320));
    line->push_back(QPointF(-580, 320));
    line->valid_line();
    line->show();
    line->setZValue(5);
    addItem(line);

    line = new BuziLine;
    line->push_back(QPointF(-620, 320));
    line->push_back(QPointF(-620, 450));
    line->push_back(QPointF(55, 450));
    line->push_back(QPointF(55, 412));
    line->valid_line();
    line->show();
    line->setZValue(5);
    addItem(line);

    line = new BuziLine;
    line->push_back(QPointF(-430, 190));
    line->push_back(QPointF(-430, -10));
    line->push_back(QPointF(55, -10));
    line->push_back(QPointF(55, 12));
    line->set_line_color(QColor(125,255, 0));
    line->set_line_width(2);
    line->valid_line();
    line->show();
    line->setZValue(5);
    addItem(line);

    string = codec->toUnicode("");
    m_electronic_switch[16] = new BuziUnit(string, QRectF(-170, -35, 100, 50), BuziUnit::EleSwitch);
    m_electronic_switch[16]->set_id(17);
    m_electronic_switch[16]->show();
    m_electronic_switch[16]->setZValue(5);
    addItem(m_electronic_switch[16]);
}


BuziLine::BuziLine(QGraphicsItem *parent)
    : m_line_color(255, 255,255)
{
    m_count = 0;
    m_line_width = 1;
}

void BuziLine::push_back(QPointF &pt)
{
    m_pts.push_back(pt);
}

void BuziLine::valid_line()
{
    m_count = m_pts.size();
    if(m_count < 2) return ;
    m_line_path.moveTo(m_pts[0]);
    for(int i=1; i<m_pts.size(); i++)
    {
        m_line_path.lineTo(m_pts[i]);
    }
    update();
}

void BuziLine::set_line_width(double w)
{
    m_line_width = w;
}

void BuziLine::set_line_color(QColor c)
{
    m_line_color = c;
}

QRectF BuziLine::boundingRect() const
{
    return m_line_path.boundingRect();
}

void BuziLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(m_count < 2) return;
    painter->setPen(QPen(m_line_color, m_line_width));
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawPath(m_line_path);
}


BuziUnit::BuziUnit(QString &text, QRectF rect, BuziUnit::UniType type, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    m_text(text),
    m_type(type),
    m_rect(rect),
    m_fill_rect(rect.left()+1, rect.top()+1, rect.width()-2, rect.height()-2),
    m_high_color(QColor(15,155,15)),
    m_low_color(QColor(55,100,55)),
    m_pen_color(QColor(0,0,0)),
    m_switch_color(QColor(0,0,0)),
    m_detector_color(0,0,0),
    m_top(rect.left() + rect.width()/2, rect.top()),
    m_bottom(rect.left() + rect.width()/2, rect.bottom()),
    m_left(rect.left(), rect.top() + rect.height()/2),
    m_right(rect.right(), rect.top() + rect.height()/2)
{
    m_muti_pts = new QPointF[SPCS_Muti_N];
    m_pressed = false;
    m_muti_id = 0;

    m_scanner_pos = 0;
    m_id = -1;
    m_detector_width = 1;

    switch (m_type) {
    case RoundRect:
    {
        m_paint_path.addRoundedRect(m_rect, 10, 10);
        m_fill_path.addRoundedRect(m_fill_rect, 10, 10);
        break;
    }
    case Rect:
    {
        m_paint_path.addRect(m_rect);
        m_fill_path.addRect(m_fill_rect);
        break;
    }
    case Ecllipse:
    {
        m_paint_path.addEllipse(m_rect);
        m_fill_path.addEllipse(m_fill_rect);
        break;
    }
    case Detector:
    {
        double midw = m_rect.width() / 4;
        m_paint_path.moveTo(m_rect.left(), m_rect.top() + m_rect.height() / 2);
        m_paint_path.lineTo(m_rect.left() + midw, m_rect.top() + m_rect.height() / 2);
        m_paint_path.moveTo(m_rect.left() + midw, m_rect.top() + m_rect.height() / 2);
        m_paint_path.lineTo(m_rect.right() - midw, m_rect.top() + m_rect.height() / 5);
        m_paint_path.moveTo(m_rect.left() + midw, m_rect.top() + m_rect.height() / 2);
        m_paint_path.lineTo(m_rect.right() - midw, m_rect.bottom() - m_rect.height() / 5);
        m_paint_path.closeSubpath();
        break;
    }
    case Scanner:
    {
        double midh = m_rect.height() / 4;
        m_paint_path.moveTo(m_rect.left(), m_rect.top() + midh);
        m_paint_path.lineTo(m_rect.left(), m_rect.bottom());
        m_paint_path.moveTo(m_rect.left(), m_rect.bottom() - m_rect.height() / 2);
        m_paint_path.lineTo(m_rect.right(), m_rect.bottom() - m_rect.height() / 2);
        m_paint_path.moveTo(m_rect.right(), m_rect.top() + midh);
        m_paint_path.lineTo(m_rect.right(), m_rect.bottom());
        double len = m_rect.width() / 30;
        double yc = 1.5;
        for(int i=1; i<16; i++)
        {
            if(i%2 == 0) yc = 1.5;
            else yc = 1.0;
            m_paint_path.moveTo(m_rect.left() + len * i, m_rect.top() + m_rect.height() / 2);
            m_paint_path.lineTo(m_rect.left() + len * i, m_rect.bottom() - midh*yc);
            m_paint_path.moveTo(m_rect.right() - len * i, m_rect.top() + m_rect.height() / 2);
            m_paint_path.lineTo(m_rect.right() - len * i, m_rect.bottom() - midh*yc);
        }
        m_paint_path.moveTo(m_rect.left() + m_rect.width() / 2, m_rect.top() + m_rect.height() / 2);
        m_paint_path.lineTo(m_rect.left() + m_rect.width() / 2, m_rect.bottom() - midh);
        m_paint_path.closeSubpath();
        break;
    }
    case Prismatic:
    {
        m_paint_path.moveTo(m_rect.left() + m_rect.width()/2, m_rect.top());
        m_paint_path.lineTo(m_rect.right(), m_rect.top() + m_rect.height()/2);
        m_paint_path.lineTo(m_rect.left() + m_rect.width()/2, m_rect.bottom());
        m_paint_path.lineTo(m_rect.left(), m_rect.top() + m_rect.height()/2);
        m_paint_path.closeSubpath();

        m_fill_path.moveTo(m_fill_rect.left() + m_fill_rect.width()/2, m_fill_rect.top());
        m_fill_path.lineTo(m_fill_rect.right(), m_fill_rect.top() + m_fill_rect.height()/2);
        m_fill_path.lineTo(m_fill_rect.left() + m_fill_rect.width()/2, m_fill_rect.bottom());
        m_fill_path.lineTo(m_fill_rect.left(), m_fill_rect.top() + m_fill_rect.height()/2);
        m_fill_path.closeSubpath();
        break;
    }
    case EleSwitch:
    {
        m_paint_path.moveTo(m_rect.left(), m_rect.top() + m_rect.height()/2);
        m_paint_path.lineTo(m_rect.left() + m_rect.width()/3, \
                            m_rect.top() + m_rect.height()/2);
        m_paint_path.moveTo(m_rect.left() + m_rect.width()/2, m_rect.top() + m_rect.height()/2);
        m_paint_path.lineTo(m_rect.right(), \
                            m_rect.top() + m_rect.height()/2);
        m_paint_path.moveTo(m_rect.left() + m_rect.width()/2, \
                            m_rect.top() + m_rect.height()/3);
        m_paint_path.lineTo(m_rect.left() + m_rect.width()/2, \
                            m_rect.top() + m_rect.height()*2.0/3);
        m_paint_path.moveTo(m_rect.left() + m_rect.width()/3, \
                            m_rect.top() + m_rect.height()/3);
        m_paint_path.lineTo(m_rect.left() + m_rect.width()/2, \
                            m_rect.top() + m_rect.height()/2);
        m_paint_path.lineTo(m_rect.left() + m_rect.width()/3, \
                            m_rect.top() + m_rect.height()*2.0/3);

        m_paint_path.closeSubpath();

        m_fill_path.moveTo(m_rect.left() + m_rect.width()/3, \
                           m_rect.top() + m_rect.height()/3);
        m_fill_path.lineTo(m_rect.left() + m_rect.width()/2, \
                           m_rect.top() + m_rect.height()/2);
        m_fill_path.lineTo(m_rect.left() + m_rect.width()/3, \
                           m_rect.top() + m_rect.height()*2.0/3);
        m_fill_path.closeSubpath();
        break;
    }case MutiSwitch:
    {
        m_paint_path.moveTo(m_rect.left(), m_rect.top() + m_rect.height()/2);
        m_paint_path.lineTo(m_rect.left() + m_rect.width()/4, \
                            m_rect.top() + m_rect.height()/2);

        m_muti_begin_pts.setX(m_rect.left() + m_rect.width()/4);
        m_muti_begin_pts.setY(m_rect.top() + m_rect.height()/2);


        //        m_paint_path.moveTo(m_rect.right(), m_rect.top() + m_rect.height()/2);
        //        m_paint_path.lineTo(m_rect.right() - m_rect.width()/4, \
        //                            m_rect.top() + m_rect.height()/2);

        m_paint_path.moveTo(m_rect.right() - m_rect.width()/4, \
                            m_rect.top());
        m_paint_path.lineTo(m_rect.right() - m_rect.width()/4, \
                            m_rect.bottom());


        float step = m_rect.height() / (SPCS_Muti_N-1.0f);
        float len = m_rect.width() / 5;

        for(int i=0; i<SPCS_Muti_N; i++)
        {
            m_paint_path.moveTo(m_rect.right() - m_rect.width()/4,
                                m_rect.top() + step * i);
            m_paint_path.lineTo(m_rect.right(),
                                m_rect.top() + step * i);
            m_muti_pts[i].setX(m_rect.right() - m_rect.width()/4);
            m_muti_pts[i].setY(m_rect.top() + step * i);
        }
        m_paint_path.closeSubpath();

        break;
    }
    default:
        break;
    }

    m_color_map[Unit_Init].first = m_high_color;
    m_color_map[Unit_Init].second = m_low_color;

    m_color_map[Unit_Normal].first = m_high_color;
    m_color_map[Unit_Normal].second = m_low_color;

    m_color_map[Unit_Warning].first = m_high_color;
    m_color_map[Unit_Warning].second = m_low_color;

    m_color_map[Unit_Error].first = m_high_color;
    m_color_map[Unit_Error].second = m_low_color;

    m_color_map[Unit_Finish].first = m_high_color;
    m_color_map[Unit_Finish].second = m_low_color;

    m_status = Unit_Normal;
}

void BuziUnit::set_status(BuziUnit::UnitStatus status)
{
    m_status = status;
}

BuziUnit::UnitStatus BuziUnit::status()
{
    return m_status;
}

void BuziUnit::actions()
{

}

void BuziUnit::init_widgets()
{

}


void BuziUnit::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit pressed();
    m_pressed = true;
    update();
}

void BuziUnit::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_pressed = false;
    update();
}

void BuziUnit::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);

    if(m_type == EleSwitch)
    {
        painter->setPen(QPen(QColor(125,255,0), 1));
        painter->fillPath(m_fill_path, QBrush(m_switch_color));
        if(m_id > 0 && m_id <= CVTS::CD_NUMS)
        {
            QRect rt(m_rect.left() +12, m_rect.top(), 24,32);
            painter->drawText(rt, Qt::AlignCenter, QString::number(m_id));
        }

    }else if(m_type == MutiSwitch)
    {
        if(m_muti_id != -1)
        {
            painter->setPen(QPen(QColor(125,255,0), 1));
            QPointF pts(m_muti_begin_pts.x(), m_muti_pts[m_muti_id].y());
            painter->setPen(QColor(125,255,0));
            painter->drawLine(m_muti_begin_pts, pts);
            painter->drawLine(pts, m_muti_pts[m_muti_id]);
        }

    }else if(m_type == Detector)
    {
        painter->setPen(QPen(m_detector_color, m_detector_width));
    }else if(m_type == Scanner)
    {
        painter->setPen(QPen(QColor(255,125,0), 1));
        double dc = m_rect.width()/30;
        QPointF pt1(m_rect.left() + m_rect.width() / 2 + m_scanner_pos * dc, \
                    m_rect.top() + m_rect.height() / 2);
        QPointF pt2(m_rect.left() + m_rect.width() / 2 + m_scanner_pos * dc - 3, \
                    m_rect.top() + m_rect.height() / 2 - 10);
        QPointF pt3(m_rect.left() + m_rect.width() / 2 + m_scanner_pos * dc + 3, \
                    m_rect.top() + m_rect.height() / 2 - 10);
        QPainterPath ls_paint_path;
        ls_paint_path.moveTo(pt1);
        ls_paint_path.lineTo(pt2);
        ls_paint_path.lineTo(pt3);
        ls_paint_path.lineTo(pt1);
        ls_paint_path.closeSubpath();
        painter->fillPath(ls_paint_path, QBrush(QColor(255, 125, 0)));

        painter->setPen(QPen(QColor(255,255,255), 1));
        double len = m_rect.width() / 30;
        double yc = 1.5;
        double midh = m_rect.height() / 4;
        QRect ls_rt(m_rect.left() + m_rect.width() / 2 - 9, \
                    m_rect.bottom() - midh, 18, 24);
        painter->drawText(ls_rt, Qt::AlignCenter, "0");

        QRect L_rt(ls_rt);
        QRect R_rt(ls_rt);
        for(int i=1; i<=3; i++)
        {
            L_rt.setLeft(ls_rt.left() + len * 8 * i);
            painter->drawText(L_rt, Qt::AlignCenter, QString::number(i * 2));

            R_rt.setLeft(ls_rt.left() - len * 8 * i);
            painter->drawText(R_rt, Qt::AlignCenter, QString::number(-i * 2));
        }

        QTextCodec *codec = QTextCodec::codecForName("GBK");
        QRect rt(m_rect.left() + m_rect.width()/2 - 50, m_rect.top() - 20, 100, 40);
        painter->drawText(rt, Qt::AlignCenter, codec->toUnicode("扫描架"));
    }else
    {
        painter->setPen(QPen(QColor(255,255,255), 1));

        if(m_pressed)
        {
            QBrush brush(m_color_map[m_status].second);
            painter->fillPath(m_fill_path, brush);
        }else
        {
            QBrush brush(m_color_map[m_status].first);
            painter->fillPath(m_fill_path, brush);
        }

        painter->drawText(m_fill_rect,Qt::AlignCenter, m_text);
    }
    painter->drawPath(m_paint_path);
}

QRectF BuziUnit::boundingRect() const
{
    return m_rect;
}


void BuziScene::switch_on(int id)
{
    if(id == 16) {m_electronic_switch[id]->switch_on(); return ;}
    if(id > 15 || id < 0) return;
    if(m_last_ele_id != id && m_last_ele_id != -1) m_electronic_switch[m_last_ele_id]->switch_off();
    m_electronic_switch[id]->switch_on();
    m_last_ele_id = id;
}

void BuziScene::switch_off(int id)
{
    if(id > 16 || id < 0) return;
    m_electronic_switch[id]->switch_off();
}

void BuziScene::detector_on(int id)
{
    if(id < 0 || id > 15) return ;
    if(m_last_det_id != id && m_last_det_id != -1) m_detector[m_last_det_id]->detector_off();
    m_detector[id]->detector_on();
    m_last_det_id = id;
}

void BuziScene::detector_off(int id)
{
    if(id < 0 || id > 15) return ;
    m_detector[id]->detector_off();
}

void BuziScene::scanner_pos(double pos)
{
    m_scanner->scanner_pos(pos);
}



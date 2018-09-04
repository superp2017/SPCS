#include "statusoutput.h"
#include "m_setfreqdlg.h"

StatusOutput::StatusOutput(QWidget *parent) :
    QWidget(parent),
    m_staTitle(this),
    m_grid_layout(this),
    m_Proj_title_item(new QStandardItem()),
    m_Proj_name_item(new QStandardItem()),
    m_item_1(new QStandardItem()),
    m_item_2(new QStandardItem()),
    m_item_3(new QStandardItem()),
    m_item_4(new QStandardItem()),
    m_item_5(new QStandardItem()),
    m_item_6(new QStandardItem()),
    m_item_7(new QStandardItem())
{

    m_Proj_title_item->setEditable(false);
    m_Proj_name_item->setEditable(false);

    m_item_1->setEditable(false);
    m_item_2->setEditable(false);
    m_item_3->setEditable(false);
    m_item_4->setEditable(false);
    m_item_5->setEditable(false);
    m_item_6->setEditable(false);
    m_item_7->setEditable(false);

    m_listModel.appendRow(m_Proj_title_item);
    m_listModel.appendRow(m_Proj_name_item);

    m_listModel.appendRow(m_item_1);
    m_listModel.appendRow(m_item_2);
    m_listModel.appendRow(m_item_3);
    m_listModel.appendRow(m_item_4);
    m_listModel.appendRow(m_item_5);
    m_listModel.appendRow(m_item_6);
    m_listModel.appendRow(m_item_7);

    m_listView.setModel(&m_listModel);
    m_grid_layout.addWidget(&m_staTitle,0, 0);
    m_grid_layout.addWidget(&m_listView, 1, 0);

    m_grid_layout.setRowStretch(0,1);
    m_grid_layout.setRowStretch(1,8);
    m_grid_layout.setSpacing(0);
    m_staTitle.setFixedHeight(20);
    m_grid_layout.setContentsMargins(0,0,0,0);
    QString ls_sheet = QString::fromUtf8("font: 11pt \"\346\245\267\344\275\223\";");
    this->setStyleSheet(ls_sheet);
    setLayout(&m_grid_layout);
    init_data();
    update_value();

}

void StatusOutput::init_data()
{
    m_default_data.t_begin_freq = 0;
    m_default_data.t_end_freq = 0;
    m_default_data.t_step_freq = 0;
    m_default_data.t_begin_detector =0;
    m_default_data.t_end_detector = 0;
    m_default_data.t_begin_sweep = 0;
    m_default_data.t_end_sweep = 0;
    m_default_data.t_antenna_count = 0;
}

void StatusOutput::update_value()
{
    char buf[1024];

    m_Proj_title_item->setText(GBKToUnicode::toUnicode("工程名字:"));

    QString name = "       "+m_Proj_name;
    m_Proj_name_item->setText(GBKToUnicode::toUnicode(name));



    char buf_start[1024];
    char buf_end[1024];
    char buf_step[1024];
    to_freq_string(m_default_data.t_begin_freq,buf_start);
    to_freq_string(m_default_data.t_end_freq,buf_end);
    to_freq_string(m_default_data.t_step_freq,buf_step);

   m_item_1->setText(GBKToUnicode::toUnicode("测试频率:"));
    sprintf(buf, "  起始:%s \n  结束:%s \n  间隔:%s",buf_start ,buf_end , buf_step);
    m_item_2->setText(CVTS::GBKToUnicode::toUnicode(buf));

    m_item_3->setText(CVTS::GBKToUnicode::toUnicode("测试探头："));

    sprintf(buf, "  起始:%d      \n  结束:%d", m_default_data.t_begin_detector, m_default_data.t_end_detector);
    m_item_4->setText(CVTS::GBKToUnicode::toUnicode(buf));

    m_item_5->setText(CVTS::GBKToUnicode::toUnicode("扫描架位置："));

    sprintf(buf, "  起始:%d      \n  结束:%d", m_default_data.t_begin_sweep, m_default_data.t_end_sweep);
    m_item_6->setText(CVTS::GBKToUnicode::toUnicode(buf));

    sprintf(buf, "  待测天线单元总数:%d", m_default_data.t_antenna_count);
    m_item_7->setText(CVTS::GBKToUnicode::toUnicode(buf));
}


void StatusOutput::update_proj_name(QString &p_name)
{
    m_Proj_name = p_name;
    update_value();
}

void StatusOutput::update(OUTPUT_STATUS_DATA &data)
{
    m_default_data.t_begin_detector = data.t_begin_detector;
    m_default_data.t_end_detector   = data.t_end_detector;
    m_default_data.t_begin_sweep    = data.t_begin_sweep;
    m_default_data.t_end_sweep      = data.t_end_sweep;
    m_default_data.t_antenna_count  = data.t_antenna_count;
    updata_freq(data.t_begin_freq,data.t_end_freq,data.t_step_freq);
}

void StatusOutput::updata_freq(double start, double end, double step)
{
    m_default_data.t_begin_freq   =     start;
    m_default_data.t_end_freq     =     end;
    m_default_data.t_step_freq    =     step;
    update_value();
}

void StatusOutput::reset()
{
    init_data();
    update_value();
}

void StatusOutput::setenable(bool enable)
{
    setEnabled(enable);
}

//void StatusOutput::paintEvent(QPaintEvent *event)
//{
//    QPainter painter(this);

//    QRectF rt(rect().left(), rect().top(), rect().width() -1, rect().height() -1);
//    painter.setPen(QPen(QColor(155,155,155), 0));
//    painter.drawRect(rt);


//    painter.setPen(QPen(QColor(55,55,55), 0));
//    int h = rect().height() / 7;
//    QRectF rt_1(rect().left(), rect().top(), rect().width(), h);
//    painter.drawText(rt_1, Qt::AlignVCenter | Qt::AlignLeft, CVTS::GBKToUnicode::toUnicode(" 测试频率："));

//    sprintf(buf, " 起始:%s结束:%s间隔:%s", to_freq_string(m_begin_freq), \
//            to_freq_string(m_end_freq), to_freq_string(m_step_freq));
//    QRectF rt_2(rect().left(), rect().top() + h, rect().width(), h);
//    painter.drawText(rt_2, Qt::AlignVCenter | Qt::AlignLeft, CVTS::GBKToUnicode::toUnicode(buf));

//    QRectF rt_3(rect().left(), rect().top() + h*2, rect().width(), h);
//    painter.drawText(rt_3, Qt::AlignVCenter | Qt::AlignLeft, CVTS::GBKToUnicode::toUnicode(" 测试探头："));

//    sprintf(buf, " 起始:%d 结束:%d", m_begin_detector, m_end_detector);
//    QRectF rt_4(rect().left(), rect().top() + h*3, rect().width(), h);
//    painter.drawText(rt_4, Qt::AlignVCenter | Qt::AlignLeft, CVTS::GBKToUnicode::toUnicode(buf));

//    QRectF rt_5(rect().left(), rect().top() + h*4, rect().width(), h);
//    painter.drawText(rt_5, Qt::AlignVCenter | Qt::AlignLeft, CVTS::GBKToUnicode::toUnicode(" 扫描架位置："));

//    sprintf(buf, " 起始:%d 结束:%d", m_begin_sweep, m_end_sweep);
//    QRectF rt_6(rect().left(), rect().top() + h*5, rect().width(), h);
//    painter.drawText(rt_6, Qt::AlignVCenter | Qt::AlignLeft, CVTS::GBKToUnicode::toUnicode(buf));

//    sprintf(buf, " 待测天线单元总数:%d", m_antenna_count);
//    QRectF rt_7(rect().left(), rect().top() + h*6, rect().width(), h);
//    painter.drawText(rt_7, Qt::AlignVCenter | Qt::AlignLeft, CVTS::GBKToUnicode::toUnicode(buf));
//}

//void StatusOutput::resizeEvent(QResizeEvent *event)
//{
//    QWidget::resizeEvent(event);
//    m_staTitle.setGeometry(0,0,event->size().width(), 20);
//}
//////////////////
/// \brief StatusOutput::to_freq_string
/// \param value
///20
void StatusOutput::to_freq_string(double value,char (&str_data)[1024])
{
    if(value < FREQ_K)
    {
        sprintf(str_data, "%.1fHz", value);
    }else if(value < FREQ_M)
    {
        sprintf(str_data, "%.1fKHz", value/FREQ_K);
    }else if(value < FREQ_G)
    {
        sprintf(str_data, "%.1fMHz", value/FREQ_M);
    }else
    {
        sprintf(str_data, "%.1fGHz", value/FREQ_G);
    }
}



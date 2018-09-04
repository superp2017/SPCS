#include "t_right.h"

T_Right::T_Right(QWidget *parent) :
    QWidget(parent),
    m_grid_layout(this)
{
    ls_group = new QGroupBox(this);
    QString ls_name = CVTS::GBKToUnicode::toUnicode("·µ»Ø");
    m_return = new QPushButton(ls_name);
    m_return->setParent(ls_group);

    QString ls_stop = CVTS::GBKToUnicode::toUnicode("Ç¿ÖÆÍ£Ö¹");
    m_stop = new QPushButton(ls_stop);
    m_stop->setParent(ls_group);
    ls_group->setFixedHeight(45);

    m_grid_layout.addWidget(&m_view, 0,0);
    m_grid_layout.addWidget(ls_group,1,0);
    m_grid_layout.setRowStretch(0,5);
    m_grid_layout.setRowStretch(1,1);
    m_grid_layout.setSpacing(2);
    m_grid_layout.setContentsMargins(1,1,1,1);

    setLayout(&m_grid_layout);
    connect(m_return,SIGNAL(clicked()),this,SIGNAL(back()),Qt::QueuedConnection);
    connect(m_stop,SIGNAL(clicked()),this,SIGNAL(StopTest()),Qt::QueuedConnection);

    m_return->setEnabled(true);
}



void T_Right::resizeEvent(QResizeEvent *e)
{

    m_return->setGeometry(ls_group->width() - 80,5,70,37);
    m_stop->setGeometry(ls_group->width() - 200,5,70,37);
    QWidget::resizeEvent(e);
}


void T_Right::UpdateData(int _ID, double freq_, double _M, double _P)
{
    m_view.UpdateData(_ID,freq_,_M,_P);
}

void T_Right::enableReturn(bool res)
{
    m_return->setEnabled(res);
}

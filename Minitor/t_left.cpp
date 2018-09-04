#include "t_left.h"

T_Left::T_Left(QWidget *parent) :
    QWidget(parent),
    m_grid_layout(this),
    m_up(new QWidget(this)),
    m_down(new QWidget(this))
{
    set_layout();
    setLayout(&m_grid_layout);
}

void T_Left::Set_up_widget(QWidget *up_)
{
    if(!up_)
        return;
    if(up_ == m_up)
        return;
    if(m_up)
        m_up->hide();
    m_up    = up_;
    set_layout();
}

void T_Left::Set_down_widget(QWidget *down_)
{
    if(!down_)
        return;
    if(down_ == m_down)
        return;
    if(m_down)
        m_down->hide();
    m_down    = down_;
    set_layout();
}

void T_Left::set_layout()
{
    m_grid_layout.addWidget(m_up,0,0);
    m_grid_layout.addWidget(m_down,1,0);
    m_grid_layout.setRowStretch(0,5);
    m_grid_layout.setRowStretch(1,2);
    m_grid_layout.setSpacing(2);
    m_grid_layout.setContentsMargins(1,1,1,1);
}

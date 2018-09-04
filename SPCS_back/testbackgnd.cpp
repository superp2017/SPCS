#include "testbackgnd.h"
#include "workbench.h"

TestBackgnd::TestBackgnd(QWidget *parent) :
    QWidget(parent),
    m_grid_layout(this)
{
    m_left.setOrientation(Qt::Vertical);
    m_grid_layout.addWidget(&m_left,0,0);
    m_grid_layout.addWidget(&m_right,0,1);
    m_grid_layout.setColumnStretch(0,5);
    m_grid_layout.setColumnStretch(1,1);
    m_grid_layout.setContentsMargins(1,1,1,1);
    setLayout(&m_grid_layout);
}

void TestBackgnd::keyPressEvent(QKeyEvent *e)
{
    if(Qt::ControlModifier == e->modifiers() && Qt::Key_F == e->key())
    {
        WorkBench::instance()->show_result_fullscreen();
    }
    QWidget::keyPressEvent(e);
}


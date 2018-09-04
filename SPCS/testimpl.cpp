#include "testimpl.h"
#include "m_testinitdlg.h"

TestImpl::TestImpl(QObject *w):
    QObject(w)
{
    connect(&m_files,SIGNAL(P_show(QString,bool)),this,SLOT(Set_act(QString,bool)));
    connect(&m_ele_switch,SIGNAL(P_show(QString,bool)),this,SLOT(Set_act(QString,bool)));
    connect(&m_Shelf,SIGNAL(P_show(QString,bool)),this,SLOT(Set_act(QString,bool)));
    connect(&m_multi_switch,SIGNAL(P_show(QString,bool)),this,SLOT(Set_act(QString,bool)));
    connect(&m_control,SIGNAL(P_show(QString,bool)),this,SLOT(Set_act(QString,bool)));
    connect(&m_tools,SIGNAL(P_show(QString,bool)),this,SLOT(Set_act(QString,bool)));
}

TestImpl *TestImpl::instance()
{
    static TestImpl * s_impl = new TestImpl();
    return s_impl;
}


void TestImpl::destroy()
{
    delete instance();
}

void TestImpl::Set_act(QString p_name, bool flag)
{
    m_view.Set_act_checked(p_name,flag);
}

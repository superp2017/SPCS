#include "probe_test.h"

Probe_test::Probe_test()
{

    connect(&m_test_ui,SIGNAL(begin_test()),this,SLOT(start()));
}

void Probe_test::show_ui()
{
    m_test_ui.showNormal();
}

void Probe_test::run()
{
    m_test_ui.test();
}

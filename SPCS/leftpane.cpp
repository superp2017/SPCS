#include "leftpane.h"
#include "testunit.h"
#include "outputview.h"
#include "workbench.h"
#include "radarface.h"
#include "controlpane.h"
#include "testresult.h"
#include "tmonitor.h"
LeftPane::LeftPane(QSplitter *parent) :
    QSplitter(parent)
{
    addWidget(WorkBench::instance());
    addWidget(OutputView::instance());
    QList<int>  list;
    list.push_back(576);
    list.push_back(200);
    setSizes(list);

    connect(TMonitor::instance(), SIGNAL(ShowMainWindow()), this, SLOT(recover_output_view()));

    connect(ControlPane::instance(), SIGNAL(face_import()),  WorkBench::instance(), SLOT(show_radar_face()));
    connect(ControlPane::instance(), SIGNAL(test_result()),  WorkBench::instance(), SLOT(show_result_area()));
    connect(ControlPane::instance(), SIGNAL(face_analy()),   WorkBench::instance(), SLOT(show_radar_analy()));
    connect(ControlPane::instance(), SIGNAL(trouble_check()),WorkBench::instance(), SLOT(trouble_check()));
    connect(ControlPane::instance(), SIGNAL(test_init()),    WorkBench::instance(),SLOT(show_init_dlg()));
    connect(ControlPane::instance(), SIGNAL(setdev()),       WorkBench::instance(),SLOT(show_dev()));
    connect(ControlPane::instance(), SIGNAL(freq_set()),     WorkBench::instance(),SLOT(show_setfreq_dlg()));
}

void LeftPane::recover_output_view()
{
    addWidget(OutputView::instance());
}


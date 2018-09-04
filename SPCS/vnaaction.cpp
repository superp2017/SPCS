#include "vnaaction.h"
#include "_global.h"
#include "mainwindow.h"
#include "m_setpnadlg.h"
#include "m_setfreqdlg.h"
#include "vnadapter.h"
#include "visa.h"
#include "outputview.h"

VNAAction::VNAAction(QObject *parent) :
    Actions(parent)
{

}

void VNAAction::register_actions()
{
    QString VNA = CVTS::GBKToUnicode::toUnicode("&Ê¸Íø");
    //  QString Type = CVTS::GBKToUnicode::toUnicode("&»úÐÍ");
    QString Set = CVTS::GBKToUnicode::toUnicode("&ÉèÖÃ");
    //   QString RS_ =  CVTS::GBKToUnicode::toUnicode("&R&&S");
    //   QString Agilent = CVTS::GBKToUnicode::toUnicode("&Agilent");
  //  QString Test = CVTS::GBKToUnicode::toUnicode("&²âÊÔ");

    m_setting = new QAction(Set, this);
    m_setting->setShortcut(QKeySequence(tr("Ctrl+E")));

    //  m_RS = new QAction(RS_,this);

    //  m_RS->setCheckable(true);
    // m_RS->setEnabled(true);
    // m_agilent = new QAction(Agilent,this);

    // m_agilent->setCheckable(true);
    //  m_agilent->setEnabled(true);
   // m_test = new QAction(Test,this);
   // m_test->setShortcut(QKeySequence(tr("Ctrl+T")));

    //   MainWindow::instance()->register_menu(VNA, Type);
    //  MainWindow::instance()->register_menu(Type,m_RS);
    //  MainWindow::instance()->register_menu(Type,m_agilent);
  //  MainWindow::instance()->register_menu(VNA, m_setting);
   // MainWindow::instance()->register_menu(VNA,m_test);

    toolbar = new ToolBar(VNA);

   // MainWindow::instance()->register_ToolBar(VNA,m_setting,toolbar);
 //   MainWindow::instance()->register_ToolBar(VNA,m_test,toolbar);

    //m_RS->setChecked(true);
    // m_agilent->setChecked(false);

   // connect(m_setting,SIGNAL(triggered()),this,SLOT(show_PNA_setting_dlg()));
    //  connect(m_RS, SIGNAL(triggered()), this, SLOT(sel_RS()));
    //  connect(m_agilent, SIGNAL(triggered()), this, SLOT(sel_Aglient()));
  //  connect(m_test,SIGNAL(triggered()),this,SLOT(show_Test_PNA_dlg()));
    connect(toolbar,SIGNAL(P_show(QString,bool)),this,SIGNAL(P_show(QString,bool)));
   // M_SetPNAdlg::instance()->init();
}

//void VNAAction::show_current_machine(CVTS::MACHINE_TYPE &type)
//{
//    if(type == CVTS::RS)
//    {
//        m_RS->setChecked(true);
//        m_agilent->setChecked(false);
//    }else if(type == CVTS::AGILENT)
//    {
//        m_agilent->setChecked(true);
//        m_RS->setChecked(false);
//    }else
//    {
//        m_agilent->setChecked(false);
//        m_RS->setChecked(false);
//    }
//}

//void VNAAction::sel_RS()
//{
//    m_RS->setChecked(true);
//    m_agilent->setChecked(false);
//}

//void VNAAction::sel_Aglient()
//{
//    m_RS->setChecked(false);
//    m_agilent->setChecked(true);
//}

void VNAAction::show_PNA_setting_dlg()
{
  //  M_SetPNAdlg::instance()->exec();
}

void VNAAction::show_Test_PNA_dlg()
{
    //    TestPNA* testPNA_(new TestPNA);
    //    testPNA_->exec();
//    std::vector<QString> res;
//    std::vector<QString> freqs = M_SetFreqdlg::instance()->get_freq();
//    int n = freqs.size();
//    if(n <= 0) return ;
//    QString start = M_SetFreqdlg::instance()->get_freq()[0];
//    QString stop = M_SetFreqdlg::instance()->get_freq()[n-1];

//    res = VNAdapter::instance(1)->test_impl_agilent(start.toDouble(), stop.toDouble(), n);
//    OutputView::instance()->append(VNAdapter::instance(1)->get_idn());

//    if(res.size() == 3)
//    {
//        QString S11(">> S11:"); OutputView::instance()->append(S11);
//        QStringList S11_list = res[0].split(QRegExp(QChar(',')));
//        if(S11_list.size() == n * 2)
//        {
//            for(int i=0; i<n; i++)
//            {
//                char buf[1024];
//                sprintf(buf, "frequency = %s,real = %s, imag = %s, magn = %f, phase = %f", freqs[i].toLocal8Bit().data(),\
//                        S11_list[2*i].toLocal8Bit().data(), S11_list[2*i+1].toLocal8Bit().data(), \
//                        VNAdapter::genMagn_w(S11_list[2*i].toDouble(), S11_list[2*i+1].toDouble()), \
//                        VNAdapter::genPhase(S11_list[2*i].toDouble(), S11_list[2*i+1].toDouble()));
//                OutputView::instance()->append(buf);
//            }
//        }

//        QString S22(">> S22:"); OutputView::instance()->append(S22);
//        QStringList S22_list = res[1].split(QRegExp(QChar(',')));
//        if(S22_list.size() == n * 2)
//        {
//            for(int i=0; i<n; i++)
//            {
//                char buf[1024];
//                sprintf(buf, "frequency = %s,real = %s, imag = %s, magn = %f, phase = %f", freqs[i].toLocal8Bit().data(),\
//                        S22_list[2*i].toLocal8Bit().data(), S22_list[2*i+1].toLocal8Bit().data(), \
//                        VNAdapter::genMagn_w(S22_list[2*i].toDouble(), S22_list[2*i+1].toDouble()), \
//                        VNAdapter::genPhase(S22_list[2*i].toDouble(), S22_list[2*i+1].toDouble()));
//                OutputView::instance()->append(buf);
//            }
//        }

//        QString S21(">> S21:"); OutputView::instance()->append(S21);
//        QStringList S21_list = res[2].split(QRegExp(QChar(',')));
//        if(S21_list.size() == n * 2)
//        {
//            for(int i=0; i<n; i++)
//            {
//                char buf[1024];
//                sprintf(buf, "frequency = %s,real = %s, imag = %s, magn = %f, phase = %f", freqs[i].toLocal8Bit().data(),\
//                        S21_list[2*i].toLocal8Bit().data(), S21_list[2*i+1].toLocal8Bit().data(), \
//                        VNAdapter::genMagn_w(S21_list[2*i].toDouble(), S21_list[2*i+1].toDouble()), \
//                        VNAdapter::genPhase(S21_list[2*i].toDouble(), S21_list[2*i+1].toDouble()));
//                OutputView::instance()->append(buf);
//            }
//        }
//    }
}



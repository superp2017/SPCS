#include "tmonitor.h"

TMonitor::TMonitor(QWidget *parent) :
    QWidget(parent),
    m_grid_layout(this)
{
    m_grid_layout.addWidget(&m_left,0,0);
    m_grid_layout.addWidget(&m_right,0,1);
    m_grid_layout.setColumnStretch(0,6);
    m_grid_layout.setColumnStretch(1,5);
    m_grid_layout.setSpacing(2);
    m_grid_layout.setContentsMargins(1,1,1,1);
    setLayout(&m_grid_layout);
    connect(&m_right,SIGNAL(StopTest()),this,SIGNAL(StopTest()),Qt::QueuedConnection);
    connect(&m_right,SIGNAL(back()),this,SLOT(back()),Qt::QueuedConnection);

}

void TMonitor::back()
{
    this->hide();
    //    this->showNormal();
    emit ShowMainWindow();
}

void TMonitor::enableReturn(bool res)
{
    if(res)
    {
        QMessageBox mes;
        QString title = CVTS::GBKToUnicode::toUnicode("Ã· æ");
        QString text = CVTS::GBKToUnicode::toUnicode("≤‚ ‘ÕÍ±œ£°");
        mes.setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
        mes.setWindowTitle(title);
        mes.setText(text);
         mes.setIconPixmap(QPixmap(".\\image\\607logo-6464.png"));
        mes.exec();
    }
    m_right.enableReturn(res);
}

void TMonitor::Set_up_widget(QWidget *up)
{
    m_left.Set_up_widget(up);
}

void TMonitor::Set_down_widget(QWidget *down)
{
    m_left.Set_down_widget(down);
}

void TMonitor::UpdateData(int _ID, double freq_, double _M, double _P)
{
    m_right.UpdateData(_ID,freq_,_M,_P);
}

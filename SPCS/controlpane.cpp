#include "controlpane.h"
#include "testunit.h"
#include "delaytask.h"
#include "_global.h"
#include "statusoutput.h"
#include <QDebug>
#include "taskimpl.h"
#include "tmonitor.h"
#include "qdatetime.h"

ControlPane::ControlPane(QWidget *parent) :
    QWidget(parent),
    m_grid_layout(this)
{
    int fixW = 55;

    m_array_set_btn = new QPushButton(CVTS::GBKToUnicode::toUnicode("阵面设置") ,this );
    m_array_set_btn->setFixedHeight(fixW);

    QString ls_sheet = QString::fromUtf8("font: 14pt \"\346\245\267\344\275\223\";");

    connect(m_array_set_btn, SIGNAL(clicked()), this, SIGNAL(face_import()));
    m_grid_layout.addWidget(m_array_set_btn, 0, 0);

    m_test_init_btn = new QPushButton(CVTS::GBKToUnicode::toUnicode("测试项设置"), this);
    m_test_init_btn->setFixedHeight(fixW);

    connect(m_test_init_btn, SIGNAL(clicked()), this, SIGNAL(test_init()));
    m_grid_layout.addWidget(m_test_init_btn, 1, 0);

    m_freq_btn = new QPushButton(CVTS::GBKToUnicode::toUnicode("频率设置") ,this );
    m_freq_btn->setFixedHeight(fixW);

    connect(m_freq_btn, SIGNAL(clicked()), this, SIGNAL(freq_set()));
    m_grid_layout.addWidget(m_freq_btn, 2, 0);

    m_an_btn = new QPushButton(CVTS::GBKToUnicode::toUnicode("硬件参数"), this);
    m_an_btn->setFixedHeight(fixW);

    connect(m_an_btn, SIGNAL(clicked()), this, SIGNAL(setdev()));
    m_grid_layout.addWidget(m_an_btn, 3, 0);

    m_begin_btn = new QPushButton(CVTS::GBKToUnicode::toUnicode("开始测试"), this);
    m_begin_btn->setFixedHeight(fixW);
    m_begin_btn->setIcon(QIcon("./image/run.png"));
    m_begin_btn->setIconSize(QSize(m_begin_btn->height()-20,m_begin_btn->height()-20));
    connect(m_begin_btn, SIGNAL(clicked()), this, SIGNAL(begin()));
    m_grid_layout.addWidget(m_begin_btn, 4, 0);
    connect(this, SIGNAL(begin()), TaskImpl::instance(), SLOT(begin()));
    connect(TaskImpl::instance(), SIGNAL(Panebeign()), this, SLOT(inner_begin()));
    //connect(TaskImpl::instance(), SIGNAL(task_impl_finish()), this, SLOT(test_finish()));

    m_pause_btn = new QPushButton(CVTS::GBKToUnicode::toUnicode("暂停"), this);
    m_pause_btn->hide();
    //connect(m_pause_btn, SIGNAL(clicked()), this, SLOT(inner_pause()));
    // m_grid_layout.addWidget(m_pause_btn, 5, 0);

    connect(this,SIGNAL(pause(bool)),TaskImpl::instance(),SLOT(pause(bool)));
    m_stop_btn = new QPushButton(CVTS::GBKToUnicode::toUnicode("停止"), this);

    connect(m_stop_btn, SIGNAL(clicked()), this, SLOT(inner_stop()));
    m_grid_layout.addWidget(m_stop_btn, 5, 0);

    m_testresult_btn = new QPushButton(CVTS::GBKToUnicode::toUnicode("测试结果"), this);
    m_testresult_btn->setFixedHeight(fixW);

    connect(m_testresult_btn, SIGNAL(clicked()), this, SIGNAL(test_result()));
    m_grid_layout.addWidget(m_testresult_btn, 6, 0);

    m_array_anay_btn = new QPushButton(CVTS::GBKToUnicode::toUnicode("阵面分析"), this);
    m_array_anay_btn->setFixedHeight(fixW);

    connect(m_array_anay_btn, SIGNAL(clicked()), this, SIGNAL(face_analy()));
    m_grid_layout.addWidget(m_array_anay_btn, 7, 0);

    m_unit_trouble_btn = new QPushButton(CVTS::GBKToUnicode::toUnicode("故障分析"), this);
    m_unit_trouble_btn->setFixedHeight(fixW);
    m_unit_trouble_btn->hide();
    // connect(m_unit_trouble_btn, SIGNAL(clicked()), this, SIGNAL(trouble_check()));
    // m_grid_layout.addWidget(m_unit_trouble_btn, 9, 0);


    m_grid_layout.addWidget(StatusOutput::instance(), 8, 0);

    m_grid_layout.setSpacing(2);
    m_grid_layout.setContentsMargins(1,1,1,1);
    setLayout(&m_grid_layout);

    m_paused = false;
    connect(DelayTask::instance(), SIGNAL(tigger_delay_task()), this, SLOT(init()));
    this->setStyleSheet(ls_sheet);

    m_stop_btn->hide();

}


void ControlPane::init()
{
    default_mode();
}


void ControlPane::inner_begin()
{
    m_begin_btn->setEnabled(false);
    m_pause_btn->setEnabled(true);
    m_stop_btn->setEnabled(true);
}

void ControlPane::inner_stop()
{
    QMessageBox msgBox;
    QString title = CVTS::GBKToUnicode::toUnicode("警告");
    QString str = CVTS::GBKToUnicode::toUnicode("此操作可能导致数据丢失,是否强制停止？");
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
    msgBox.setWindowTitle(title);
    msgBox.setText(str);
    msgBox.setIconPixmap(QPixmap(".\\image\\607logo-6464.png"));
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    switch (ret) {
    case QMessageBox::Ok:
        emit  stoptest();
        TestEnd_mode();
        m_pause_btn->setText(CVTS::GBKToUnicode::toUnicode("暂停"));
        break;
    case QMessageBox::Cancel:
        break;
    default:
        break;
    }

}

void ControlPane::inner_pause()
{
    m_paused = !m_paused;
    m_begin_btn->setEnabled(false);
    m_pause_btn->setEnabled(true);
    if(m_paused)
        m_pause_btn->setText(CVTS::GBKToUnicode::toUnicode("继续"));
    else
        m_pause_btn->setText(CVTS::GBKToUnicode::toUnicode("暂停"));
    emit pause(m_paused);
    m_stop_btn->setEnabled(true);
}

void ControlPane::default_mode()
{
    setbuttonsenable(false);
      // setbuttonsenable(true);
}

void ControlPane::CreatNew_mode()
{
    m_array_set_btn->setEnabled(true);
    m_test_init_btn->setEnabled(true);
    m_an_btn->setEnabled(true);
    m_freq_btn->setEnabled(true);
    m_begin_btn->setEnabled(true);
    m_pause_btn->setEnabled(false);
    m_stop_btn->setEnabled(false);
    m_testresult_btn->setEnabled(false);
    m_array_anay_btn->setEnabled(false);
    m_unit_trouble_btn->setEnabled(false);
    StatusOutput::instance()->setenable(true);
    M_SetFreqdlg::instance()->init();

      // setbuttonsenable(true);
}

void ControlPane::TestEnd_mode()
{
    m_array_set_btn->setEnabled(true);
    m_test_init_btn->setEnabled(true);
    m_an_btn->setEnabled(true);
    m_freq_btn->setEnabled(true);
    m_testresult_btn->setEnabled(true);
    m_array_anay_btn->setEnabled(true);
    m_unit_trouble_btn->setEnabled(true);
    m_begin_btn->setEnabled(false);
    m_pause_btn->setEnabled(false);
    m_stop_btn->setEnabled(false);
    StatusOutput::instance()->setenable(true);
}

void ControlPane::open_mode()
{
    m_array_set_btn->setEnabled(true);
    m_test_init_btn->setEnabled(true);
    m_an_btn->setEnabled(true);
    m_freq_btn->setEnabled(true);
    m_testresult_btn->setEnabled(true);
    m_array_anay_btn->setEnabled(true);
    m_unit_trouble_btn->setEnabled(true);
    m_begin_btn->setEnabled(false);
    m_pause_btn->setEnabled(false);
    m_stop_btn->setEnabled(false);
    StatusOutput::instance()->setenable(false);

      // setbuttonsenable(true);
}

void ControlPane::setbuttonsenable(bool enable)
{
//    m_array_set_btn->setEnabled(true);
//    m_test_init_btn->setEnabled(enable);
//    m_an_btn->setEnabled(enable);
//    m_freq_btn->setEnabled(enable);
//    m_testresult_btn->setEnabled(enable);
//    m_array_anay_btn->setEnabled(enable);
//    m_unit_trouble_btn->setEnabled(enable);
//    m_begin_btn->setEnabled(enable);
//    m_pause_btn->setEnabled(enable);
//    m_stop_btn->setEnabled(enable);
//    StatusOutput::instance()->setenable(enable);
}



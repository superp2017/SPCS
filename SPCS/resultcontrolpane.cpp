#include "resultcontrolpane.h"
#include "ui_resultcontrolpane.h"

ResultControlPane::ResultControlPane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResultControlPane)
{
    ui->setupUi(this);
    InitWidget();
    createConnection();
    viewChanged();

    m_isFullScreen = false;

    m_mpTimes  =0 ;
    m_m_mpTimes = 0;
}

ResultControlPane::~ResultControlPane()
{
    delete ui;
}

void ResultControlPane::addFreqItem(std::vector<QString> &tFreq)
{
    ui->comboBox_freq->clear();
    for(size_t i = 0 ;i < tFreq.size(); ++i)
    {
        QString key ;
        CVTS::DoubleFre_TO_QStringFreq::Double_TO_QString(tFreq.at(i).toDouble(),key);
        ui->comboBox_freq->addItem(key);
    }
    ui->comboBox_freq->setCurrentIndex(0);
}

void ResultControlPane::addTimesItem(int t_mpTimes,int t_m_mpTimes)
{
    m_mpTimes   = t_mpTimes;
    m_m_mpTimes = t_m_mpTimes;
}

bool ResultControlPane::isDB()
{
    return ui->radioButton_db->isChecked();
}

bool ResultControlPane::is360()
{
    return ui->radioButton_360->isChecked();
}



void ResultControlPane::checkbox_checked()
{
    bool ismagn =  ui->checkBox_magn->isChecked() ;
    bool isphase = ui->checkBox_phase->isChecked();
    ui->groupBox_db_line->setEnabled(ismagn);
    ui->groupBox_phase_range->setEnabled(isphase);
    emit show_MagnPhase(ismagn,isphase);
}

void ResultControlPane::enable_combox(bool enable,bool isdb)
{
    ui->comboBox_stage->setEnabled(enable);
    ui->comboBox_times->setEnabled(enable);
    ui->comboBox_type->setEnabled(enable);
    if(isdb)
    {
        ui->radioButton_db->setChecked(true);
    }
    ui->groupBox_db_line->setEnabled(!isdb);

}

void ResultControlPane::Clear()
{
    enable_combox(true);
    ui->comboBox_freq->clear();
    ui->comboBox_times->clear();
    emit clear_data();
}


void ResultControlPane::InitWidget()
{
    ui->comboBox_stage->addItem(ORG_MP);
    ui->comboBox_stage->addItem(CFG_MP);
    ui->comboBox_stage->addItem(CFG_M);
    ui->comboBox_stage->addItem(FINAL_CFG);

   // ui->comboBox_type->addItem(S_1_1);
     ui->comboBox_type->addItem(S_2_1);
   //ui->comboBox_type->addItem(S_2_2);
     ui->comboBox_type->addItem(TYPE_CFG);
     ui->comboBox_type->addItem(TYPE_MP_1);
}

void ResultControlPane::createConnection()
{
    connect(ui->comboBox_stage,SIGNAL(currentTextChanged(QString)),this,SLOT(add_time_item(QString)),Qt::QueuedConnection);

    connect(ui->comboBox_stage,SIGNAL(currentTextChanged(QString)),this,SLOT(currentSelectChanged()),Qt::QueuedConnection);
    connect(ui->comboBox_times,SIGNAL(currentTextChanged(QString)),this,SLOT(currentSelectChanged()),Qt::QueuedConnection);
    connect(ui->comboBox_type,SIGNAL(currentTextChanged(QString)),this,SLOT(currentSelectChanged()),Qt::QueuedConnection);
    connect(ui->comboBox_freq,SIGNAL(currentTextChanged(QString)),this,SLOT(currentSelectChanged()),Qt::QueuedConnection);
    connect(ui->radioButton_db,SIGNAL(clicked()),this,SLOT(currentSelectChanged()),Qt::QueuedConnection);
    connect(ui->radioButton_line,SIGNAL(clicked()),this,SLOT(currentSelectChanged()),Qt::QueuedConnection);
    connect(ui->radioButton_360,SIGNAL(clicked()),this,SLOT(currentSelectChanged()),Qt::QueuedConnection);
    connect(ui->radioButton_0_180,SIGNAL(clicked()),this,SLOT(currentSelectChanged()),Qt::QueuedConnection);


    connect(ui->checkBox_magn,SIGNAL(clicked()),this,SLOT(viewChanged()));
    connect(ui->checkBox_phase,SIGNAL(clicked()),this,SLOT(viewChanged()));
    connect(ui->pushButton_full,SIGNAL(clicked()),this,SLOT(fullScreen_slot()));

    connect(ui->pushButton_export,SIGNAL(clicked()),this,SIGNAL(export_data()));
    connect(ui->pushButton_import,SIGNAL(clicked()),this,SIGNAL(load_data()));
    connect(ui->pushButton_add,SIGNAL(clicked()),this,SIGNAL(add_data()));
    connect(ui->pushButton_clear,SIGNAL(clicked()),this,SLOT(Clear()));

}

void ResultControlPane::add_time_item(QString stage)
{
    ui->comboBox_times->clear();
    if(stage == CFG_MP)
    {
        for(int i = 0;i < m_mpTimes; ++i)
        {
            ui->comboBox_times->addItem(QString("%1").arg(i+1));
        }
    }
    if(stage == CFG_M)
    {
        for(int i = 0;i < m_m_mpTimes; ++i)
        {
            ui->comboBox_times->addItem(QString("%1").arg(i+1));
        }
    }
}

void ResultControlPane::currentSelectChanged()
{
    viewChanged();
    QString stage = ui->comboBox_stage->currentText();
    QString type  = ui->comboBox_type->currentText();
    QString freq  = ui->comboBox_freq->currentText();
    QString times = ui->comboBox_times->currentText();
    bool isDB  = ui->radioButton_db->isChecked();
    bool is360 = ui->radioButton_360->isChecked();

    emit SelectChanged(stage,times,type,freq,isDB,is360);

}

void ResultControlPane::viewChanged()
{
    bool ret = false;
    if(ui->comboBox_stage->currentText() == FINAL_CFG)
    {
        ui->comboBox_times->setEnabled(false);
        ui->comboBox_type->setCurrentIndex(1);
        ui->comboBox_type->setEnabled(false);
        ui->groupBox_db_line->setEnabled(false);
        ret = true;
    }
    else
    {
        if(ui->comboBox_stage->currentText() == ORG_MP)
            ui->comboBox_times->setEnabled(false);
        else
            ui->comboBox_times->setEnabled(true);
        ui->comboBox_type->setEnabled(true);

        if(ui->comboBox_type->currentText() == TYPE_CFG || ui->comboBox_type->currentText() == TYPE_MP_1)
        {
            ui->groupBox_db_line->setEnabled(false);
            ui->radioButton_db->setChecked(true);
            ret = true;
        }
        else
        {
            ui->groupBox_db_line->setEnabled(true);
            ret = false;
        }
    }

    bool isMagn  = ui->checkBox_magn->isChecked();
    bool isPhase = ui->checkBox_phase->isChecked();

    if(isMagn&!ret)
        ui->groupBox_db_line->setEnabled(true);
    else
        ui->groupBox_db_line->setEnabled(false);

    ui->groupBox_phase_range->setEnabled(isPhase);


    if(!(isMagn||isPhase))
    {
        ui->checkBox_magn->setChecked(true);
        ui->checkBox_phase->setChecked(true);
        currentSelectChanged();
    }

    emit show_MagnPhase(isMagn, isPhase);
}


void ResultControlPane::fullScreen_slot()
{
    m_isFullScreen = !m_isFullScreen;
    emit full_screen(m_isFullScreen);
    if(m_isFullScreen)
        ui->pushButton_full->setText(CVTS::GBKToUnicode::toUnicode("ÍË³öÈ«ÆÁ"));
    else
        ui->pushButton_full->setText(CVTS::GBKToUnicode::toUnicode("È«ÆÁ"));
}




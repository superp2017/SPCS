#include "m_setfreqdlg.h"
#include "ui_m_setfreqdlg.h"
#include <QIntValidator>
#include "m_setpnadlg.h"


M_SetFreqdlg::M_SetFreqdlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::M_SetFreqdlg)
{
    ui->setupUi(this);
    m_init = false;
    connect(ui->radioButton_range,SIGNAL(clicked()),M_SetPNAdlg::instance(),SLOT(range_click()));
    connect(ui->radioButton_single,SIGNAL(clicked()),M_SetPNAdlg::instance(),SLOT(single_clicK()));
    connect(M_SetPNAdlg::instance(),SIGNAL(range()),this,SLOT(range()));
    connect(M_SetPNAdlg::instance(),SIGNAL(single()),this,SLOT(single()));
    init();
    this->setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
}

M_SetFreqdlg::~M_SetFreqdlg()
{
    delete ui;
}

void M_SetFreqdlg::reset()
{
    if(m_init)
    {
        init_data();
    }
}

void M_SetFreqdlg::init()
{
    m_init = true;
    init_type();
    init_item();
    init_tablewidget();
    init_data();
}

std::vector<QString>&  M_SetFreqdlg::get_freq()
{
    if (Calculate_freq())
        sort_freqs();
    return m_freq;
}

QString M_SetFreqdlg::get_freq_step()
{
    return ui->lineEdit_iter->text();
}

void M_SetFreqdlg::setfreq(VNA_SWEEP_TYPE type, double start, double end, QString step)
{
    if(type == SINGLE_POINT)
    {
        ui->radioButton_single->setChecked(true);
        QString start_str = QString::number(start,'f',0);
        QString cur;
        int index ;
        CVTS::COMBOX_INDEX_RREQ::GET_Combox_Index_Freq(start_str,cur,index);
        ui->lineEdit_start->setText(cur);
        ui->comboBox_start->setCurrentIndex(index);
        ui->lineEdit_iter->setText("1");
    }
    else
    {
        ui->radioButton_range->setChecked(true);
        QString start_str = QString::number(start,'f',0);
        QString end_str = QString::number(end,'f',0);
        QString cur;
        int index;
        CVTS::COMBOX_INDEX_RREQ::GET_Combox_Index_Freq(start_str,cur,index);
        ui->lineEdit_start->setText(cur);
        ui->comboBox_start->setCurrentIndex(index);

        CVTS::COMBOX_INDEX_RREQ::GET_Combox_Index_Freq(end_str,cur,index);
        ui->lineEdit_end->setText(cur);
        ui->comboBox_end->setCurrentIndex(index);
        ui->lineEdit_iter->setText(step);
    }
    update_freq();
}

void M_SetFreqdlg::setfreq(VNA_SWEEP_TYPE type, std::vector<QString> &freq)
{
    if(freq.size()>0)
        setfreq(type,freq.at(0).toDouble(),freq.at(freq.size()-1).toDouble());
    else
        setfreq(type,0,0,0);
}

void M_SetFreqdlg::init_item()
{
    ui->comboBox_start->addItem("Hz");
    ui->comboBox_start->addItem("kHz");
    ui->comboBox_start->addItem("MHz");
    ui->comboBox_start->addItem("GHz");
    ui->comboBox_end->addItem("Hz");
    ui->comboBox_end->addItem("kHz");
    ui->comboBox_end->addItem("MHz");
    ui->comboBox_end->addItem("GHz");
}

void M_SetFreqdlg::init_type()
{
    ui->lineEdit_start->setValidator(new QDoubleValidator(0.0, 100000000000.0,5,this));
    ui->lineEdit_end->setValidator(new QDoubleValidator(0.0, 100000000000.0,5,this));
    ui->lineEdit_iter->setValidator(new QIntValidator(0, 1000000000,this));
}

void M_SetFreqdlg::init_data()
{
    expand = false;
    this->resize(337,231);
    ui->comboBox_start->setCurrentIndex(3);
    ui->comboBox_end->setCurrentIndex(3);
    ui->lineEdit_start->setText("8");
    ui->lineEdit_end->setText("12");
    ui->radioButton_range->setChecked(true);
    ui->lineEdit_end->setEnabled(true);
    ui->label_end->setEnabled(true);
    ui->comboBox_end->setEnabled(true);
    ui->lineEdit_iter->setText("3");
    ui->tableWidget->hide();
    ui->groupBox_4->hide();
    ui->lineEdit_loadname->setEnabled(false);
    ui->pushButton_load->setEnabled(false);
    update_freq();
}

void M_SetFreqdlg::init_tablewidget()
{
    QStringList ls_list;
    ls_list << "Frequency"<<"Unit";
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(ls_list);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setColumnWidth(0,75);
    ui->tableWidget->setColumnWidth(1,63);
    form_hide();
}

void M_SetFreqdlg::AllItemAlignment( int row_)
{
    ui->tableWidget->item(row_,0)->setTextAlignment(Qt::AlignHCenter);
}

void M_SetFreqdlg::remove_all()
{
    int n = ui->tableWidget->rowCount();
    for(int i=0;i<n;++i)
    {
        ui->tableWidget->removeRow(0);
    }
}

void M_SetFreqdlg::display_freq()
{
    remove_all();
    if(m_freq.size()>0)
    {
        for(size_t i = 0;i< m_freq.size();++i)
        {
            QString  item_text = m_freq.at(i);
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setRowHeight(ui->tableWidget->rowCount()-1, 20);
            QComboBox *comBox = new QComboBox(this);
            comBox->insertItem(0, QString("Hz"));
            comBox->insertItem(1, QString("KHz"));
            comBox->insertItem(2, QString("MHz"));
            comBox->insertItem(3, QString("GHz"));
            QString item;
            int dex;
            CVTS::COMBOX_INDEX_RREQ::GET_Combox_Index_Freq(item_text,item,dex);
            if(!item.isEmpty() && dex >= 0)
            {
                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(item));
                comBox->setCurrentIndex(dex);
                comBox->setEnabled(false);
                ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 1, comBox);
                AllItemAlignment(ui->tableWidget->rowCount()-1);
            }
        }
    }
}

void M_SetFreqdlg::set_single_point_freq()
{
    QString num = QString::number(ui->lineEdit_start->text().toDouble()*pow(1000.0,ui->comboBox_start->currentIndex()),'f',0);
    m_freq.push_back(num);
}
bool M_SetFreqdlg::Calculate_freq() //根据始末频率计算所有频率
{
    m_freq.clear();
    if(ui->radioButton_range->isChecked())
    {
        double end_ = ui->lineEdit_end->text().toDouble();
        double start_ = ui->lineEdit_start->text().toDouble();
        if(end_<start_)
        {
            QMessageBox::information(this,tr("Error"),tr("Input error !"));
            return false;
        }
        if(end_> start_)
        {
            double step = (end_*pow(1000.0,ui->comboBox_end->currentIndex())\
                           - start_*pow(1000.0,ui->comboBox_start->currentIndex()))/(ui->lineEdit_iter->text().toInt()-1);
            for(int i=0; i<ui->lineEdit_iter->text().toInt(); i++)
            {
                QString fre_cur =QString::number(ui->lineEdit_start->text().toDouble()*pow(1000.0,ui->comboBox_start->currentIndex()) + step * i,'f',0);
                m_freq.push_back(fre_cur);
            }
        }

        if(end_ == start_)
        {
            set_single_point_freq();
        }

    }else
    {
        set_single_point_freq();
    }

    return true;
}

void M_SetFreqdlg::on_radioButton_single_clicked()
{
    ui->lineEdit_end->setEnabled(false);
    ui->comboBox_end->setEnabled(false);
    ui->lineEdit_loadname->setEnabled(false);
    ui->pushButton_load->setEnabled(false);
    ui->lineEdit_iter->setEnabled(true);
    ui->lineEdit_iter->setText("1");
    ui->lineEdit_start->setEnabled(true);
    ui->comboBox_start->setEnabled(true);
}

void M_SetFreqdlg::on_radioButton_range_clicked()
{
    ui->lineEdit_start->setEnabled(true);
    ui->comboBox_start->setEnabled(true);
    ui->lineEdit_end->setEnabled(true);
    ui->comboBox_end->setEnabled(true);
    ui->lineEdit_iter->setEnabled(true);
    ui->lineEdit_iter->setText("3");
    ui->lineEdit_loadname->setEnabled(false);
    ui->pushButton_load->setEnabled(false);
}

void M_SetFreqdlg::on_radioButton_load_clicked()
{
    ui->lineEdit_loadname->setEnabled(true);
    ui->pushButton_load->setEnabled(true);
    ui->comboBox_start->setEnabled(false);
    ui->comboBox_end->setEnabled(false);
    ui->lineEdit_start->setEnabled(false);
    ui->lineEdit_end->setEnabled(false);
    ui->lineEdit_iter->setEnabled(false);
    remove_all();
}



void M_SetFreqdlg::on_pushButton_load_clicked()
{    
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load Freq"),
                                                    QApplication::applicationDirPath(),
                                                    tr("Dat (*.freq)"));
    if(!fileName.isEmpty())
        ParsefreqList(fileName);
}


bool M_SetFreqdlg::update_freq()
{
    if(!ui->radioButton_load->isChecked())
    {
        if(Calculate_freq())
        {
            sort_freqs();
            display_freq();
            update_outstatus_freq();
            return true;
        }else
            return false;
    }
    return true;
}


void M_SetFreqdlg::on_pushButton_OK_clicked()
{
    if(update_freq())
        done(123);
}

void M_SetFreqdlg::on_pushButton_cancel_clicked()
{
    done(-1);
}
void M_SetFreqdlg::on_pushButton_update_clicked()
{
    if(!ui->radioButton_load->isChecked())
        update_freq();
}

void M_SetFreqdlg::update_outstatus_freq()
{
    double start = 0;
    double end   = 0;
    double step  = 0;
    if(m_freq.size()>1)
    {
        start = m_freq.at(0).toDouble();
        end   = m_freq.at(m_freq.size()-1).toDouble();
        step  = (end - start)/(m_freq.size()-1);
        StatusOutput::instance()->updata_freq(start,end,step);
    }
    if(m_freq.size() ==1)
    {
        StatusOutput::instance()->updata_freq(m_freq.at(0).toDouble(), m_freq.at(0).toDouble(),step);
    }
    if(m_freq.size() == 0)
    {
        StatusOutput::instance()->updata_freq(start,end,step);
    }
}

void M_SetFreqdlg::on_pushButton_expand_clicked()
{
    if(!expand)
    {
        form_expand();

    }else
    {
        form_hide();
    }
}
void M_SetFreqdlg::form_hide()
{
    this->setFixedSize(337, 231);
    ui->tableWidget->hide();
    ui->groupBox_4->hide();
    expand = false;
    ui->pushButton_expand->setText(">>>");
}

void M_SetFreqdlg::form_expand()
{
    this->setFixedSize(523,231);
    ui->groupBox_4->showNormal();
    ui->tableWidget->showNormal();
    expand =true;
    ui->pushButton_expand->setText("<<<");
}


void M_SetFreqdlg::sort_freqs()
{
    // sort
    std::stable_sort(m_freq.begin(), m_freq.end(), Compare_freq());
}

void M_SetFreqdlg::range()
{
    if(m_init)
    {
        ui->radioButton_range->setChecked(true);
        on_radioButton_range_clicked();
        update_freq();
    }
}

void M_SetFreqdlg::single()
{
    if(m_init)
    {
        ui->radioButton_single->setChecked(true);
        on_radioButton_single_clicked();
        update_freq();
    }
}

void M_SetFreqdlg::ParsefreqList(QString filename)
{
    if(parse(filename))
    {
        sort_freqs();
        display_freq();
        ui->lineEdit_loadname->setText(filename);
        update_outstatus_freq();
    }else
        QMessageBox::information(NULL,tr("Warning"),tr("frequency files Parse failed !"));
}

bool M_SetFreqdlg::parse(QString p_path)
{
    m_freq.clear();
    QSettings settings(p_path,QSettings::IniFormat);
    settings.beginGroup("frequency");
    QString freq  = settings.value("f").toString();
    QStringList ls_list = freq.split(QRegExp(","));
    for(int i = 0;i<ls_list.size();++i)
    {
        m_freq.push_back(ls_list.at(i));
    }
    settings.endGroup();
    return m_freq.size()>0;
}







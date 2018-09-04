#include "testresult.h"
#include "datadapter_s.h"
#include "m_plottestview.h"
#include "m_parsecurvedata.h"
#include "projectmanager.h"
#include "resultcontrolpane.h"

TestResult::TestResult(QWidget *parent) :
    QWidget(parent),
    m_grid_layout(this)
{
    m_grid_layout.addWidget(&m_title,0);
    m_title.setFixedHeight(20);
    m_grid_layout.addWidget(&m_out_area,1);
    m_grid_layout.setSpacing(0);
    m_grid_layout.setContentsMargins(10,10,10,10);
    setLayout(&m_grid_layout);
    m_rang_360 = true;
    m_isDB = true;

    createConnection();
       this->setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
}

TestResult *TestResult::instance()
{
    static TestResult *s_result = new TestResult();
    return s_result;
}

void TestResult::destroy()
{
    delete instance();
}


void TestResult::createConnection()
{    
    connect(ResultControlPane::instance(),SIGNAL(show_MagnPhase(bool,bool)),this,SLOT(show_chart(bool,bool)), Qt::QueuedConnection);

    connect(ResultControlPane::instance(),SIGNAL(load_data()),this,SLOT(on_import()), Qt::QueuedConnection);
    connect(ResultControlPane::instance(),SIGNAL(export_data()),this,SLOT(on_export()), Qt::QueuedConnection);
    connect(ResultControlPane::instance(),SIGNAL(add_data()),this,SLOT(on_add()), Qt::QueuedConnection);
    connect(ResultControlPane::instance(),SIGNAL(clear_data()),this,SLOT(on_clear()), Qt::QueuedConnection);
    connect(ResultControlPane::instance(),SIGNAL(full_screen(bool)),this,SLOT(fullScreen(bool)), Qt::QueuedConnection);
    connect(ResultControlPane::instance(),SIGNAL(SelectChanged(QString,QString,QString,QString,bool,bool)),\
            this,SLOT(selectChange(QString,QString,QString,QString,bool,bool)), \
            Qt::QueuedConnection);
}

///
/// \brief TestResult::initData
/// \param t_org
/// \param t_cfg_mp
/// \param t_cfg_m_mp
/// \param t_cfg_final
/// \param t_Id
/// \param t_freq
/// 初始化数据
void TestResult::initData(H_ORG &t_org, H_CFG_MP &t_cfg_mp, H_CFG_MP &t_cfg_m_mp, H_CFG_FINAL &t_cfg_final, std::vector<int> &t_Id, std::vector<QString> &t_freq)
{
    clear();

    m_org         = t_org;
    m_cfg_mp      = t_cfg_mp;
    m_cfg_m_mp    = t_cfg_m_mp;
    m_cfg_final   = t_cfg_final;

    for(size_t i = 0; i < t_Id.size(); ++i)
    {
        int id = t_Id.at(i);
        m_id.push_back(QString("%1").arg(id));
    }

    ResultControlPane::instance()->addFreqItem(t_freq);
    //add times undo
    ResultControlPane::instance()->addTimesItem(m_cfg_mp.size(),m_cfg_m_mp.size());
}

/////
/// \brief TestResult::on_clear
/// 清空按钮对应的槽
void TestResult::on_clear()
{
    if(!Clear_data()) return;
    reset();
}

/////
/// \brief TestResult::reset
/// 清空揭界面和数据
void TestResult::reset()
{
    M_PlotTestView::instance()->reset();
    clear();
}
/////
/// \brief TestResult::on_export
/// 导出槽
void TestResult::on_export()
{
    M_PlotTestView::instance()->export_curve_data(m_id,m_isDB,m_rang_360,this);
}

/////
/// \brief TestResult::fullScreen
/// \param isFullScreen
/// 全屏
void TestResult::fullScreen(bool isFullScreen)
{
    if(isFullScreen)
        emit on_fullscreen();
    else
        emit on_show_normal();
}

/////
/// \brief TestResult::on_import
/// 导入或添加
void TestResult::on_import()
{
    if(!Clear_data()) return;

    QString fileName = QFileDialog::getOpenFileName(this, tr("Data Import"),
                                                    ProjectManager::instance()->get_path()\
                                                    +DATA_PATH,\
                                                    tr("Curve (*.curve);;Original(*.org);;MagnPhase(*.mp);;Calibration(*.cal)"));
    import(false,fileName);
}

/////
/// \brief TestResult::on_add
/// 添加
void TestResult:: on_add()
{
    QStringList fileList = QFileDialog::getOpenFileNames(this, tr("Data Import"),
                                                         ProjectManager::instance()->get_path()\
                                                         +DATA_PATH,\
                                                         tr("Curve (*.curve)"));

    for(int i =0;i<fileList.size();++i)
    {
        QString  fileName = fileList.at(i);
        import(true,fileName);
    }
}

/////
/// \brief TestResult::import
/// \param isadd
/// \param fileName
/// 导入
void TestResult::import(bool isadd,QString &fileName)
{    
    Curvedata m_data;
    QFileInfo ls_file(fileName);
    if(!ls_file.exists()) return ;

    if(ls_file.completeSuffix() == "org" )
    {
        reset();
        import_MaxFile(fileName);
    }
    if(ls_file.completeSuffix() == "mp"|| ls_file.completeSuffix() == "cal")
    {
        reset();
        import_MP_Files(fileName);
    }
    if(ls_file.completeSuffix() == "curve")
    {
        parse_data(fileName,m_data);
        if(!isadd)
        {
            reset();
            ResultControlPane::instance()->enable_combox(false,true);
        }else
        {
           // clear();
            ResultControlPane::instance()->enable_combox(true);
        }
        if(!creat_curve(m_data))
        {
            qDebug()<<" import creat_curve failed";
        }
    }

}

/////
/// \brief TestResult::import_MaxFile
/// \param p_path
/// 导入原始数据
void TestResult::import_MaxFile(QString &p_path)
{
    std::vector<QString> ls_freq;

    m_import_data_org =  m_manage.ReadMAXFile(p_path,ls_freq,false);
    if(ls_freq.size()>0)
    {
        ResultControlPane::instance()->addFreqItem(ls_freq);
    }
}

/////
/// \brief TestResult::import_MP_Files
/// \param p_path
/// 导入.mp数据
void TestResult::import_MP_Files(QString &p_path)
{
    std::vector<QString> ls_freq;

    m_import_data_db =  m_manage.ReadMAXFile(p_path,ls_freq,true);
    if(ls_freq.size()>0)
    {
        ResultControlPane::instance()->addFreqItem(ls_freq);
    }
}

/////
/// \brief TestResult::clear
/// 清空缓存
void TestResult::clear()
{
    m_id.clear();
    m_import_data_org.clear();
    m_import_data_db.clear();

    m_org.clear();
    m_cfg_mp.clear();
    m_cfg_m_mp.clear();
    m_cfg_final.clear();
}

/////
/// \brief TestResult::Clear_data
/// \return
/// 清空警告
bool TestResult::Clear_data()
{
    QString ls_title = CVTS::GBKToUnicode::toUnicode("提示");
    QString ls_com   = CVTS::GBKToUnicode::toUnicode("这个动作将导致当前测试数据先清空");
    QString text     = CVTS::GBKToUnicode::toUnicode("是否继续导入？");
    QMessageBox mes;

    mes.setText(ls_com);
    mes.setInformativeText(text);
    mes.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    mes.setDefaultButton(QMessageBox::Save);
    mes.setIconPixmap(QPixmap(".\\image\\607logo-6464.png"));
    mes.setWindowTitle(ls_title);
    mes.setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));

    int ret = mes.exec();
    switch (ret) {
    case QMessageBox::Ok:
        return true;
    case QMessageBox::Cancel:
        return false;
    default:
        return false;
    }
}


/////
/// \brief TestResult::creat_curve
/// \param m_data
/// \param ishowmagn
/// \return
///  创建曲线
bool TestResult::creat_curve(Curvedata &m_data,bool ishowmagn)
{
    if(m_data.t_magn.size() == m_data.t_phase.size()&& m_data.t_magn.size()>0)
    {
        return M_PlotTestView::instance()->creat_curve(m_data,ishowmagn);
    }
    return false;
}

/////
/// \brief TestResult::parse_data
/// \param p_filename
/// \param data
/// 解析数据
void TestResult::parse_data(QString& p_filename,Curvedata &data)
{
    M_ParseCurveData::instance()->parse(p_filename,m_isDB,m_rang_360);
    data = M_ParseCurveData::instance()->get_curve_data();
}



/////
/// \brief TestResult::selectChange
/// \param pStage
/// \param pTimes
/// \param pType
/// \param pFreq
/// \param isDB
/// \param is360
///  界面选项变动相应槽
void TestResult::selectChange(QString pStage, QString pTimes, QString pType, QString pFreq, bool isDB, bool is360)
{
   qDebug()<<pStage<<pTimes<<pType<<pFreq<<isDB<<is360;
    m_rang_360 = is360;
    m_isDB     = isDB;
    M_PlotTestView::instance()->reset();
    Curvedata m_data;
    m_data.t_date  = QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss_zzz");
    m_data.t_freq  = pFreq;
    m_data.t_id    = m_id;

    if(m_import_data_org.size()>0)
    {
        ResultControlPane::instance()->enable_combox(false);
        for(size_t i =0;i<m_import_data_org.size();++i)
        {
            QString key ;
            DoubleFre_TO_QStringFreq::Double_TO_QString(m_import_data_org.at(i).t_freq.toDouble(),key);
            if( key== pFreq)
            {
                M_PlotTestView::instance()->reset();
                Curvedata m_data;
                Curvedata ls_data =  m_import_data_org.at(i);
                m_data.t_date = ls_data.t_date;
                m_data.t_freq = ls_data.t_freq;
                m_data.t_id   = ls_data.t_id;
                for(size_t k =0;k<ls_data.t_id.size();++k)
                {
                    if(m_isDB)
                        m_data.t_magn.push_back(QString::number(SPCS_dB::dB(ls_data.t_magn.at(k).toDouble()),'f'));
                    else
                        m_data.t_magn.push_back(ls_data.t_magn.at(k));
                    if(m_rang_360)
                    {
                        double ls_p = ls_data.t_phase.at(k).toDouble() ;
                        if(ls_p <0) ls_p +=360;
                        m_data.t_phase.push_back(QString::number(ls_p,'f'));
                    }else
                        m_data.t_phase.push_back(ls_data.t_phase.at(k));
                }
                creat_curve(m_data);
            }
        }
    }else if(m_import_data_db.size()>0)
    {
        ResultControlPane::instance()->enable_combox(false,true);
        for(size_t i =0;i<m_import_data_db.size();++i)
        {
            QString key ;
            DoubleFre_TO_QStringFreq::Double_TO_QString(m_import_data_db.at(i).t_freq.toDouble(),key);
            if( key== pFreq)
            {
                M_PlotTestView::instance()->reset();
                Curvedata m_data;
                Curvedata ls_data =  m_import_data_db.at(i);
                m_data.t_date = ls_data.t_date;
                m_data.t_freq = ls_data.t_freq;
                m_data.t_id   = ls_data.t_id;
                m_data.t_magn = ls_data.t_magn;
                for(size_t k =0;k<ls_data.t_id.size();++k)
                {
                    if(m_rang_360)
                    {
                        double ls_p = ls_data.t_phase.at(k).toDouble() ;
                        if(ls_p <0) ls_p +=360;
                        m_data.t_phase.push_back(QString::number(ls_p,'f'));
                    }else
                        m_data.t_phase.push_back(ls_data.t_phase.at(k));
                }
                creat_curve(m_data);
            }
        }
    }else
    {
        std::map<int, std::pair<QString,QString> > tmp;
        if(pStage == ORG_MP)
        {
            if(m_org.count(pType)>0&&m_org[pType].count(pFreq)>0)
                tmp = m_org[pType][pFreq];
        }
        if(pStage == CFG_MP)
        {
            int times = pTimes.toInt()-1;
            if(m_cfg_mp.count(times)>0&&m_cfg_mp[times].count(pType)>0 \
                    && m_cfg_mp[times][pType].count(pFreq)>0)
                tmp = m_cfg_mp[times][pType][pFreq];
        }
        if(pStage == CFG_M)
        {
            int times = pTimes.toInt()-1;
            if(m_cfg_m_mp.count(times)>0\
                    &&m_cfg_m_mp[times].count(pType)>0 \
                    && m_cfg_m_mp[times][pType].count(pFreq)>0)
                tmp = m_cfg_m_mp[times][pType][pFreq];
        }
        if(pStage == FINAL_CFG)
        {
            if(m_cfg_final.count(pFreq)>0)
                tmp = m_cfg_final[pFreq];
        }

        if(tmp.empty()) { qDebug()<<"testresult tmp size  0"; return;}
        for(size_t i = 0; i <m_id.size();++i)
        {
            int id = m_id.at(i).toInt();
            if(tmp.count(id)>0)
            {
                QString ls_magn  = tmp[id].first;
                QString ls_phase = tmp[id].second;
                if(isDB&& pType != TYPE_CFG &&  pType != TYPE_MP_1)
                {
                    double db = SPCS_dB::dB(ls_magn.toDouble());
                    m_data.t_magn.push_back(QString::number(db,'f'));
                }else
                    m_data.t_magn.push_back(ls_magn);

                if(is360)
                {
                    double ls_p = ls_phase.toDouble();
                    if(ls_p < 0 )
                        ls_p += 360;
                    m_data.t_phase.push_back(QString::number(ls_p,'f'));
                }else
                    m_data.t_phase.push_back(ls_phase);
            }else
                qDebug()<<"testresult id is no exist!";
        }
        if( m_data.t_magn.size() !=   m_data.t_phase.size() \
                || m_data.t_id.size() !=   m_data.t_magn.size() \
                || m_data.t_phase.size() ==0 )
        {
            qDebug()<< "TestResult::selectChange : create_curve failed  size error";;
        }else
        {
            if(!creat_curve(m_data))
            {
                qDebug() << "TestResult::selectChange : create_curve failed";
            }
        }
    }
}

/////
/// \brief TestResult::show_chart
/// \param show_magn
/// \param show_phase
/// 显示界面,幅度或者相位显示
void TestResult::show_chart(bool show_magn,bool show_phase)
{
    if(show_magn & show_phase) {
        M_PlotTestView::instance()->show_two_chart();
    }
    else
    {
        if(show_magn)
            M_PlotTestView::instance()->show_magn_chart();
        if(show_phase)
            M_PlotTestView::instance()->show_phase_chart();
    }
}


/////
/// \brief TestResult::paintEvent
/// \param e
///
void TestResult::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QRectF rt(rect().left(), rect().top(), rect().width() -1, rect().height() -1);
    painter.setPen(QPen(QColor(155,155,155), 0));
    painter.drawRect(rt);
}


void TestResult::keyPressEvent(QKeyEvent *e)
{
    if(Qt::ControlModifier == e->modifiers() && Qt::Key_Q == e->key())
    {
        emit on_show_normal();
    }
}



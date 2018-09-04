#include "stableplotview.h"
#include "mainwindow.h"
#include "projectmanager.h"

StablePlotView::StablePlotView(QWidget *parent) :
    QWidget(parent)
{
    m_Layout.setSpacing(2);
    m_Layout.setContentsMargins(1,1,1,1);
    setLayout(&m_Layout);
}

StablePlotView::~StablePlotView()
{
    this->setParent(0);
    del();
}

void StablePlotView::del()
{
    m_color_index =0;
    m_charts.del();
}

void StablePlotView::init()
{
    m_charts.t_num = C_TWO;
    QString mag =CVTS::GBKToUnicode::toUnicode("幅度");
    M_CVTS_Plot *ls_plot = new M_CVTS_Plot(mag, this);
    ls_plot->setFrameShape(QFrame::StyledPanel);
    ls_plot->setCanvasBackground(QColor(Qt::black));
    ls_plot->setAxisTitle(QwtPlot::yLeft,"Magn");
    ls_plot->setVisible(false);
    m_charts.t_plots.push_back(ls_plot);

    QString phase =CVTS::GBKToUnicode::toUnicode("相位");
    ls_plot = new M_CVTS_Plot(phase, this);
    ls_plot->setFrameShape(QFrame::StyledPanel);
    ls_plot->setCanvasBackground(QColor(Qt::black));
    ls_plot->setAxisTitle(QwtPlot::yLeft,"Phase");
    ls_plot->setVisible(false);
    m_charts.t_plots.push_back(ls_plot);
    m_cur_wnd = 0;

    m_color.push_back(CVTS_YELLOW);
    m_color.push_back(CVTS_RED);
    m_color.push_back(CVTS_GREEN);
    m_color.push_back(CVTS_BLUE);
    m_color.push_back(CVTS_PURPLE);
    m_color.push_back(CVTS_GRAY);
    m_color.push_back(CVTS_WHITE);
    m_color_index = 0;
    show_chart(m_charts);
}

void StablePlotView::reset()
{
    view_reset();
    data_clear();
}

bool StablePlotView::creat_curve(Curvedata &p_data, bool ishowmagn)
{
    if(m_color_index < m_color.size())
    {
        m_curves_data.push_back(p_data);
        QString name_mg    = "Mag_"   + p_data.t_date;
        QString name_phase = "Phase_" + p_data.t_date;
        std::vector<QString> ls_x_data;
        for(size_t i =0;i<p_data.t_id.size();++i)
        {
            ls_x_data.push_back(QString("%1").arg(i));
        }

        ///////////
        //////mp 2014/ 3/ 9
        ///
        if(ishowmagn)
            m_charts.t_plots.at(0)->Create_new_Curve(name_mg, m_color.at(m_color_index),p_data.t_magn,ls_x_data,p_data.t_id.size());
        m_charts.t_plots.at(1)->Create_new_Curve(name_phase, m_color.at(m_color_index),p_data.t_phase,ls_x_data,p_data.t_id.size());
        ++m_color_index;
        return true;
    }else
    {
        QString  title =CVTS::GBKToUnicode::toUnicode("提示");
        QString info =CVTS::GBKToUnicode::toUnicode("添加的曲线数量达到上限！");
        QMessageBox::information(NULL,title.toStdString().c_str(),info.toStdString().c_str());
        return false;
    }
}

void StablePlotView::creatcurve(Curvedata &p_data)
{
    if(m_color_index < m_color.size())
    {
        m_curves_data.push_back(p_data);
        QString name_mg    = p_data.t_date;
        QString name_phase = p_data.t_date;

        m_charts.t_plots.at(0)->Create_new_Curve(name_mg, m_color.at(m_color_index),p_data.t_magn,p_data.t_id,p_data.t_id.size());
        m_charts.t_plots.at(1)->Create_new_Curve(name_phase, m_color.at(m_color_index),p_data.t_phase,p_data.t_id,p_data.t_id.size());
        ++m_color_index;
        return;
    }else
    {
        QString  title =CVTS::GBKToUnicode::toUnicode("提示");
        QString info =CVTS::GBKToUnicode::toUnicode("添加的曲线数量达到上限！");
        QMessageBox::information(NULL,title.toStdString().c_str(),info.toStdString().c_str());
        return ;
    }
}

void StablePlotView::export_curve_data()
{
    QString p_path;
    p_path = QFileDialog::getExistingDirectory(MainWindow::instance(), tr("Data Export"), ProjectManager::instance()->get_path()+DATA_PATH);

    if(!p_path.isEmpty())
    {
        for(size_t i=0;i<m_curves_data.size();++i)
        {
            QString cur_date = QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss_zzz");
            QString ls_path = p_path+"/"+QString("Curve_%1").arg(i)+"_"+cur_date + ".curve";

            QFile  file(ls_path);
            if(file.open(QFile::Append|QFile::Text))
            {
                QTextStream out(&file);

                Curvedata ls_data = m_curves_data.at(i);
                out << "[Freq]";
                out << "\n";
                out << "freq=";
                out << ls_data.t_freq;
                out << "\n\n";
                out << "[Date]";
                out << endl;
                out << "date=";
                out << cur_date;//ls_data.t_date;
                out << endl;
                out << endl;
                out << "[Data]";
                out << endl;
                if(ls_data.t_magn.size() == ls_data.t_phase.size())
                    for(size_t j =0;j<ls_data.t_magn.size();++j)
                    {
                        out << j+1 << "=\"";
                        out << ls_data.t_magn.at(j);
                        out << ",";
                        out << ls_data.t_phase.at(j);
                        out << "\"";
                        out << endl;
                    }
                out << endl;
                file.close();
            }
            else
            {
                qDebug() << "export: file open failed";
            }
        }
    }
    else
    {
        qDebug() << "path is empty, export failed";
    }
}

void StablePlotView::show_chart(CVTSChart &p_charts)
{
    m_charts = p_charts;
    if(m_charts.t_num == C_NONE) return ;
    switch(m_charts.t_num)
    {
    case C_ONE:
    {
        show_magn_chart();
        break;
    }
    case C_TWO:
    {
        show_two_chart();
        break;
    }
    case C_FOUR:
    {
        break;
    }
    case C_EIGHT:
    {
        break;
    }
    case C_SIXTEEN:
    {
        break;
    }
    }
}

void StablePlotView::show_magn_chart()
{
    if(m_cur_wnd == 1) return ;
    if(m_cur_wnd == 2)
    {
        m_Layout.removeWidget(m_charts.t_plots[0]);
        m_Layout.removeWidget(m_charts.t_plots[1]);
    }else if(m_cur_wnd == 4)
    {
        m_Layout.removeWidget(m_charts.t_plots[0]);
        m_Layout.removeWidget(m_charts.t_plots[1]);
    }

    m_Layout.addWidget(m_charts.t_plots[0],0);
    m_charts.t_plots[0]->setVisible(true);
    m_charts.t_plots[1]->setVisible(false);
    m_Layout.setStretch(0,1);
    m_Layout.setStretch(1,0);
    m_Layout.setSizeConstraint(QLayout::SetDefaultConstraint);
    m_cur_wnd = 1;
}

void StablePlotView::show_two_chart()
{
    if(m_cur_wnd == 2) return ;
    if(m_cur_wnd == 1)
    {
        m_Layout.removeWidget(m_charts.t_plots[0]);
    }else if(m_cur_wnd == 4)
    {
        m_Layout.removeWidget(m_charts.t_plots[0]);
        m_Layout.removeWidget(m_charts.t_plots[1]);
    }

    m_Layout.addWidget(m_charts.t_plots[0],0);
    m_Layout.addWidget(m_charts.t_plots[1],1);
    m_charts.t_plots[0]->setVisible(true);
    m_charts.t_plots[1]->setVisible(true);
    m_Layout.setStretch(0,1);
    m_Layout.setStretch(1,1);
    m_Layout.setSpacing(4);
    m_Layout.setSizeConstraint(QLayout::SetDefaultConstraint);
    m_cur_wnd = 2;
}

void StablePlotView::show_phase_chart()
{
    if(m_cur_wnd == 1) return ;
    if(m_cur_wnd == 2)
    {
        m_Layout.removeWidget(m_charts.t_plots[0]);
        m_Layout.removeWidget(m_charts.t_plots[1]);
    }else if(m_cur_wnd == 4)
    {
        m_Layout.removeWidget(m_charts.t_plots[0]);
        m_Layout.removeWidget(m_charts.t_plots[1]);
    }

    m_Layout.addWidget(m_charts.t_plots[1],0);
    m_charts.t_plots[1]->setVisible(true);
    m_charts.t_plots[0]->setVisible(false);
    m_Layout.setStretch(0,1);
    m_Layout.setStretch(1,0);
    m_Layout.setSizeConstraint(QLayout::SetDefaultConstraint);
    m_cur_wnd = 1;
}

void StablePlotView::data_clear()
{
    m_curves_data.clear();
    m_charts.t_plots.at(0)->init_data();
    m_charts.t_plots.at(1)->init_data();
}

void StablePlotView::view_reset()
{
    m_color_index = 0;
    m_charts.reset();
}

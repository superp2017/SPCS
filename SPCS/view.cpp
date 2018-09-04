#include "view.h"

View::View(QObject *parent) :
    Actions(parent)
{

}

void View::register_actions()
{

    SView= CVTS::GBKToUnicode::toUnicode("&视图");
    Sfile = CVTS::GBKToUnicode::toUnicode("&文件");
    Selec = CVTS::GBKToUnicode::toUnicode("&电子开关");
    Sscanning = CVTS::GBKToUnicode::toUnicode("&扫描架");
    Sgallery = CVTS::GBKToUnicode::toUnicode("&开关矩阵");
    Swvae = CVTS::GBKToUnicode::toUnicode("&波控分机");

    m_show_file =  new QAction(Sfile, this);
    m_show_file->setCheckable(true);
    m_show_elecswitch=  new QAction(Selec, this);
    m_show_elecswitch->setCheckable(true);
    m_scanning=  new QAction(Sscanning, this);
    m_scanning->setCheckable(true);
    m_selectgallery=  new QAction(Sgallery, this);
    m_selectgallery->setCheckable(true);
    m_wave=  new QAction(Swvae, this);
    m_wave->setCheckable(true);

    m_actions[Sfile] = m_show_file;
    m_actions[Selec] = m_show_elecswitch;
    m_actions[Sscanning] = m_scanning;
    m_actions[Sgallery] = m_selectgallery;
    m_actions[Swvae] = m_wave;

    MainWindow::instance()->register_menu(SView, m_show_file);
    MainWindow::instance()->register_menu(SView, m_show_elecswitch);
    MainWindow::instance()->register_menu(SView, m_scanning);
    MainWindow::instance()->register_menu(SView, m_selectgallery);
    MainWindow::instance()->register_menu(SView, m_wave);

    connect(m_show_file,SIGNAL(triggered()),this,SLOT(on_show_file()));
    connect(m_show_elecswitch,SIGNAL(triggered()),this,SLOT(on_show_elecswitch()));
    connect(m_scanning,SIGNAL(triggered()),this,SLOT(on_show_scanning()));
    connect(m_selectgallery,SIGNAL(triggered()),this,SLOT(on_show_selectgallery()));
    connect(m_wave,SIGNAL(triggered()),this,SLOT(on_show_wave()));
}

void View::Set_act_checked(QString t_name, bool checked)
{
    if(t_name.isEmpty()) return ;
    if(t_name.count(t_name)>0)
        m_actions[t_name]->setChecked(checked);
}

void View::on_show_file()
{
    MainWindow::instance()->show_bar(Sfile,m_show_file->isChecked());
}

void View::on_show_elecswitch()
{
    MainWindow::instance()->show_bar(Selec,m_show_elecswitch->isChecked());
}

void View::on_show_scanning()
{
    MainWindow::instance()->show_bar(Sscanning,m_scanning->isChecked());
}

void View::on_show_selectgallery()
{
    MainWindow::instance()->show_bar(Sgallery,m_selectgallery->isChecked());
}


void View::on_show_wave()
{
    MainWindow::instance()->show_bar(Swvae,m_wave->isChecked());
}

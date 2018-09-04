#include "mainwindow.h"
#include <QtWidgets>
#include <QDebug>
#include <QPushButton>




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QPushButton *btn = new QPushButton(this);
    connect(btn, SIGNAL(clicked()), this, SLOT(btn_clicked()));
}

MainWindow::~MainWindow()
{
    setWindowModality(Qt::WindowModal);
}


void MainWindow::btn_clicked()
{
    static QProgressDialog ls_Dlg;

    ls_Dlg.setWindowModality(Qt::WindowModal);
    ls_Dlg.setMinimum(0);
    ls_Dlg.setMaximum(1000000000);
    ls_Dlg.showNormal();

    qDebug() << "pa = " << QThread::currentThreadId();
    for(int i=0; i<1000000000; i++)
    {
        //ls_Dlg.setProgress(i);
        ls_Dlg.setValue(i);
        ::Sleep(10);
        //qDebug() << "i = " << i;
        qDebug() << "resize = " << ls_Dlg.thread()->currentThreadId() << "  i = " << i;
    }
    qDebug() << "here";
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    qDebug() << "resize = " << QThread::currentThreadId();
}

void MainWindow::paintEvent(QPaintEvent *)
{

}

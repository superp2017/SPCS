#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <QProgressBar>
#include <QProgressDialog>
#include <QThread>

class TDialog : public QProgressDialog
{
    Q_OBJECT
public:
    explicit TDialog(QWidget *parent = 0)
        :QProgressDialog(parent),
          m_pbar(this)
    {
        m_pbar.setOrientation(Qt::Horizontal);
        m_pbar.setFixedWidth(400);
        m_pbar.setMaximum(100000);
        m_pbar.setMinimum(0);
    }

    void update_bk()
    {

    }
    void setProgress(int value)
    {
        m_pbar.setValue(value);
    }
protected:
    virtual void paintEvent(QPaintEvent *e)
    {

        QPainter painter(this);
        painter.fillRect(rect(), QBrush(QColor(m_i, m_i, m_i)));
    }
private:
    int             m_i;
    QProgressBar    m_pbar;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:

public slots:
    void btn_clicked();
protected:
    virtual void resizeEvent(QResizeEvent *e);
    virtual void paintEvent(QPaintEvent *);
};

#endif // MAINWINDOW_H

#ifndef OUTPUTVIEW_H
#define OUTPUTVIEW_H

#include <QtWidgets>
#include "_global.h"
#include <QStandardItemModel>


/*!
 * \brief The CleanButton class
 * 程序输出窗口
 */
class CleanButton : public QWidget
{
    Q_OBJECT
public:
    explicit CleanButton(QWidget *parent = 0)
        :QWidget(parent)
    {
        m_pressed = false;
    }

signals:
    void pressed();

protected:
    void mousePressEvent(QMouseEvent *e)
    {
        m_pressed = true;
        update();
        emit pressed();
    }

    void mouseReleaseEvent(QMouseEvent *e)
    {
        m_pressed = false;
        update();
    }

    void paintEvent(QPaintEvent *e)
    {
        QPainter painter(this);

        if(m_pressed)
        {
            QRectF rt_top(rect().left(), rect().top(), rect().width(), rect().height()*2/5);
            QRectF rt_bottom(rect().left(), rect().top() + rect().height()*2/5, rect().width(), rect().height()*3/5);
            painter.fillRect(rt_top, QBrush(QColor(110,115,115)));
            painter.fillRect(rt_bottom, QBrush(QColor(105,110,110)));
        }else
        {
            QRectF rt_top(rect().left(), rect().top(), rect().width(), rect().height()*2/5);
            QRectF rt_bottom(rect().left(), rect().top() + rect().height()*2/5, rect().width(), rect().height()*3/5);
            painter.fillRect(rt_top, QBrush(QColor(120,125,125)));
            painter.fillRect(rt_bottom, QBrush(QColor(115,120,120)));
        }

        painter.drawText(rect(), Qt::AlignCenter, CVTS::GBKToUnicode::toUnicode("清空"));

        QRectF rt(rect().left(), rect().top(), rect().width() -1, rect().height() -1);
        painter.setPen(QPen(QColor(100,100,100), 1));
        painter.drawRect(rt);
    }

private:
    bool        m_pressed;
};


class OutpuTitle : public QWidget
{
    Q_OBJECT
public:
    explicit OutpuTitle(QWidget *parent = 0)
        : QWidget(parent),
          m_clean_btn(this)
    {
        connect(&m_clean_btn, SIGNAL(pressed()), this, SIGNAL(clean_output()));
    }

signals:
    void clean_output();
public slots:

protected:
    void resizeEvent(QResizeEvent *e)
    {
        m_clean_btn.setGeometry(e->size().width() - 41, 0, 40, e->size().height());
    }

    void paintEvent(QPaintEvent *)
    {
        QPainter painter(this);
        QRectF rt_top(rect().left(), rect().top(), rect().width(), rect().height()*2/5);
        QRectF rt_bottom(rect().left(), rect().top() + rect().height()*2/5, rect().width(), rect().height()*3/5);
        painter.fillRect(rt_top, QBrush(QColor(115,120,120)));
        painter.fillRect(rt_bottom, QBrush(QColor(110,110,110)));
        QRectF rt(rect().left(), rect().top(), 100, rect().height());
        painter.drawText(rt, Qt::AlignLeft | Qt::AlignVCenter, CVTS::GBKToUnicode::toUnicode(" 输 出 窗 口"));
        painter.setPen(QPen(QColor(100,100,100), 1));
        painter.drawRect(rt);
    }
private:
    CleanButton     m_clean_btn;
};

class OutputView : public QWidget
{
    Q_OBJECT
protected:
    explicit OutputView(QWidget *parent = 0);

public:
    static OutputView* instance()
    {
        static OutputView *s_view = new OutputView();
        return s_view;
    }

    static void destroy()
    {
        delete instance();
    }
    
signals:
    void scroll_to_bottom();
    void append_sig(QString text);
    void append_sig(const char *text);
    void clean_output_sig();

public:
    void append(QString &text){emit append_sig(text);}
    void append(const char *text){emit append_sig(text);}
    void clean_output(){emit clean_output_sig();}
public slots:
    void append_slot(QString text);
    void append_slot(const char *text);
    void clean_output_slot();
protected:
    void paintEvent(QPaintEvent *);
    
private:
    QGridLayout             m_gridLayout;
    OutpuTitle              m_ouTitle;
    QListView               m_listView;
    QStandardItemModel      m_listModel;
    char                    m_buf[OUT_BUFFER];
};

#endif // OUTPUTVIEW_H

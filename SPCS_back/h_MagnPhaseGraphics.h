#ifndef H_MAGNPHASEGRAPHICS_H
#define H_MAGNPHASEGRAPHICS_H

#include <QWidget>
#include <QGridLayout>
#include <QPainter>
#include <QPaintEvent>

/*!
 * \brief The h_MagnPhaseGraphics class
 * 后处理界面的中间层
 *
 */

class h_MagnPhaseGraphics : public QWidget
{
    Q_OBJECT
public:
    explicit h_MagnPhaseGraphics(QWidget *parent = 0);

public slots:
    void show_widget(QWidget *widget);

protected:
    void paintEvent(QPaintEvent *e);

private:
    QWidget * m_widget;
    QGridLayout *m_layout;

};

#endif // H_MAGNPHASEGRAPHICS_H

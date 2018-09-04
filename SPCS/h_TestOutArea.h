#ifndef H_TESTOUTAREA_H
#define H_TESTOUTAREA_H

#include <QWidget>
#include "m_plottestview.h"
#include "h_MagnPhaseGraphics.h"
#include "resultcontrolpane.h"

/*!
 * \brief The h_TestOutArea class
 *后处理的界面的框架中间层
 */
class h_TestOutArea : public QWidget
{
    Q_OBJECT
public:
    h_TestOutArea(QWidget *parent = 0);

signals:

public slots:

protected:
    void initWidget();
    void paintEvent(QPaintEvent *e);
private:
    QHBoxLayout               m_grid_layout;
    h_MagnPhaseGraphics       m_mp_gra;

};

#endif // H_TESTOUTAREA_H

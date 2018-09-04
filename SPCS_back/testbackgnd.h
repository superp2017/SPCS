#ifndef TESTBACKGND_H
#define TESTBACKGND_H

#include <QtWidgets>
#include "leftpane.h"
#include "rightpane.h"

/*!
 * \brief The TestBackgnd class
 *主界面的背景框架
 */
class TestBackgnd : public QWidget
{
    Q_OBJECT
public:
    explicit TestBackgnd(QWidget *parent = 0);

protected:
    void keyPressEvent(QKeyEvent *e);
private:
    QGridLayout     m_grid_layout;
    LeftPane        m_left;
    RightPane       m_right;
};

#endif // TESTBACKGND_H

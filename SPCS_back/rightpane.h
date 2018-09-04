#ifndef LEFTPANE_H
#define LEFTPANE_H

#include <QtWidgets>

/*!
 * \brief The RightPane class
 * 主界面的右边区域
 */
class RightPane : public QWidget
{
    Q_OBJECT
public:
    explicit RightPane(QWidget *parent = 0);
    
signals:
    

protected:
    virtual void paintEvent(QPaintEvent *);
    
private:
    QGridLayout         m_gridLayout;
};

#endif // LEFTPANE_H

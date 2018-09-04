#ifndef TESTUNITSCENE_H
#define TESTUNITSCENE_H

#include <QGraphicsScene>
#include <QtWidgets>


/*!
 * \brief The TestUnitScene class
 * ≤‚ ‘º‡øÿ¿‡ ≥°æ∞¿‡
 */
class TestUnitScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit TestUnitScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = 0);
    
signals:
    
public slots:
    
protected:
    void init();

protected:

private:
    qreal       m_x;
    qreal       m_y;
    qreal       m_w;
    qreal       m_h;
};

#endif // TESTUNITSCENE_H

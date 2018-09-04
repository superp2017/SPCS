#ifndef TWOSHORTTOId_H
#define TWOSHORTTOId_H

#include <QObject>
/*!
 * \brief The TwoShortToId class
 * ID、行列转换类
 */
class TwoShortToId : public QObject
{
    Q_OBJECT
protected:
    explicit TwoShortToId(QObject *parent = 0);
public:
    static TwoShortToId*instance()
    {
        static TwoShortToId *trans =  new TwoShortToId;
        return trans;
    }
    static void destry()
    {
        delete instance();
    }
    int AddrToId(short row,short col);
    void IdToAddr(int id,short &row,short &col);
signals:
    
public slots:
    
};

#endif // TWOSHORTTOINT_H

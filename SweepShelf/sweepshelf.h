#ifndef SWEEPSHELF_H
#define SWEEPSHELF_H

#include "sweepshelf_global.h"
#include "operacmd.h"

class SWEEPSHELFSHARED_EXPORT SweepShelf: public QObject
{
    Q_OBJECT
protected:
    SweepShelf(QObject *parent =0);
public:
    static SweepShelf *instance();
    static void destory();
    double Cur_Pos();
    void   ClearWarnning();
    void   SetMoveSpeed(MOVESPEESD speed);
    bool   Isopen();
signals:
    void MoveStatus(bool isdone);
public slots:
    bool   IsMoveDone();
    bool   MOVE_TO_Origin();
    bool   MOVE_TO(double distance);
    bool   Open_DEV(QString com);
    void   Close_DEV();
    void   reset();
private:
    OperaCmd        m_opera;
    bool            m_isopen;
};

#endif // SWEEPSHELF_H

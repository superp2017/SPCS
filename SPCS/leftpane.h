#ifndef RIGHTPANE_H
#define RIGHTPANE_H

#include <QtWidgets>
#include "testunitscene.h"


/*!
 * \brief The LeftPane class
 * �������������
 */
class LeftPane : public QSplitter
{
    Q_OBJECT
public:
    explicit LeftPane(QSplitter *parent = 0);
    
signals:
    
public slots:
    void recover_output_view();
private:

};

#endif // RIGHTPANE_H

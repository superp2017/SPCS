#ifndef DATADAPTER_S_H
#define DATADAPTER_S_H

#include <QtWidgets>
#include "_global.h"


/*!
 * \brief The DatAdapter_S class
 * 此类目前没用到
 *
 */
class DatAdapter_S : public QObject
{
    Q_OBJECT
protected:
    explicit DatAdapter_S(QObject *parent = 0);

public:
    static DatAdapter_S* instance();
    static void destroy();

    const std::vector<QString>& get_freqs();

    void search(std::vector<int> &p_ids, CVTS::MVCD &res);

signals:
    
public slots:
    

private:
    QMutex                      m_mutex;
    CVTS::MVCD                  m_mvcd;
    std::vector<QString>        m_freqs;
};

#endif // DATADAPTER_S_H

#include "datadapter_s.h"

DatAdapter_S::DatAdapter_S(QObject *parent) :
    QObject(parent)
{
}

DatAdapter_S *DatAdapter_S::instance()
{
    static DatAdapter_S * s_data = new DatAdapter_S();
    return s_data;
}


void DatAdapter_S::destroy()
{
    delete instance();
}

const std::vector<QString> &DatAdapter_S::get_freqs()
{
    return m_freqs;
}

void DatAdapter_S::search(std::vector<int> &p_ids, CVTS::MVCD &res)
{
    for(size_t i=0; i<p_ids.size(); i++)
    {
        if(m_mvcd[p_ids[i]])
        {
            res[p_ids[i]] = m_mvcd[p_ids[i]];
        }
    }
}

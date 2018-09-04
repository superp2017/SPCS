#ifndef POINTMAP_H
#define POINTMAP_H
#include "_global.h"

class PointMap
{
public:
    PointMap()
    {

    }

    virtual CVTS::SPoint operator()(CVTS::SPoint &sp)
    {
        return sp;
    }


};



#endif // POINTMAP_H

#ifndef GEOPERATOR_H
#define GEOPERATOR_H
#include "GECommand.h"
#include <boost/function.hpp>
#include <map>
#include "GEAsura.h"

namespace Asura
{
class GEOperator
{
public:
    typedef boost::function<int (GEAsura*, std::vector<std::string> &)>   GEFUN;
private:
    GEOperator()
    {

    }

public:
    static GEOperator& instance()
    {
        static GEOperator s_go;
        return s_go;
    }


public:
    void register_handler(GECommand &com_, GEFUN &func_)
    {
        m_com_funcs[com_] = func_;
    }

public:
    GEFUN& operator & (GECommand &com_)
    {
        return m_com_funcs[com_];
    }

private:
    std::map<GECommand, GEFUN > m_com_funcs;
};

}

#endif // GEOPERATOR_H

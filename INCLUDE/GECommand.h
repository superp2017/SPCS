#ifndef GECOMMAND_H
#define GECOMMAND_H
#include "_win32.h"
#include <string>

namespace Asura
{

class GECommand : public std::string
{
    friend class GEComParam;
public:
    GECommand(const char *c)
        :std::string(c)
    {
        reset();
    }
    GECommand(){reset();}
    void reset()
    {
        m_valid_ = false;
    }
    operator bool()
    {
        return m_valid_;
    }
    GECommand& operator=(bool b_)
    {
        m_valid_ = b_;
        return *this;
    }
    bool operator==(GECommand &R_)
    {
        int L = size();
        int N = R_.size();
        if(L != N) return false;
        while(L--)
        {
            if(this->at(L) != R_.at(L)) return false;
        }
        return true;
    }
private:
    bool                    m_valid_;
};
}

#endif // GECOMMAND_H

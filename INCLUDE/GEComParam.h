#ifndef GECOMPARAM_H
#define GECOMPARAM_H
#include "GECommand.h"
#include "GEParam.h"
#include <vector>
#include <boost/asio.hpp>


namespace Asura
{
class GEComParam
{
public:
    typedef std::vector<boost::asio::const_buffer>      VcBuffer;
    typedef std::vector<boost::asio::mutable_buffer>    VmBuffer;
    typedef boost::asio::const_buffer                   CBuffer;
    typedef boost::asio::mutable_buffer                 MBuffer;
public:
    static void command_param(GECommand&, GEParam&, VcBuffer&, char, char m_);
    static void command_param(GECommand&, GEParam&, VmBuffer&, char, char m_);
    static void command_param(GECommand&, GEParam&, CBuffer&, char, char m_);
    static void command_param(GECommand&, GEParam&, MBuffer&, char, char m_);
};

}

#endif // GECOMPARAM_H

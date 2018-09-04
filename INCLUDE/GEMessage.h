#ifndef GEMESSAGE_H
#define GEMESSAGE_H
#include "GECommand.h"
#include "GEParam.h"
#include <boost/tokenizer.hpp>
#include <logger.h>
#include <vector>
#include <_win32.h>
#include <boost/asio.hpp>

namespace Asura
{

class GEAsura;


class GEMessage
{
public:
    typedef boost::asio::mutable_buffer                 ReadHeader;
    typedef std::vector<boost::asio::mutable_buffer>    ReadBody;

public:
    enum GEMStatus{M_PENDING, M_INIT, M_READY, M_FINISH, M_ERROR};
public:
    GEMessage(GEAsura* asura_, char com_c = COMMAND_DECOLLATOR, char param_c = PARAM_DECOLLATOR);
    virtual ~GEMessage();
    void reset();
    size_t size(){return m_size_; }
    void to_string(std::string &str);
    operator GEMStatus();
    GECommand& command();
    GEParam& param();

public:
    ReadHeader& read_header();
    ReadBody& read_body();
    virtual int read_header_complete();
    virtual int read_body_complete();

private:
    GEAsura*                        m_asura_;
    ReadHeader                      m_read_header_;
    ReadBody                        m_read_body_;
    GEMStatus                       m_status_;
    GECommand                       m_com_;
    GEParam                         m_param_;
    char                            m_com_c_;
    char                            m_param_c_;
    size_t                          m_size_;
};



}

#endif // GEMESSAGE_H

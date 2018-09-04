#ifndef GERESULT_H
#define GERESULT_H
#include <boost/asio.hpp>
#include "GEParam.h"
#include <boost/tokenizer.hpp>
#include <logger.h>
#include <vector>

namespace Asura
{
class GEAsura;

class GEResult
{
public:
    typedef boost::asio::const_buffer                   WriteHeader;
    typedef std::vector<boost::asio::const_buffer>      WriteBody;
    enum GERStatus{R_PENDING, R_INIT, R_READY, R_FINISH, R_CLOSE, R_ERROR};
public:
    GEResult(GEAsura* asura_);
    virtual ~GEResult();

    void reset();

    size_t size(){return m_size_;}
    void reply_unknown_error();
    void reply_parse_error();
    void reply_invalid_header();

    void reply_normal_comfirm();

    void set_status(GERStatus status_);
    operator GERStatus();
public:
    WriteHeader& write_header();
    int write_header_complete();
    WriteBody& write_body();
    int write_body_complete();
    void* malloc(size_t s_);
    GEResult& operator <<(const char *p_);
    GEResult& operator <<(std::string &str_);
private:
    GEAsura*                m_asura_;
    GERStatus               m_status_;
    WriteHeader             m_write_header_;
    WriteBody               m_write_body_;
    size_t                  m_size_;
};

}

#endif // GERESULT_H

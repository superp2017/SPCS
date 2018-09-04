#ifndef NETSESSION_H
#define NETSESSION_H
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <QObject>
#include "_win32.h"
#include <boost/pool/pool.hpp>
#include "GEMessage.h"
#include "GEResult.h"
#include "GEAsura.h"

namespace Asura
{

class NetSession
        :  private boost::noncopyable,
         public GEAsura
{

public:
    NetSession(boost::asio::ip::tcp::socket *sock_);
    virtual ~NetSession();

    int parse();

    void init();

    ReadHeader& read_header()
    {
        return m_message_ptr_->read_header();
    }
    int read_header_complete()
    {
        return m_message_ptr_->read_header_complete();
    }
    ReadBody& read_body()
    {
        return m_message_ptr_->read_body();
    }
    int read_body_complete()
    {
        return m_message_ptr_->read_body_complete();
    }

    WriteHeader& write_header()
    {
        return m_result_ptr_->write_header();
    }

    int write_header_complete()
    {
        return m_result_ptr_->write_header_complete();
    }

    WriteBody& write_body()
    {
        return m_result_ptr_->write_body();
    }

    int write_body_complete()
    {
        return m_result_ptr_->write_body_complete();
    }

    virtual std::string client_message()
    {
        char buff[1024];
        sprintf(buff, "ip = %s, port = %d", \
                m_socket_->remote_endpoint().address().to_string().c_str(),\
                m_socket_->remote_endpoint().port());
        return std::string(buff);
        return std::string();
    }
private:
    boost::asio::ip::tcp::socket                *m_socket_;
};
}

#endif // NETSESSION_H

#ifndef GECLIENT_H
#define GECLIENT_H
#include <boost/thread.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/function.hpp>
#include <string>
#include "GEBuffer.h"
#include <_win32.h>

namespace Asura
{

class GEClient
        : public boost::enable_shared_from_this<GEClient>,
          private boost::noncopyable
{
public:
    GEClient(const char *ip, const char *port);
    ~GEClient();
    void run();
    bool connect();
    void handle_connect(const boost::system::error_code& e);
    int exec(GECBuffer&,GEMBuffer&);
    int read(GEMBuffer&);
    int write(GECBuffer&);
    void close_socket();
    bool IsConnected(){ return m_conn_; }
private:
    int valid_header(Asura::msg_header *header_);
    void fill_header(Asura::msg_header *header_);

private:
    boost::asio::io_service                     m_io_service_;
    boost::asio::io_service::strand             m_strand_;
    boost::asio::ip::tcp::socket                m_socket_;
    boost::thread*                              m_thread_;
    bool                                        m_keep_;
    bool                                        m_conn_;
    std::string                                 m_ip;
    std::string                                 m_port;
};

}

#endif // GECLIENT_H

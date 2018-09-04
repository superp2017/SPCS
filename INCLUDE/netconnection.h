#ifndef NETCONNECTION_H
#define NETCONNECTION_H
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "netsession.h"

namespace Asura
{
class NetConnection
        : public boost::enable_shared_from_this<NetConnection>,
          private boost::noncopyable
{
public:
    typedef boost::shared_ptr<NetSession>   NetSession_ptr;


    explicit NetConnection(boost::asio::io_service& io_service/*, AsuraLoader *loader_*/);
    ~NetConnection();
    boost::asio::ip::tcp::socket& socket();
    void start();

    void read_header();
    void read_body();
    void write_reply_header();
    void write_reply_body();

private:
    void handle_read_header(const boost::system::error_code& e);
    void handle_read_body(const boost::system::error_code& e);
    void handle_write_header(const boost::system::error_code& e);
    void handle_write_body(const boost::system::error_code& e);
    void close_socket();

private:
    boost::asio::io_service::strand             m_strand_;
    boost::asio::ip::tcp::socket                m_socket_;
    NetSession_ptr                              m_session_;

};

}

#endif // NETCONNECTION_H

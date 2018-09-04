#ifndef NETASURA_H
#define NETASURA_H

#include <boost/asio.hpp>
#include <string>
#include <vector>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include "netconnection.h"


namespace Asura
{

typedef boost::shared_ptr<NetConnection>    NetConnection_ptr;

class Netasura
        : private boost::noncopyable
{
public:
    explicit Netasura(const std::string& address, const std::string& port,
             const std::string& config_root, std::size_t thread_pool_size);

    void run();
    void accept();
    void handle_accept(const boost::system::error_code& e);


private:
    std::size_t                         m_thread_pool_size_;
    boost::asio::io_service             m_io_service_;
    boost::asio::signal_set             m_signals_;
    boost::asio::ip::tcp::acceptor      m_acceptor_;
    NetConnection_ptr                   m_con_ptr_;
//    AsuraLoader                         m_asura_loader;
};

}

#endif // NETASURA_H

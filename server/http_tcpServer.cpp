#include "http_tcpServer.h"
#include <sys/socket.h>
#include <iostream>

namespace http
{
    void log(const std::string &message)
    {
        std::cout << message << std::endl;
    }

    TcpServer::TcpServer(std::string ip_address, int port) :
        m_ip_address(ip_address), m_port(port), m_socket(),
        m_new_socket(), m_incomingMessage(), m_socketAddress(),
        m_socketAddress_len(sizeof(m_socketAddress)),
        m_serverMessage(buildResponse())
    {
        startServer();
    };

    TcpServer::~TcpServer()
    {
    };

    int TcpServer::startServer()
    {
        // m_socket for member variable
        m_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (m_socket < 0)
        {
            // TODO: Error handling
            return 1;
        }
        return 0;
    }

    void TcpServer::closeServer()
    {
        close(m_socket);
        exit(0);
    }

} // namespace http 

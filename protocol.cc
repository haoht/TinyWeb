/*
*Author:GeneralSandman
*Code:https://github.com/GeneralSandman/TinyWeb
*E-mail:generalsandman@163.com
*Web:www.generalsandman.cn
*/

/*---XXX---
*
****************************************
*
*/

#include "protocol.h"
#include "log.h"

//----------Protocol api----------//
Protocol::Protocol()
{
    LOG(Debug) << "class Protocol constructor\n";
}

Protocol::~Protocol()
{
    LOG(Debug) << "class Protocol destructor\n";
}

//--------EchoProtocol api-------------//
EchoProtocol::EchoProtocol()
{
    LOG(Debug) << "class EchoProtocol constructor\n";
}

void EchoProtocol::connectionMade(Connection *con)
{
    std::cout << "(EchoProtocol) "
              << "get a new connection\n";
}

void EchoProtocol::dataReceived(Connection *con, Buffer *input, Time time)
{
    std::cout << "(EchoProtocol) "
              << "get a new message\n";
}

void EchoProtocol::connectionLost(Connection *con)
{
    std::cout << "(EchoProtocol) "
              << "lost a connection\n";
}

EchoProtocol::~EchoProtocol()
{
    LOG(Debug) << "class EchoProtocol destructor\n";
}

//--------WebProtocol api-------------//
WebProtocol::WebProtocol()
{
    LOG(Debug) << "class WebProtocol constructor\n";
}

void WebProtocol::m_fResponse(Connection *con, struct HttpRequest &request)
{
    std::string h = "HTTP/1.0 200 OK\r\n";
    std::string c = "Content-Type: text/html\r\n\r\n";
    std::string html = "hello world";

    std::string res = h + c + html;
    con->send(res);
    con->shutdownWrite();
    //If we don't close this connection,
    //the html can't be showed in browser.
    //[Http protocol]

    printHttpRequest(request);
}

void WebProtocol::connectionMade(Connection *con)
{
    std::cout << "(WebProtocol) "
              << "get a new connection\n";
}

void WebProtocol::dataReceived(Connection *con, Buffer *input, Time time)
{
    std::cout << "(WebProtocol) "
              << "get a new message\n";
    //class Parser to parse the data received;

    std::string line;
    int i = 0;
    struct HttpRequest request;

    while (input->getALine(line))
    {
        // std::cout << i++ << "-" << line << "-\n";
        if (m_nParser.parseRequestLine(line, request))
        {
            m_fResponse(con, request);
        }

        line = "";
    }
}

void WebProtocol::connectionLost(Connection *con)
{
    std::cout << "(WebProtocol) "
              << "lost a connection\n";
}

WebProtocol::~WebProtocol()
{
    LOG(Debug) << "class WebProtocol destructor\n";
}
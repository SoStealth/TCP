#ifndef __SOCKETTCP_HPP
#define __SOCKETTCP_HPP

#include <sys/socket.h>
#include <arpa/inet.h>
#include "Address.hpp"

#define IP_LOOPBACK "127.0.0.1"
#define IP_MYSELF "0.0.0.0"
#define MAX_CONN 50

class Connection{
private:  int conn_id;
public:   Connection(int conn_id);
          ~Connection(); /* API: shutdown() */
          bool invia(char* msg);
          bool invia_raw(void* buffer, int length); /* API: send() */
          char* ricevi();
          char* ricevi_raw(int* length); /* API: recv() */
};
class ServerTCP{
private:  int sock_id;
public:   ServerTCP(int port, bool loopback); /* API: bind() */
          ~ServerTCP(); /* API: close() */
          Connection accetta(); /* API: accept() */
          bool broadcast(bool broadcast); /* API: setsockopt() */
};
class ClientTCP{
private:  int sock_id;
public:   ClientTCP(bool loopback);
          ~ClientTCP(); /* API: close() */
          bool connetti(Address server); /* API: connect() */
          bool invia(char* msg);
          bool invia_raw(void* buffer, int length); /* API: send() */
          char* ricevi();
          char* ricevi_raw(int* length); /* API: recv() */
          bool broadcast(bool broadcast); /* API: setsockopt() */
};







#endif  //__SERVERTCP_HPP

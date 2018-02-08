#ifndef __SOCKETTCP_HPP
#define __SOCKETTCP_HPP

#include <sys/socket.h>
#include <arpa/inet.h>
#include "Address.hpp"

#define IP_LOOPBACK "127.0.0.1"
#define IP_MYSELF "0.0.0.0"

class Connection{
private:  int conn_id;
public:   Connection(int conn_id);
          ~Connection();
          bool invia(char* msg);
          bool invia_raw(void* buffer, int length);
          char* ricevi();
          char* ricevi_raw(int* length);
          
};
class ServerTCP;
class ClientTCP;







#endif  //__SERVERTCP_HPP

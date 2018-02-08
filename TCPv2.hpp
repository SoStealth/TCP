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
public:   ServerTCP(int port, bool loopback); /* API: socket(),bind() */
          ~ServerTCP(); /* API: close() */
          Connection accetta(); /* API: accept() */
          bool broadcast(bool broadcast); /* API: setsockopt() */
};
class ClientTCP{
private:  int sock_id;
          Connection* connessione;
public:   ClientTCP(bool loopback); /* API: socket() */
          ~ClientTCP(); /* API: close() */
          bool connetti(Address server); /* API: connect() */
          bool invia(char* msg);
          bool invia_raw(void* buffer, int length); /* API: send() */
          char* ricevi();
          char* ricevi_raw(int* length); /* API: recv() */
          bool broadcast(bool broadcast); /* API: setsockopt() */
};
bool ClientTCP::connetti(Address server){
          struct sockaddr_in server_addr;
          server_addr = server->get_address();
          
          int ret = connect(sock_id,
                                (struct sockaddr*) &server_addr,
                                (socklen_t)sizeof(struct sockaddr));          
          if(ret) return true;
    
          /*si può passare sock_id perché sul client ha la stessa funzione di conn_id */
          connessione = new Connessione(sock_id);
          
          return false;
}
bool ClientTCP::invia(char* msg){
          return connessione->invia(msg);
}





#endif  //__SERVERTCP_HPP

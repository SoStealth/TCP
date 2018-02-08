#ifndef __SOCKETTCP_HPP
#define __SOCKETTCP_HPP

#include <sys/socket.h>
#include <arpa/inet.h>
#include "Address.hpp"

#define IP_LOOPBACK "127.0.0.1"
#define IP_MYSELF "0.0.0.0"
#define MAX_CONN 50

class SocketTCP{
protected:int sock_id;
public:   SocketTCP(); /* API: socket() */
          ~SocketTCP(); /* API: close() */
          bool broadcast(bool broadcast); /* API: setsockopt() */
};

class Connection{
private:  int conn_id;
          bool fuffa;
public:   Connection(int conn_id, bool fuffa);
          ~Connection(); /* API: shutdown() */
          bool invia(char* msg);
          bool invia_raw(void* buffer, int length); /* API: send() */
          char* ricevi();
          char* ricevi_raw(int* length); /* API: recv() */
};

class ServerTCP: public SocketTCP{
public:   ServerTCP(int port, bool loopback); /* API: bind(),listen() */
          ~ServerTCP(); /* API: close() */
          Connection accetta(); /* API: accept() */
};
ServerTCP::ServerTCP(int port, bool loopback): SocketTCP{
          
          //bind()
          //listen()
}

class ClientTCP: public SocketTCP{
private:  Connection* connessione;
public:   ClientTCP(); /* API: socket() */
          ~ClientTCP(); /* API: close() */
          bool connetti(Address server); /* API: connect() */
          bool invia(char* msg);
          bool invia_raw(void* buffer, int length);
          char* ricevi();
          char* ricevi_raw(int* length);
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
ClientTCP::ClientTCP(): SocketTCP() {
}
bool ClientTCP::invia(char* msg){
          return connessione->invia(msg);
}
char* ClientTCP::ricevi(){
          return connessione->ricevi();
}





#endif  //__SERVERTCP_HPP

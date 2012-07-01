#include "stdio.h"
#include "winsock2.h"

class SocketSender{

  SOCKET s;    //ソケット

  //接続するサーバの情報
  struct sockaddr_in dest;

  char buffer[1024];

public:
	SocketSender();
	void start();

};
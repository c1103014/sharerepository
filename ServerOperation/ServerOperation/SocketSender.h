#include "stdio.h"
#include "winsock2.h"

class SocketSender{

  SOCKET s;    //�\�P�b�g

  //�ڑ�����T�[�o�̏��
  struct sockaddr_in dest;

  char buffer[1024];

public:
	SocketSender();
	void start();

};
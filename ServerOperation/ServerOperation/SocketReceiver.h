#include "stdio.h"
#include "winsock2.h"

class SocketReveiver{
	SOCKET s, s1;         //�\�P�b�g
	int result;          //�߂�l
	//�ڑ���������N���C�A���g�[���̏��
	struct sockaddr_in source;
	char buffer[1024];  //��M�f�[�^�̃o�b�t�@�̈�
	//char ans[] = "���M����";
	char ret;

public:
	SocketReveiver();
	void start();

};
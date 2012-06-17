#include "stdio.h"
#include "winsock2.h"

class SocketReveiver{
	SOCKET s, s1;         //ソケット
	int result;          //戻り値
	//接続を許可するクライアント端末の情報
	struct sockaddr_in source;
	char buffer[1024];  //受信データのバッファ領域
	//char ans[] = "送信成功";
	char ret;

public:
	SocketReveiver();
	void start();

};
#include "SocketReceiver.h"

SocketReceiver::SocketReceiver(){
		memset(&buffer, '\0', sizeof(buffer));
		//送信元の端末情報を登録する
		memset(&source, 0, sizeof(source));
		source.sin_family = AF_INET;
		//ポート番号はクライアントプログラムと共通
		source.sin_port = htons(7000);
		source.sin_addr.s_addr = htonl(INADDR_ANY);

		//ソケット通信の開始準備
		WSADATA data;
		result = WSAStartup(MAKEWORD(2, 0), &data);
		if (result < 0){
			printf("%d\n", GetLastError());
			printf("ソケット通信準備エラー\n");
		}

		//ソケットの生成
		s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (s < 0){
			printf("%d\n", GetLastError());
			printf("ソケット生成エラー\n");
		}

		//ソケットのバインド
		result = bind(s, (struct sockaddr *)&source, sizeof(source));
		if (result < 0){
			printf("%d\n", GetLastError());
			printf("バインドエラー\n");
		}

		//接続の許可
		result = listen(s, 1);
		if (result < 0){
			printf("接続許可エラー\n");
		}

		printf("接続開始\n");

		//クライアントから通信があるまで待機
		s1 = accept(s, NULL, NULL);
		if (s1 < 0){
			printf("待機エラー\n");
		}
}

void SocketReceiver::start()            //メンバ関数(start)の定義
{
	//toDo future by nakagawa
}


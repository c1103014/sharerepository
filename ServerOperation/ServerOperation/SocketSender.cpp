#include "SocketSender.h"
#include "stdio.h"

SocketSender::SocketSender(){

  //接続するサーバのIPアドレス
  //xxx.xxx.xxx.xxxの形式で指定する
  //char destination[] = "192.168.100.6";
  char destination[] = "localhost";

  //接続先（サーバ）のアドレス情報を設定
  memset(&dest, 0, sizeof(dest));
  //ポート番号はサーバプログラムと共通
  dest.sin_port = htons(8000);
  dest.sin_family = AF_INET;
  dest.sin_addr.s_addr = inet_addr(destination);

  //ソケットの生成
  s = socket(AF_INET, SOCK_STREAM, 0);

  //サーバへの接続
  if(connect(s, (struct sockaddr *) &dest, sizeof(dest))){
    printf("%sに接続できませんでした\n", destination);
    //return -1;
  }
  printf("%sに接続しました\n", destination);

  printf("サーバに送信する文字列を入力して下さい\n");
  scanf("%s", buffer);


  //サーバにデータを送信
  send(s, buffer, sizeof(buffer), 0);

  // Windows でのソケットの終了
  //closesocket(s);
  //WSACleanup();

  //return 0;
}

void SocketSender::start()            //メンバ関数(start)の定義
{
	//toDo future by nakagawa
}
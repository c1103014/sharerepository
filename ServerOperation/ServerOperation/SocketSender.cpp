#include "SocketSender.h"
#include "stdio.h"

SocketSender::SocketSender(){

  //�ڑ�����T�[�o��IP�A�h���X
  //xxx.xxx.xxx.xxx�̌`���Ŏw�肷��
  //char destination[] = "192.168.100.6";
  char destination[] = "localhost";

  //�ڑ���i�T�[�o�j�̃A�h���X����ݒ�
  memset(&dest, 0, sizeof(dest));
  //�|�[�g�ԍ��̓T�[�o�v���O�����Ƌ���
  dest.sin_port = htons(8000);
  dest.sin_family = AF_INET;
  dest.sin_addr.s_addr = inet_addr(destination);

  //�\�P�b�g�̐���
  s = socket(AF_INET, SOCK_STREAM, 0);

  //�T�[�o�ւ̐ڑ�
  if(connect(s, (struct sockaddr *) &dest, sizeof(dest))){
    printf("%s�ɐڑ��ł��܂���ł���\n", destination);
    //return -1;
  }
  printf("%s�ɐڑ����܂���\n", destination);

  printf("�T�[�o�ɑ��M���镶�������͂��ĉ�����\n");
  scanf("%s", buffer);


  //�T�[�o�Ƀf�[�^�𑗐M
  send(s, buffer, sizeof(buffer), 0);

  // Windows �ł̃\�P�b�g�̏I��
  //closesocket(s);
  //WSACleanup();

  //return 0;
}

void SocketSender::start()            //�����o�֐�(start)�̒�`
{
	//toDo future by nakagawa
}
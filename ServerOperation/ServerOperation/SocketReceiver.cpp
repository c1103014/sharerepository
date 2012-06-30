#include "SocketReceiver.h"

SocketReceiver::SocketReceiver(){
		memset(&buffer, '\0', sizeof(buffer));
		//���M���̒[������o�^����
		memset(&source, 0, sizeof(source));
		source.sin_family = AF_INET;
		//�|�[�g�ԍ��̓N���C�A���g�v���O�����Ƌ���
		source.sin_port = htons(7000);
		source.sin_addr.s_addr = htonl(INADDR_ANY);

		//�\�P�b�g�ʐM�̊J�n����
		WSADATA data;
		result = WSAStartup(MAKEWORD(2, 0), &data);
		if (result < 0){
			printf("%d\n", GetLastError());
			printf("�\�P�b�g�ʐM�����G���[\n");
		}

		//�\�P�b�g�̐���
		s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (s < 0){
			printf("%d\n", GetLastError());
			printf("�\�P�b�g�����G���[\n");
		}

		//�\�P�b�g�̃o�C���h
		result = bind(s, (struct sockaddr *)&source, sizeof(source));
		if (result < 0){
			printf("%d\n", GetLastError());
			printf("�o�C���h�G���[\n");
		}

		//�ڑ��̋���
		result = listen(s, 1);
		if (result < 0){
			printf("�ڑ����G���[\n");
		}

		printf("�ڑ��J�n\n");

		//�N���C�A���g����ʐM������܂őҋ@
		s1 = accept(s, NULL, NULL);
		if (s1 < 0){
			printf("�ҋ@�G���[\n");
		}
}

void SocketReceiver::start()            //�����o�֐�(start)�̒�`
{
	//toDo future by nakagawa
}


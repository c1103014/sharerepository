#include "SocketReceiver.h"

SocketReceiver::SocketReceiver(){
		memset(&buffer, '\0', sizeof(buffer));
		//���M���̒[������o�^����
		memset(&source, 0, sizeof(source));
		source.sin_family = AF_INET;
		//�|�[�g�ԍ��̓N���C�A���g�v���O�����Ƌ���
		source.sin_port = htons(8000);
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

 
		//written by naka
		while(1){ 
			//�N���C�A���g���瑗�M���ꂽ�f�[�^�̎�M
			result = recv(s1, buffer, 10, 0);
			if (result < 0){
				printf("��M�G���[\n");
			}
			printf("%s����M���܂���", buffer);
			
			//by naka
			//forced disconnect socket connection process in future. 
			//if(){
				//WSACleanup();
				//printf("�ڑ��I��\n");
			//}	
		}

		//�N���C�A���g�փf�[�^�𑗐M����
		//result = send(s1, ans, 10, 0);

		//printf("�����L�[�������ĉ�����\n");
		//scanf("%c", &ret);
}

void SocketReceiver::start()            //�����o�֐�(start)�̒�`
{
	//toDo future by nakagawa
}


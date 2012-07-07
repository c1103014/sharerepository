#include <Windows.h>
#include <cstdio>

#include "Vmd.h"

/**
 * �R���X�g���N�^
 */
CVmd::CVmd(void)
{
	mlpBoneFrame = NULL;
}

/**
 * �f�X�g���N�^
 */
CVmd::~CVmd(void)
{
	CVmd::free();
}

int CVmd::load(char *szFileName)
{
	FILE *fp;
	fp = fopen(szFileName, "rb");
	if (fp == NULL) {
		return -1;
	}

	// �w�b�_���ǂݍ���
	fread(mHeader.szVersion, sizeof(char), 30, fp);
	fread(mHeader.szModelName, sizeof(char), 20, fp);

	// �{�[���t���[�����ǂݍ���
	fread(&mdwBoneFrameCount, sizeof(DWORD), 1, fp);
	mlpBoneFrame = new VMDBONEFRAME[mdwBoneFrameCount];
	for (DWORD i = 0; i < mdwBoneFrameCount; i++) {
		fread(mlpBoneFrame[i].szName, sizeof(char), 15, fp);
		fread(&mlpBoneFrame[i].dwFrameNo, sizeof(DWORD), 1, fp);
		fread(&mlpBoneFrame[i].fPosX, sizeof(float), 1, fp);
		fread(&mlpBoneFrame[i].fPosY, sizeof(float), 1, fp);
		fread(&mlpBoneFrame[i].fPosZ, sizeof(float), 1, fp);
		fread(&mlpBoneFrame[i].fQuaternionX, sizeof(float), 1, fp);
		fread(&mlpBoneFrame[i].fQuaternionY, sizeof(float), 1, fp);
		fread(&mlpBoneFrame[i].fQuaternionZ, sizeof(float), 1, fp);
		fread(&mlpBoneFrame[i].fQuaternionW, sizeof(float), 1, fp);
		fread(mlpBoneFrame[i].bezier, sizeof(char), 64, fp);
	}

	fclose(fp);

	return 1;
}

void CVmd::free(void)
{
	if (mlpBoneFrame != NULL) {
		delete [] mlpBoneFrame;
		mlpBoneFrame = NULL;
	}
}

#include <cstdio>
#include <cstring>

#include "Pmd.h"

const char SEPARATOR_DIR = '\\';

/**
 * �R���X�g���N�^
 */
CPmd::CPmd(void)
{
	mszFilePath = NULL;
	mszDirPath = NULL;
	mlpVertex = NULL;
	mlpwFaceIndex = NULL;
	mlpMaterial = NULL;
	mlpBone = NULL;
}

/**
 * �f�X�g���N�^
 */
CPmd::~CPmd(void)
{
	CPmd::free();
}

/**
 * PMD�t�@�C�������[�h����
 * @param szFileName ���[�h����t�@�C����
 * @return != 0 : ���[�h����<br />0 : ���[�h���s
 */
int CPmd::load(char *szFileName)
{
	mszFilePath = new char[strlen(szFileName) + sizeof(char)];
	mszDirPath = new char[strlen(szFileName) + sizeof(char)];
	strcpy(mszFilePath, szFileName);
	strcpy(mszDirPath, szFileName);
	*strrchr(mszDirPath, SEPARATOR_DIR) = '\0';

	FILE *fp;
	fp = fopen(szFileName, "rb");
	if (fp == NULL) {
		return -1;
	}

	// PMD���ǂݍ���
	fread(mHeader.szMagic, sizeof(char), 3, fp);
	mHeader.szMagic[3] = '\0';
	fread(&mHeader.fVersion, sizeof(float), 1, fp);
	fread(mHeader.szModelName, sizeof(char), 20, fp);
	fread(mHeader.szComment, sizeof(char), 256, fp);

	// ���_���ǂݍ���
	fread(&mdwVertexCount, sizeof(DWORD), 1, fp);
	mlpVertex = new PMDVERTEX[mdwVertexCount];
	for (DWORD i = 0; i < mdwVertexCount; i++) {
		fread(mlpVertex[i].fPosition, sizeof(float), 3, fp);
		fread(mlpVertex[i].fNormalVector, sizeof(float), 3, fp);
		fread(mlpVertex[i].fUv, sizeof(float), 2, fp);
		fread(mlpVertex[i].wBoneNumber, sizeof(WORD), 2, fp);
		fread(&mlpVertex[i].byBoneWeight, sizeof(BYTE), 1, fp);
		fread(&mlpVertex[i].byEdgeFlag, sizeof(BYTE), 1, fp);
	}

	// �ʏ��ǂݍ���
	fread(&mdwFaceCount, sizeof(DWORD), 1, fp);
	mlpwFaceIndex = new WORD[mdwFaceCount];
	fread(mlpwFaceIndex, sizeof(WORD), mdwFaceCount, fp);

	// �ގ����ǂݍ���
	fread(&mdwMaterialCount, sizeof(DWORD), 1, fp);
	mlpMaterial = new PMDMATERIAL[mdwMaterialCount];
	for (DWORD i = 0; i < mdwMaterialCount; i++) {
		fread(mlpMaterial[i].fDiffuseColor, sizeof(float), 3, fp);
		fread(&mlpMaterial[i].fAlpha, sizeof(float), 1, fp);
		fread(&mlpMaterial[i].fSpecularity, sizeof(float), 1, fp);
		fread(mlpMaterial[i].fSpecularColor, sizeof(float), 3, fp);
		fread(mlpMaterial[i].fMirrorColor, sizeof(float), 3, fp);
		mlpMaterial[i].fDiffuseColor[3] = mlpMaterial[i].fAlpha;
		mlpMaterial[i].fSpecularColor[3] = mlpMaterial[i].fAlpha;
		mlpMaterial[i].fMirrorColor[3] = mlpMaterial[i].fAlpha;
		fread(&mlpMaterial[i].byToonIndex, sizeof(BYTE), 1, fp);
		fread(&mlpMaterial[i].byEdgeFlag, sizeof(BYTE), 1, fp);
		fread(&mlpMaterial[i].dwFaceNumber, sizeof(DWORD), 1, fp);
		fread(mlpMaterial[i].szTextureFileName, sizeof(char), 20, fp);
		mlpMaterial[i].szTextureFileName[20] = '\0';
		if (strchr(mlpMaterial[i].szTextureFileName, '*') != NULL) {
			strncpy(mlpMaterial[i].szTextureFileName1, mlpMaterial[i].szTextureFileName, strchr(mlpMaterial[i].szTextureFileName, '*') - mlpMaterial[i].szTextureFileName);
			mlpMaterial[i].szTextureFileName1[strchr(mlpMaterial[i].szTextureFileName, '*') - mlpMaterial[i].szTextureFileName] = '\0';
			strcpy(mlpMaterial[i].szTextureFileName2, &mlpMaterial[i].szTextureFileName[strchr(mlpMaterial[i].szTextureFileName, '*') - mlpMaterial[i].szTextureFileName + 1]);
		} else {
			strcpy(mlpMaterial[i].szTextureFileName1, mlpMaterial[i].szTextureFileName);
			strcpy(mlpMaterial[i].szTextureFileName2, "");
		}
		mlpMaterial[i].uiTexId = 0xFFFFFFFF;
	}

	// �{�[�����ǂݍ���
	fread(&mwBoneCount, sizeof(WORD), 1, fp);
	mlpBone = new PMDBONE[mwBoneCount];
	for (WORD i = 0; i < mwBoneCount; i++) {
		fread(mlpBone[i].szBoneName, sizeof(char), 20, fp);
		fread(&mlpBone[i].wParentBoneIndex, sizeof(WORD), 1, fp);
		fread(&mlpBone[i].wTailBoneIndex, sizeof(WORD), 1, fp);
		fread(&mlpBone[i].byBoneType, sizeof(BYTE), 1, fp);
		fread(&mlpBone[i].wIKBoneIndex, sizeof(WORD), 1, fp);
		fread(mlpBone[i].fBoneHeadPos, sizeof(float), 3, fp);
		mlpBone[i].fQuaternion[0] = 0.0;
		mlpBone[i].fQuaternion[1] = 0.0;
		mlpBone[i].fQuaternion[2] = 0.0;
		mlpBone[i].fQuaternion[3] = 0.0;
	}

	fclose(fp);

	return 1;
}

/**
 * ���f���f�[�^�ǂݍ��݂Ŋm�ۂ������������������
 */
void CPmd::free(void)
{
	if (mszFilePath != NULL) {
		delete [] mszFilePath;
		mszFilePath = NULL;
	}
	if (mszDirPath != NULL) {
		delete [] mszDirPath;
		mszDirPath = NULL;
	}
	if (mlpVertex != NULL) {
		delete [] mlpVertex;
		mlpVertex = NULL;
	}
	if (mlpwFaceIndex != NULL) {
		delete [] mlpwFaceIndex;
		mlpwFaceIndex = NULL;
	}
	if (mlpMaterial != NULL) {
		delete [] mlpMaterial;
		mlpMaterial = NULL;
	}
	if (mlpBone != NULL) {
		delete [] mlpBone;
		mlpBone = NULL;
	}
}

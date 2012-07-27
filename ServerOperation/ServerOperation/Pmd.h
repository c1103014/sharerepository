#pragma once

#include <Windows.h>
#include <gl/glut.h>

/**
 * �w�b�_���\����
 */
typedef struct tagPmdHeader {
	char szMagic[4];	// PMD���Ƃ��Ă̓T�C�Y3�����A�I�[�L�����Ȃ��̂ŃT�C�Y4�Ƃ���
	float fVersion;
	char szModelName[20];
	char szComment[256];
} PMDHEADER;

/**
 * ���_���\����
 */
typedef struct tagPmdVertex {
	float fPosition[3];
	float fNormalVector[3];
	float fUv[2];
	WORD wBoneNumber[2];
	BYTE byBoneWeight;
	BYTE byEdgeFlag;
} PMDVERTEX;

/**
 * �ގ����\����
 */
typedef struct tagPmdMaterial {
	float fDiffuseColor[4];
	float fAlpha;
	float fSpecularity;
	float fSpecularColor[4];
	float fMirrorColor[4];
	BYTE byToonIndex;
	BYTE byEdgeFlag;
	DWORD dwFaceNumber;
	char szTextureFileName[21];	// PMD���Ƃ��Ă̓T�C�Y20�����A�I�[�L�����Ȃ��ꍇ������̂ŃT�C�Y21�Ƃ���
	char szTextureFileName1[21];	// �e�N�X�`���t�@�C���ƃX�t�B�A�t�@�C���ɕ����邽�߂̃o�b�t�@
	char szTextureFileName2[21];
	GLuint uiTexId;
} PMDMATERIAL;

/**
 * �{�[�����\����
 */
typedef struct tagPmdBone {
	char szBoneName[20];
	WORD wParentBoneIndex;
	WORD wTailBoneIndex;
	BYTE byBoneType;
	WORD wIKBoneIndex;
	float fBoneHeadPos[3];
	float fQuaternion[4];
	float fPreviousQuat[4];
	float fNextQuat[4];
	float fTransformPos[3]; // �ړ���̈ʒu
	float fPreviousTrans[3];
	float fNextTrans[3];
	float fRotMat[16];
	UINT unPreviousKeyFrame;
	UINT unNextKeyFrame;
} PMDBONE;

/**
 * PMD�����܂Ƃ߂��N���X
 */
class CPmd
{
public:
	char *mszFilePath;
	char *mszDirPath;
	PMDHEADER mHeader;
	DWORD mdwVertexCount;
	PMDVERTEX *mlpVertex;
	DWORD mdwFaceCount;
	WORD *mlpwFaceIndex;
	DWORD mdwMaterialCount;
	PMDMATERIAL *mlpMaterial;
	WORD mwBoneCount;
	PMDBONE *mlpBone;

	CPmd(void);
	virtual ~CPmd(void);
	int load(char *szFileName);
	void free(void);
};

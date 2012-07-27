#pragma once

#include <Windows.h>
#include <gl/glut.h>

/**
 * ヘッダ情報構造体
 */
typedef struct tagPmdHeader {
	char szMagic[4];	// PMD情報としてはサイズ3だが、終端記号がないのでサイズ4とする
	float fVersion;
	char szModelName[20];
	char szComment[256];
} PMDHEADER;

/**
 * 頂点情報構造体
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
 * 材質情報構造体
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
	char szTextureFileName[21];	// PMD情報としてはサイズ20だが、終端記号がない場合もあるのでサイズ21とする
	char szTextureFileName1[21];	// テクスチャファイルとスフィアファイルに分けるためのバッファ
	char szTextureFileName2[21];
	GLuint uiTexId;
} PMDMATERIAL;

/**
 * ボーン情報構造体
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
	float fTransformPos[3]; // 移動後の位置
	float fPreviousTrans[3];
	float fNextTrans[3];
	float fRotMat[16];
	UINT unPreviousKeyFrame;
	UINT unNextKeyFrame;
} PMDBONE;

/**
 * PMD情報をまとめたクラス
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

#include <Windows.h>
#include <string>
#include <ctime>
#include <gl/glut.h>

#include "PmdRenderer.h"
#include "Pmd.h"
#include "ImageInfo.h"
#include "Vmd.h"
#include "MatrixUtility.h"

using namespace std;

CPmdRenderer::CPmdRenderer(VOID)
{
}

CPmdRenderer::~CPmdRenderer(VOID)
{
}

VOID CPmdRenderer::load(string filename)
{
	// PMDモデルの読み込み
	pmd.load(const_cast<char *>(filename.c_str()));

	// VMDモーションの読み込み
	vmd.load(const_cast<char *>(string("res\\vmd\\abc.vmd").c_str()));

	// テクスチャの読み込み
	string parentDir = pmd.mszDirPath + string("\\");
	string textureFileList[100];
	GLuint textureNoList[100];
	INT nTexPos = 0;
	for (UINT i = 0; i < pmd.mdwMaterialCount; i++) {
		string textureFile = parentDir + pmd.mlpMaterial[i].szTextureFileName1;
		if (pmd.mlpMaterial[i].szTextureFileName1 != string("")) {
			INT j;
			for (j = 0; j < nTexPos; j++) {
				if (textureFile == textureFileList[j]) {
					pmd.mlpMaterial[i].uiTexId = textureNoList[j];
					break;
				}
			}
			if (j == nTexPos) {
				textureFileList[nTexPos] = textureFile;

				glGenTextures(1, &pmd.mlpMaterial[i].uiTexId);
				textureNoList[nTexPos] = pmd.mlpMaterial[i].uiTexId;

				glBindTexture(GL_TEXTURE_2D, textureNoList[nTexPos]);
				glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
				ImageInfo imageInfo;
				imageInfo.load(textureFileList[nTexPos]);
				if (imageInfo.getDepth() == 24) {
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageInfo.getWidth(), imageInfo.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, imageInfo.getImageData());
				} else {
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageInfo.getWidth(), imageInfo.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, imageInfo.getImageData());
				}
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
				//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

				nTexPos++;
			}
		}
	}
}

VOID CPmdRenderer::render(VOID)
{
	glEnable(GL_NORMALIZE);
	glEnableClientState(GL_NORMAL_ARRAY);
	glDisable(GL_TEXTURE_2D);

	// テストコード(ここから)
	// ボーン設定
	static DWORD dwFrameNo = 0;
	for (USHORT i = 0; i < pmd.mwBoneCount; i++) {
		for (UINT j = 0; j < vmd.mdwBoneFrameCount; j++) {
			if (string(pmd.mlpBone[i].szBoneName) == string(vmd.mlpBoneFrame[j].szName) && vmd.mlpBoneFrame[j].dwFrameNo == dwFrameNo) {
				pmd.mlpBone[i].fQuaternion[0] = vmd.mlpBoneFrame[j].fQuaternionX;
				pmd.mlpBone[i].fQuaternion[1] = vmd.mlpBoneFrame[j].fQuaternionY;
				pmd.mlpBone[i].fQuaternion[2] = vmd.mlpBoneFrame[j].fQuaternionZ;
				pmd.mlpBone[i].fQuaternion[3] = vmd.mlpBoneFrame[j].fQuaternionW;
				pmd.mlpBone[i].fTransformPos[0] = pmd.mlpBone[i].fVmdTrans[0] = vmd.mlpBoneFrame[j].fPosX;
				pmd.mlpBone[i].fTransformPos[1] = pmd.mlpBone[i].fVmdTrans[1] = vmd.mlpBoneFrame[j].fPosY;
				pmd.mlpBone[i].fTransformPos[2] = pmd.mlpBone[i].fVmdTrans[2] = vmd.mlpBoneFrame[j].fPosZ;
				break;
			}
		}
	}

	// フレーム番号更新
	static clock_t start = clock();
	clock_t now = clock();
	//dwFrameNo++;
	if (dwFrameNo > 1000) {
		dwFrameNo = 1000;
	}

	static FLOAT r[4];
	static FLOAT pos[3];
	for (USHORT i = 0; i < pmd.mwBoneCount; i++) {
		if (pmd.mlpBone[i].wParentBoneIndex != 0xFFFF) {
			multiquat(pmd.mlpBone[pmd.mlpBone[i].wParentBoneIndex].fQuaternion, pmd.mlpBone[i].fQuaternion, r);
			pmd.mlpBone[i].fQuaternion[0] = r[0];
			pmd.mlpBone[i].fQuaternion[1] = r[1];
			pmd.mlpBone[i].fQuaternion[2] = r[2];
			pmd.mlpBone[i].fQuaternion[3] = r[3];
			quat2mat(pmd.mlpBone[i].fQuaternion, pmd.mlpBone[i].fRotMat);

			pmd.mlpBone[i].fTransformPos[0] = pmd.mlpBone[i].fBoneHeadPos[0] - pmd.mlpBone[pmd.mlpBone[i].wParentBoneIndex].fBoneHeadPos[0] + pmd.mlpBone[i].fTransformPos[0];
			pmd.mlpBone[i].fTransformPos[1] = pmd.mlpBone[i].fBoneHeadPos[1] - pmd.mlpBone[pmd.mlpBone[i].wParentBoneIndex].fBoneHeadPos[1] + pmd.mlpBone[i].fTransformPos[1];
			pmd.mlpBone[i].fTransformPos[2] = pmd.mlpBone[i].fBoneHeadPos[2] - pmd.mlpBone[pmd.mlpBone[i].wParentBoneIndex].fBoneHeadPos[2] + pmd.mlpBone[i].fTransformPos[2];
			multimatvec(pmd.mlpBone[pmd.mlpBone[i].wParentBoneIndex].fRotMat, pmd.mlpBone[i].fTransformPos, pos);
			pmd.mlpBone[i].fTransformPos[0] = pos[0] + pmd.mlpBone[pmd.mlpBone[i].wParentBoneIndex].fTransformPos[0];
			pmd.mlpBone[i].fTransformPos[1] = pos[1] + pmd.mlpBone[pmd.mlpBone[i].wParentBoneIndex].fTransformPos[1];
			pmd.mlpBone[i].fTransformPos[2] = pos[2] + pmd.mlpBone[pmd.mlpBone[i].wParentBoneIndex].fTransformPos[2];
		} else {
			quat2mat(pmd.mlpBone[i].fQuaternion, pmd.mlpBone[i].fRotMat);
			pmd.mlpBone[i].fTransformPos[0] = pmd.mlpBone[i].fBoneHeadPos[0] + pmd.mlpBone[i].fTransformPos[0];
			pmd.mlpBone[i].fTransformPos[1] = pmd.mlpBone[i].fBoneHeadPos[1] + pmd.mlpBone[i].fTransformPos[1];
			pmd.mlpBone[i].fTransformPos[2] = pmd.mlpBone[i].fBoneHeadPos[2] + pmd.mlpBone[i].fTransformPos[2];
		}
		
	}
	// 頂点設定
	static FLOAT pos1[3];
	static FLOAT pos2[3];
	static FLOAT tmp[3];
	static FLOAT *lpfVertex = new FLOAT[pmd.mdwVertexCount * 3];
	for (UINT i = 0; i < pmd.mdwVertexCount; i++) {
		tmp[0] = pmd.mlpVertex[i].fPosition[0] - pmd.mlpBone[pmd.mlpVertex[i].wBoneNumber[0]].fBoneHeadPos[0];
		tmp[1] = pmd.mlpVertex[i].fPosition[1] - pmd.mlpBone[pmd.mlpVertex[i].wBoneNumber[0]].fBoneHeadPos[1];
		tmp[2] = pmd.mlpVertex[i].fPosition[2] - pmd.mlpBone[pmd.mlpVertex[i].wBoneNumber[0]].fBoneHeadPos[2];
		multimatvec(pmd.mlpBone[pmd.mlpVertex[i].wBoneNumber[0]].fRotMat, tmp, pos1);
		pos1[0] += pmd.mlpBone[pmd.mlpVertex[i].wBoneNumber[0]].fTransformPos[0];
		pos1[1] += pmd.mlpBone[pmd.mlpVertex[i].wBoneNumber[0]].fTransformPos[1];
		pos1[2] += pmd.mlpBone[pmd.mlpVertex[i].wBoneNumber[0]].fTransformPos[2];
		tmp[0] = pmd.mlpVertex[i].fPosition[0] - pmd.mlpBone[pmd.mlpVertex[i].wBoneNumber[1]].fBoneHeadPos[0];
		tmp[1] = pmd.mlpVertex[i].fPosition[1] - pmd.mlpBone[pmd.mlpVertex[i].wBoneNumber[1]].fBoneHeadPos[1];
		tmp[2] = pmd.mlpVertex[i].fPosition[2] - pmd.mlpBone[pmd.mlpVertex[i].wBoneNumber[1]].fBoneHeadPos[2];
		multimatvec(pmd.mlpBone[pmd.mlpVertex[i].wBoneNumber[1]].fRotMat, tmp, pos2);
		pos2[0] += pmd.mlpBone[pmd.mlpVertex[i].wBoneNumber[1]].fTransformPos[0];
		pos2[1] += pmd.mlpBone[pmd.mlpVertex[i].wBoneNumber[1]].fTransformPos[1];
		pos2[2] += pmd.mlpBone[pmd.mlpVertex[i].wBoneNumber[1]].fTransformPos[2];
		lpfVertex[i * 3] = (pos1[0] * pmd.mlpVertex[i].byBoneWeight / 100.0) + (pos2[0] * (100 - pmd.mlpVertex[i].byBoneWeight) / 100.0);
		lpfVertex[i * 3 + 1] = (pos1[1] * pmd.mlpVertex[i].byBoneWeight / 100.0) + (pos2[1] * (100 - pmd.mlpVertex[i].byBoneWeight) / 100.0);
		lpfVertex[i * 3 + 2] = (pos1[2] * pmd.mlpVertex[i].byBoneWeight / 100.0) + (pos2[2] * (100 - pmd.mlpVertex[i].byBoneWeight) / 100.0);
/*
		lpfVertex[i * 3] = (pmd.mlpVertex[i].fPosition[0] * pmd.mlpBone[pmd.mlpVertex[i].wBoneNumber[0]].fRotMat[0] +
							pmd.mlpVertex[i].fPosition[1] * pmd.mlpBone[pmd.mlpVertex[i].wBoneNumber[0]].fRotMat[1] +
							pmd.mlpVertex[i].fPosition[2] * pmd.mlpBone[pmd.mlpVertex[i].wBoneNumber[0]].fRotMat[2]) * pmd.mlpVertex[i].byBoneWeight / 100.0 +
						   (pmd.mlpVertex[i].fPosition[0] * pmd.mlpBone[pmd.mlpVertex[i].wBoneNumber[1]].fRotMat[0] +
							pmd.mlpVertex[i].fPosition[1] * pmd.mlpBone[pmd.mlpVertex[i].wBoneNumber[1]].fRotMat[1] +
							pmd.mlpVertex[i].fPosition[2] * pmd.mlpBone[pmd.mlpVertex[i].wBoneNumber[1]].fRotMat[2]) * (100 - pmd.mlpVertex[i].byBoneWeight) / 100.0;
		lpfVertex[i * 3 + 1] = (pmd.mlpVertex[i].fPosition[0] * pmd.mlpBone[pmd.mlpVertex[i].wBoneNumber[0]].fRotMat[4] +
								pmd.mlpVertex[i].fPosition[1] * pmd.mlpBone[pmd.mlpVertex[i].wBoneNumber[0]].fRotMat[5] +
								pmd.mlpVertex[i].fPosition[2] * pmd.mlpBone[pmd.mlpVertex[i].wBoneNumber[0]].fRotMat[6]) * pmd.mlpVertex[i].byBoneWeight / 100.0 +
							   (pmd.mlpVertex[i].fPosition[0] * pmd.mlpBone[pmd.mlpVertex[i].wBoneNumber[1]].fRotMat[4] +
								pmd.mlpVertex[i].fPosition[1] * pmd.mlpBone[pmd.mlpVertex[i].wBoneNumber[1]].fRotMat[5] +
								pmd.mlpVertex[i].fPosition[2] * pmd.mlpBone[pmd.mlpVertex[i].wBoneNumber[1]].fRotMat[6]) * (100 - pmd.mlpVertex[i].byBoneWeight) / 100.0;
		lpfVertex[i * 3 + 2] = (pmd.mlpVertex[i].fPosition[0] * pmd.mlpBone[pmd.mlpVertex[i].wBoneNumber[0]].fRotMat[8] +
								pmd.mlpVertex[i].fPosition[1] * pmd.mlpBone[pmd.mlpVertex[i].wBoneNumber[0]].fRotMat[9] +
								pmd.mlpVertex[i].fPosition[2] * pmd.mlpBone[pmd.mlpVertex[i].wBoneNumber[0]].fRotMat[10]) * pmd.mlpVertex[i].byBoneWeight / 100.0 +
							   (pmd.mlpVertex[i].fPosition[0] * pmd.mlpBone[pmd.mlpVertex[i].wBoneNumber[1]].fRotMat[8] +
								pmd.mlpVertex[i].fPosition[1] * pmd.mlpBone[pmd.mlpVertex[i].wBoneNumber[1]].fRotMat[9] +
								pmd.mlpVertex[i].fPosition[2] * pmd.mlpBone[pmd.mlpVertex[i].wBoneNumber[1]].fRotMat[10]) * (100 - pmd.mlpVertex[i].byBoneWeight) / 100.0;
*/
	}
	glVertexPointer(3, GL_FLOAT, 0, lpfVertex);
	// テストコード(ここまで)

	//glVertexPointer(3, GL_FLOAT, sizeof(PMDVERTEX), pmd.mlpVertex[0].fPosition);
	glNormalPointer(GL_FLOAT, sizeof(PMDVERTEX), pmd.mlpVertex[0].fNormalVector);
	glTexCoordPointer(2, GL_FLOAT, sizeof(PMDVERTEX), pmd.mlpVertex[0].fUv);

	DWORD dwVertexPos = 0;
	WORD *wIndex = pmd.mlpwFaceIndex;
	for (UINT i = 0; i < pmd.mdwMaterialCount; i++) {
		// 材質の設定
		if (pmd.mlpMaterial[i].byEdgeFlag == 1) {
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, pmd.mlpMaterial[i].fDiffuseColor);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, pmd.mlpMaterial[i].fSpecularColor);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, pmd.mlpMaterial[i].fMirrorColor);
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, pmd.mlpMaterial[i].fSpecularity);
			glEnable(GL_LIGHTING);
			//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		} else {
			// 照明を無効にした際に使う係数
			static const float	fLightDif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
			static const float	fLightAmb[] = { 0.5f, 0.5f, 0.5f, 1.0f };
			float color[4];
			color[0] = pmd.mlpMaterial[i].fMirrorColor[0] + fLightAmb[0];
			color[1] = pmd.mlpMaterial[i].fMirrorColor[1] + fLightAmb[1];
			color[2] = pmd.mlpMaterial[i].fMirrorColor[2] + fLightAmb[2];
			color[3] = pmd.mlpMaterial[i].fMirrorColor[3] + fLightAmb[3];
			color[0] = (color[0] > 1.0f) ? 1.0f : color[0];
			color[1] = (color[1] > 1.0f) ? 1.0f : color[1];
			color[2] = (color[2] > 1.0f) ? 1.0f : color[2];
			color[3] = (color[3] > 1.0f) ? 1.0f : color[3];
			color[0] *= pmd.mlpMaterial[i].fDiffuseColor[0] * fLightDif[0];
			color[1] *= pmd.mlpMaterial[i].fDiffuseColor[1] * fLightDif[1];
			color[2] *= pmd.mlpMaterial[i].fDiffuseColor[2] * fLightDif[2];
			color[3] *= pmd.mlpMaterial[i].fDiffuseColor[3] * fLightDif[3];
			glColor4fv(color);
			glDisable(GL_LIGHTING);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		}

		if (pmd.mlpMaterial[i].fAlpha < 1.0f) {
			glDisable(GL_CULL_FACE);
		} else {
			glEnable(GL_CULL_FACE);
		}

		GLuint uiTexId = pmd.mlpMaterial[i].uiTexId;
		if (uiTexId != 0xFFFFFFFF) {
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, uiTexId);
		} else {
			glDisable(GL_TEXTURE_2D);
		}
		glDrawElements(GL_TRIANGLES, pmd.mlpMaterial[i].dwFaceNumber, GL_UNSIGNED_SHORT, wIndex);
		wIndex += pmd.mlpMaterial[i].dwFaceNumber;
	}

	glEnable(GL_TEXTURE_2D);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisable(GL_NORMALIZE);
}

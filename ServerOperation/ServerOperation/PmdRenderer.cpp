#include <Windows.h>
#include <string>
#include <gl/glut.h>

#include "PmdRenderer.h"
#include "Pmd.h"
#include "ImageInfo.h"

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

	glVertexPointer(3, GL_FLOAT, sizeof(PMDVERTEX), pmd.mlpVertex[0].fPosition);
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

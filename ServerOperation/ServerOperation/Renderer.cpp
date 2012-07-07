#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <gl/glut.h>

#include "ServerOperation.h"
#include "Renderer.h"
#include "ImageInfo.h"
#include "PmdRenderer.h"

Renderer::Renderer(void)
{
	// 背景ポリゴンの初期化
//	m_afVertex[0] = -1.0f; m_afVertex[1] = 1.0f; m_afVertex[2] = 0.0f;
//	m_afVertex[3] = -1.0f; m_afVertex[4] = -1.0f; m_afVertex[5] = 0.0f;
//	m_afVertex[6] = 1.0f; m_afVertex[7] = -1.0f; m_afVertex[8] = 0.0f;
//	m_afVertex[9] = 1.0f; m_afVertex[10] = 1.0f; m_afVertex[11] = 0.0f;

	// 背景ポリゴンの初期化(テストデータ)
	m_afVertex[0] = -9.0f; m_afVertex[1] = 18.0f; m_afVertex[2] = 10.0f;
	m_afVertex[3] = -9.0f; m_afVertex[4] = 0.0f; m_afVertex[5] = 10.0f;
	m_afVertex[6] = 9.0f; m_afVertex[7] = 0.0f; m_afVertex[8] = 10.0f;
	m_afVertex[9] = 9.0f; m_afVertex[10] = 18.0f; m_afVertex[11] = 10.0f;

	// 背景ポリゴンの頂点インデックスの初期化
	m_ashVertexIndex[0] = 0; m_ashVertexIndex[1] = 1; m_ashVertexIndex[2] = 2;
	m_ashVertexIndex[3] = 0; m_ashVertexIndex[4] = 2; m_ashVertexIndex[5] = 3;

	// 背景テクスチャ座標配列の初期化
	m_afTextureAxis[0] = 1.0f; m_afTextureAxis[1] = 0.0f;
	m_afTextureAxis[2] = 1.0f; m_afTextureAxis[3] = 1.0f;
	m_afTextureAxis[4] = 0.0f; m_afTextureAxis[5] = 1.0f;
	m_afTextureAxis[6] = 0.0f; m_afTextureAxis[7] = 0.0f;

	// テクスチャ変数の初期化
	m_unBgTexture = 0;
}

Renderer::~Renderer(void)
{
}

void Renderer::init(void)
{
	// 背景色の設定
	glClearColor(1.0, 1.0, 0.6, 1.0);

	// 頂点配列を有効
	glEnableClientState(GL_VERTEX_ARRAY);

	// デプスバッファを有効
	glEnable(GL_DEPTH_TEST);

	// カリングを有効
	glEnable(GL_CULL_FACE);

	// 背面のポリゴンを透明化
	glCullFace(GL_FRONT);

	// アルファブレンド
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// アルファテスト
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GEQUAL, 0.5);

	// 光源の設定
	float fLightPos[] = { 0.45f, 0.55f, 1.0f, 0.0f };
	float fLightDif[] = { 0.9f, 0.9f, 0.9f, 0.0f };
	float fLightAmb[] = { 1.0f, 1.0f, 1.0f, 0.0f };
	float fLightSpq[] = { 0.9f, 0.9f, 0.9f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, fLightPos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, fLightDif);
	glLightfv(GL_LIGHT0, GL_AMBIENT, fLightAmb);
	glLightfv(GL_LIGHT0, GL_SPECULAR, fLightSpq);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	// スムーズシェーディング
	//glShadeModel(GL_SMOOTH);

	// 頂点設定順を時計回りに設定
	glFrontFace(GL_CW);

	// テクスチャを有効
	glEnable(GL_TEXTURE_2D);

	// テクスチャ座標配列を有効
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	// 背景テクスチャの準備
	glGenTextures(1, &m_unBgTexture);
	glBindTexture(GL_TEXTURE_2D, m_unBgTexture);
	ImageInfo imageInfo;
	imageInfo.load(g_szBgImagePath);
	if (imageInfo.getDepth() == 24) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageInfo.getWidth(), imageInfo.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, imageInfo.getImageData());
	} else {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageInfo.getWidth(), imageInfo.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, imageInfo.getImageData());
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	pmdRenderer.load("res\\pmd\\Lat式ミクVer2.3\\Lat式ミクVer2.3_Normal.pmd");
}

void Renderer::render(void)
{
	static double dRadian = 0.0;

	// 画面初期化
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 行列の初期化
	glLoadIdentity();

	// 視点の位置設定
	//gluLookAt(50.0 * sin(dRadian), 30.0, -50.0 * cos(dRadian), 0.0, 10.0, 0.0, 0.0, 1.0, 0.0);
	gluLookAt(50.0 * sin(dRadian), 20.0, -50.0 * cos(dRadian), 0.0, 10.0, 0.0, 0.0, 1.0, 0.0);
	//gluLookAt(0.0, 20.0, -50.0, 0.0, 10.0, 0.0, 0.0, 1.0, 0.0);

	// 描画
	glVertexPointer(3, GL_FLOAT, 0, m_afVertex);
	glTexCoordPointer(2, GL_FLOAT, 0, m_afTextureAxis);
	glBindTexture(GL_TEXTURE_2D, m_unBgTexture);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, m_ashVertexIndex);
	pmdRenderer.render();
	glutSwapBuffers();

	// 回転角設定
	dRadian += 0.025;
	if (dRadian > 2 * M_PI) {
		dRadian -= 2 * M_PI;
	}
}

void Renderer::resize(int w, int h)
{
	// ウィンドウ全体をビューポートに設定
	glViewport(0, 0, w, h);

	// 透視投影モード
	glMatrixMode(GL_PROJECTION);
	// 変換行列の初期化
	glLoadIdentity();
	// 透視投影
	gluPerspective(27.0, (double)w / (double)h, 1.0, 1000.0);

	// モデルビューモード
	glMatrixMode(GL_MODELVIEW);
}

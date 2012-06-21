#include <iostream>
#include <gl/glut.h>

#include "ServerOperation.h"
#include "Renderer.h"
#include "ImageInfo.h"

Renderer::Renderer(void)
{
	// 背景ポリゴンの初期化
//	m_afVertex[0] = -1.0f; m_afVertex[1] = 1.0f; m_afVertex[2] = 0.0f;
//	m_afVertex[3] = -1.0f; m_afVertex[4] = -1.0f; m_afVertex[5] = 0.0f;
//	m_afVertex[6] = 1.0f; m_afVertex[7] = -1.0f; m_afVertex[8] = 0.0f;
//	m_afVertex[9] = 1.0f; m_afVertex[10] = 1.0f; m_afVertex[11] = 0.0f;

	// 背景ポリゴンの初期化(テストデータ)
	m_afVertex[0] = -0.9f; m_afVertex[1] = 0.9f; m_afVertex[2] = 0.0f;
	m_afVertex[3] = -0.9f; m_afVertex[4] = -0.9f; m_afVertex[5] = 0.0f;
	m_afVertex[6] = 0.9f; m_afVertex[7] = -0.9f; m_afVertex[8] = 0.0f;
	m_afVertex[9] = 0.9f; m_afVertex[10] = 0.9f; m_afVertex[11] = 0.0f;

	// 背景ポリゴンの頂点インデックスの初期化
	m_ashVertexIndex[0] = 0; m_ashVertexIndex[1] = 1; m_ashVertexIndex[2] = 2;
	m_ashVertexIndex[3] = 0; m_ashVertexIndex[4] = 2; m_ashVertexIndex[5] = 3;

	// 背景テクスチャ座標配列の初期化
	m_afTextureAxis[0] = 0.0f; m_afTextureAxis[1] = 0.0f;
	m_afTextureAxis[2] = 0.0f; m_afTextureAxis[3] = 1.0f;
	m_afTextureAxis[4] = 1.0f; m_afTextureAxis[5] = 1.0f;
	m_afTextureAxis[6] = 1.0f; m_afTextureAxis[7] = 0.0f;

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
}

void Renderer::render(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertexPointer(3, GL_FLOAT, 0, m_afVertex);
	glTexCoordPointer(2, GL_FLOAT, 0, m_afTextureAxis);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, m_ashVertexIndex);
	glFlush();
}

#include <iostream>
#include <gl/glut.h>

#include "Renderer.h"


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
}


Renderer::~Renderer(void)
{
}

void Renderer::init(void)
{
	// 背景色の設定
	glClearColor(1.0, 1.0, 0.6, 1.0);

	// 頂点配列を使用可
	glEnableClientState(GL_VERTEX_ARRAY);
}

void Renderer::render(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertexPointer(3, GL_FLOAT, 0, m_afVertex);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, m_ashVertexIndex);
	glFlush();
}

#include <iostream>
#include <gl/glut.h>

#include "Renderer.h"


Renderer::Renderer(void)
{
	// �w�i�|���S���̏�����
//	m_afVertex[0] = -1.0f; m_afVertex[1] = 1.0f; m_afVertex[2] = 0.0f;
//	m_afVertex[3] = -1.0f; m_afVertex[4] = -1.0f; m_afVertex[5] = 0.0f;
//	m_afVertex[6] = 1.0f; m_afVertex[7] = -1.0f; m_afVertex[8] = 0.0f;
//	m_afVertex[9] = 1.0f; m_afVertex[10] = 1.0f; m_afVertex[11] = 0.0f;

	// �w�i�|���S���̏�����(�e�X�g�f�[�^)
	m_afVertex[0] = -0.9f; m_afVertex[1] = 0.9f; m_afVertex[2] = 0.0f;
	m_afVertex[3] = -0.9f; m_afVertex[4] = -0.9f; m_afVertex[5] = 0.0f;
	m_afVertex[6] = 0.9f; m_afVertex[7] = -0.9f; m_afVertex[8] = 0.0f;
	m_afVertex[9] = 0.9f; m_afVertex[10] = 0.9f; m_afVertex[11] = 0.0f;

	// �w�i�|���S���̒��_�C���f�b�N�X�̏�����
	m_ashVertexIndex[0] = 0; m_ashVertexIndex[1] = 1; m_ashVertexIndex[2] = 2;
	m_ashVertexIndex[3] = 0; m_ashVertexIndex[4] = 2; m_ashVertexIndex[5] = 3;
}


Renderer::~Renderer(void)
{
}

void Renderer::init(void)
{
	// �w�i�F�̐ݒ�
	glClearColor(1.0, 1.0, 0.6, 1.0);

	// ���_�z����g�p��
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

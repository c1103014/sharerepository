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
	// �w�i�|���S���̏�����
//	m_afVertex[0] = -1.0f; m_afVertex[1] = 1.0f; m_afVertex[2] = 0.0f;
//	m_afVertex[3] = -1.0f; m_afVertex[4] = -1.0f; m_afVertex[5] = 0.0f;
//	m_afVertex[6] = 1.0f; m_afVertex[7] = -1.0f; m_afVertex[8] = 0.0f;
//	m_afVertex[9] = 1.0f; m_afVertex[10] = 1.0f; m_afVertex[11] = 0.0f;

	// �w�i�|���S���̏�����(�e�X�g�f�[�^)
	m_afVertex[0] = -9.0f; m_afVertex[1] = 18.0f; m_afVertex[2] = 10.0f;
	m_afVertex[3] = -9.0f; m_afVertex[4] = 0.0f; m_afVertex[5] = 10.0f;
	m_afVertex[6] = 9.0f; m_afVertex[7] = 0.0f; m_afVertex[8] = 10.0f;
	m_afVertex[9] = 9.0f; m_afVertex[10] = 18.0f; m_afVertex[11] = 10.0f;

	// �w�i�|���S���̒��_�C���f�b�N�X�̏�����
	m_ashVertexIndex[0] = 0; m_ashVertexIndex[1] = 1; m_ashVertexIndex[2] = 2;
	m_ashVertexIndex[3] = 0; m_ashVertexIndex[4] = 2; m_ashVertexIndex[5] = 3;

	// �w�i�e�N�X�`�����W�z��̏�����
	m_afTextureAxis[0] = 1.0f; m_afTextureAxis[1] = 0.0f;
	m_afTextureAxis[2] = 1.0f; m_afTextureAxis[3] = 1.0f;
	m_afTextureAxis[4] = 0.0f; m_afTextureAxis[5] = 1.0f;
	m_afTextureAxis[6] = 0.0f; m_afTextureAxis[7] = 0.0f;

	// �e�N�X�`���ϐ��̏�����
	m_unBgTexture = 0;
}

Renderer::~Renderer(void)
{
}

void Renderer::init(void)
{
	// �w�i�F�̐ݒ�
	glClearColor(1.0, 1.0, 0.6, 1.0);

	// ���_�z���L��
	glEnableClientState(GL_VERTEX_ARRAY);

	// �f�v�X�o�b�t�@��L��
	glEnable(GL_DEPTH_TEST);

	// �J�����O��L��
	glEnable(GL_CULL_FACE);

	// �w�ʂ̃|���S���𓧖���
	glCullFace(GL_FRONT);

	// �A���t�@�u�����h
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// �A���t�@�e�X�g
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GEQUAL, 0.5);

	// �����̐ݒ�
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

	// �X���[�Y�V�F�[�f�B���O
	//glShadeModel(GL_SMOOTH);

	// ���_�ݒ菇�����v���ɐݒ�
	glFrontFace(GL_CW);

	// �e�N�X�`����L��
	glEnable(GL_TEXTURE_2D);

	// �e�N�X�`�����W�z���L��
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	// �w�i�e�N�X�`���̏���
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

	pmdRenderer.load("res\\pmd\\Lat���~�NVer2.3\\Lat���~�NVer2.3_Normal.pmd");
}

void Renderer::render(void)
{
	static double dRadian = 0.0;

	// ��ʏ�����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// �s��̏�����
	glLoadIdentity();

	// ���_�̈ʒu�ݒ�
	//gluLookAt(50.0 * sin(dRadian), 30.0, -50.0 * cos(dRadian), 0.0, 10.0, 0.0, 0.0, 1.0, 0.0);
	gluLookAt(50.0 * sin(dRadian), 20.0, -50.0 * cos(dRadian), 0.0, 10.0, 0.0, 0.0, 1.0, 0.0);
	//gluLookAt(0.0, 20.0, -50.0, 0.0, 10.0, 0.0, 0.0, 1.0, 0.0);

	// �`��
	glVertexPointer(3, GL_FLOAT, 0, m_afVertex);
	glTexCoordPointer(2, GL_FLOAT, 0, m_afTextureAxis);
	glBindTexture(GL_TEXTURE_2D, m_unBgTexture);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, m_ashVertexIndex);
	pmdRenderer.render();
	glutSwapBuffers();

	// ��]�p�ݒ�
	dRadian += 0.025;
	if (dRadian > 2 * M_PI) {
		dRadian -= 2 * M_PI;
	}
}

void Renderer::resize(int w, int h)
{
	// �E�B���h�E�S�̂��r���[�|�[�g�ɐݒ�
	glViewport(0, 0, w, h);

	// �������e���[�h
	glMatrixMode(GL_PROJECTION);
	// �ϊ��s��̏�����
	glLoadIdentity();
	// �������e
	gluPerspective(27.0, (double)w / (double)h, 1.0, 1000.0);

	// ���f���r���[���[�h
	glMatrixMode(GL_MODELVIEW);
}

#pragma once

#include <gl/glut.h>

class Renderer
{
public:
	Renderer(void);
	virtual ~Renderer(void);
	void init(void);
	void render(void);
	void resize(int w, int h);
private:
	GLfloat m_afVertex[12];
	GLushort m_ashVertexIndex[6];
	GLfloat m_afTextureAxis[8];
	GLuint m_unBgTexture;
};

#pragma once

class Renderer
{
public:
	Renderer(void);
	virtual ~Renderer(void);
	void init(void);
	void render(void);
private:
	GLfloat m_afVertex[12];
	GLushort m_ashVertexIndex[6];
};

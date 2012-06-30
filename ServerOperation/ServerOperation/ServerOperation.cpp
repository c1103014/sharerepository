#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

#include <Windows.h>
#include <gl/glut.h>

#include "ServerOperation.h"
#include "Renderer.h"

void display(void);
void resize(int w, int h);
Renderer g_renderer;

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	g_renderer.init();
	glutMainLoop();
	return 0;
}

void display(void)
{
	g_renderer.render();
}

void resize(int w, int h)
{
	g_renderer.resize(w, h);
}

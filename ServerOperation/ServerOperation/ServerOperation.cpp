#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

#include "ServerOperation.h"
#include "Renderer.h"

#include <gl/glut.h>

void display(void);
Renderer g_renderer;

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	g_renderer.init();
	glutMainLoop();
	return 0;
}

void display(void)
{
	g_renderer.render();
}

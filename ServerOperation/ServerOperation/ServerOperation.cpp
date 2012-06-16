#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

#include <gl/glut.h>

#include "ServerOperation.h"
#include "Renderer.h"

void display(void);

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

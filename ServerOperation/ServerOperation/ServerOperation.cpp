//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

#include <Windows.h>
#include <gl/glut.h>

#include "ServerOperation.h"
#include "Renderer.h"

void display(void);
void resize(int w, int h);
void timer(int value);
Renderer g_renderer;

//int main(int argc, char *argv[])
//{
//	//test
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
//	glutCreateWindow(argv[0]);
//	glutDisplayFunc(display);
//	glutReshapeFunc(resize);
//	glutTimerFunc(1000 / 30, timer, 0);
//	g_renderer.init();
//	glutMainLoop();
//	return 0;
//}

void display(void)
{
	g_renderer.render();
}

void resize(int w, int h)
{
	g_renderer.resize(w, h);
}

void timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / 30, timer, 0);
}

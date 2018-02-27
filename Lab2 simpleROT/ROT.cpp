#include <windows.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/GLUT.h> //

void myDisplay(void)
{

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2i(180, 15);
	glVertex2i(10, 145);
	glEnd();

	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);

	glFlush();

}
void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);

}

int main(int argc, char * argv[])
{

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

	glutInitWindowPosition(50, 100);

	glutInitWindowSize(400, 300);

	glutCreateWindow("OpenGL");

	init();

	glutDisplayFunc(&myDisplay);

	glutMainLoop();

	return 0;

}

/*
	
	OpenGL GLUT template for Xcode 3.

*/
   
#include <GLUT/glut.h>
#include <stdio.h>

void init(void);
void display(void);
void reshape(int, int);
void mouse(int, int, int, int);

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); /* Sets the window to double buffered with RGB colour profile */
	glutInitWindowSize(300, 300); /* Sets the size of the window */
	glutInitWindowPosition(100, 100); /* Sets the window position */
	glutCreateWindow("GLUT Template"); /* Creates the window with title GLUT Template */
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMainLoop();

    return 0;
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void display(void)
{
	/* code goes here */
}

void reshape(int w, int h)
{
	/* window reshape function */
}

void mouse(int button, int state, int x, int y)
{
	/* mouse handling function */
}

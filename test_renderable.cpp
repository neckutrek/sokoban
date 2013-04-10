//
//  main.cpp
//  OpenGLGLUTApp
//
//  Created by Marcus Johansson on 4/4/13.
//
//
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include "MicroGlut.h"
// Linking hint for Lightweight IDE
// uses framework Cocoa
#endif

#include "GL_utilities.h"
#include "VectorUtils3.h"
#include "OpenGLObject.h"
#include "OpenGLCamera.h"
#include "loadobj.h"
#include "LoadTGA2.h"

#include "Renderable.h"

#include <iostream>
using namespace std;

Renderable r;

void init(void) {
    r = Renderable();
}

void display(void) {
    
}

void timer(void) {
    
}

int main(int argc, char *argv[]) {
    
    srand(time(0));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("TSBK07 Lab 4");
	glutDisplayFunc(display);
	//glutPassiveMotionFunc(updateMouse);
	//glutKeyboardFunc(setKeyDown);
	//glutKeyboardUpFunc(setKeyUp);
	init();
	glutTimerFunc(20, &timer, 0);
    
	glutMainLoop();
	exit(0);
}

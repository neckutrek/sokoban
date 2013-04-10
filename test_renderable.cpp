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
#endif

#include "GL_utilities.h"
#include "VectorUtils3.h"
#include "loadobj.h"
#include "LoadTGA2.h"

#include "Renderable.h"

#include <iostream>
using namespace std;

mat4 projection_transformation;
Renderable r;
GLuint program_ref_id;

void init(void) {
    glClearColor(0.2,0.2,0.5,0);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
    
    program = loadShaders("terrain.vert", "terrain.frag");
    glUseProgram(program_ref_id);

    frustum(-0.2, 0.2, -0.2, 0.2, 0.1, 500.0, projection_transformation);
    
    glUniformMatrix4fv(glGetUniformLocation(program, "projection_transformation"),
                       1, GL_TRUE, projection_transformation);
    
    r = Renderable("bunnyplus.obj");
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(program_ref_id);
	
	mat4 model_transformation;
	mat4 camera_transformation;
    
	IdentityMatrix(model_transformation);
    IdentityMatrix(camera_transformation);
    
	glUniformMatrix4fv(glGetUniformLocation(program, "model_transformation"),
                       1, GL_TRUE, model_transformation);
	glUniformMatrix4fv(glGetUniformLocation(program, "camera_transformation"),
                       1, GL_TRUE, camera_transformation);
	
    r.render(program_ref_id);
    
    glutSwapBuffers();
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
	init();
	glutTimerFunc(20, &timer, 0);
    
	glutMainLoop();
	exit(0);
}

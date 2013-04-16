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
#include "GameObject.h"

#include <iostream>
using namespace std;

mat4 projection_transformation;
GameObject* my_game_object;
GLuint program_ref_id;

void init(void) {
    glClearColor(0.2,0.2,0.5,0);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
    
    program_ref_id = loadShaders("terrain.vert", "terrain.frag");
    glUseProgram(program_ref_id);

    projection_transformation = frustum(-0.2, 0.2, -0.2, 0.2, 0.1, 500.0);
    
    glUniformMatrix4fv(glGetUniformLocation(program_ref_id, "projection_transformation"),
                       1, GL_TRUE, projection_transformation.m);
    
    my_game_object = new GameObject();
    my_game_object->loadModel("bunnyplus.obj");
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(program_ref_id);
	
	mat4 model_transformation;
	mat4 camera_transformation;
    
	model_transformation = IdentityMatrix();
    camera_transformation= IdentityMatrix();
    
	glUniformMatrix4fv(glGetUniformLocation(program_ref_id, "model_transformation"),
                       1, GL_TRUE, model_transformation.m);
	glUniformMatrix4fv(glGetUniformLocation(program_ref_id, "camera_transformation"),
                       1, GL_TRUE, camera_transformation.m);
	
    my_game_object->render(program_ref_id);
    
    glutSwapBuffers();
}

int main(int argc, char *argv[]) {
    
    srand(time(0));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("TSBK07 Lab 4");
	glutDisplayFunc(display);
	init();
	//glutTimerFunc(20, &timer, 0);
    
	glutMainLoop();
	exit(0);
}

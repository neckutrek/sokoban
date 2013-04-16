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
#include "VectorUtils3Addons.h"
#include "loadobj.h"
#include "LoadTGA2.h"
#include "GameObject.h"
#include "Camera.h"

#include <iostream>
using namespace std;

mat4 projection_transformation;
GameObject* my_game_object;
Model* bunnyModel;
GLuint program_ref_id;

void init(void) {
    glClearColor(0.2,0.2,0.5,0);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
    
    program_ref_id = loadShaders("shader_1.vert", "shader_1.frag");
    glUseProgram(program_ref_id);

    projection_transformation = frustum(-0.2, 0.2, -0.2, 0.2, 0.1, 500.0);
    
    //projection_transformation = IdentityMatrix();
    glUniformMatrix4fv(glGetUniformLocation(program_ref_id, "projection_transformation"),
                       1, GL_TRUE, projection_transformation.m);
    
    //bunnyModel = LoadModelPlus("bunnyplus.obj");
    
    my_game_object = new GameObject();
    my_game_object->loadModel("bunnyplus.obj");
    my_game_object->setPosition(0, 0, -3);
	my_game_object->setAcceleration(0, 0, 0.001);
    my_game_object->setRotAcceleration(1, 1, 0, 0.01);
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
	
    /*mat4 trans_matrix = IdentityMatrix();
    trans_matrix.m[11] = -3;
    
    glBindVertexArray(bunnyModel->vao);
    glUniformMatrix4fv(glGetUniformLocation(program_ref_id,
                                            "model_transformation"),
                       1, GL_TRUE, trans_matrix.m);
    */
    //DrawModel(bunnyModel, program_ref_id, "vertex_coordinate", "normal_vector", "texture_coordinate");
    //glDrawElements(GL_TRIANGLES, bunnyModel->numIndices, GL_UNSIGNED_INT, 0L);
    
    my_game_object->render(program_ref_id);
    
    glutSwapBuffers();
}

void update(int dtime)
{
    glutTimerFunc(20, &update, dtime);
    my_game_object->update(dtime);
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    srand(time(0));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("TSBK07 Lab 4");
	glutDisplayFunc(display);
	init();
	glutTimerFunc(20, &update, 0);
    
	glutMainLoop();
	exit(0);
}

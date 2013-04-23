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
#include "LightContainer.h"

#include <iostream>
#include <vector>
using namespace std;

mat4 projection_transformation;
GameObject* my_game_object;
Model* bunnyModel;
GLuint program_ref_id;
LightContainer* light_instances;

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
    
    my_game_object = new GameObject();
    my_game_object->loadModel("bunnyplus.obj");
    my_game_object->setPosition(-5, 0, -2);
    my_game_object->setVelocity(0.05, 0.0, 0.0);
	my_game_object->setAcceleration(0, 0, 0.0);
    my_game_object->setRotVelocity(1, 1, 0, 0.05);
    
    light_instances = new LightContainer();
    light_instances->addLight(vec3(-5.0, 0.0, 0.0), vec3(1.0, 0.0, 0.0), 1.0);
    light_instances->addLight(vec3(0.0, 0.0, 5.0), vec3(0.0, 1.0, 0.0), 0.5);
    light_instances->addLight(vec3(5.0, 0.0, 0.0), vec3(0.0, 0.0, 1.0), 1.0);
    
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(program_ref_id);
	
    // upload light information to shader
    
    glUniform1i(glGetUniformLocation(program_ref_id, "light_counter"), light_instances->getLightCounter());
    
    glUniform3fv(glGetUniformLocation(program_ref_id, "light_sources_pos_array"),
                 8, light_instances->getLightSourcesPositionArray());
    
    glUniform3fv(glGetUniformLocation(program_ref_id, "light_sources_color_array"),
                 8, light_instances->getLightSourcesColorArray());
    
    glUniform1fv(glGetUniformLocation(program_ref_id, "light_sources_lux_array"),
                 8, light_instances->getLightSourcesLuxArray());
    
    
    // upload model and camera matrices to shader
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
    
    // render game objects
    my_game_object->render(program_ref_id);
    
    // swap the buffers
    glutSwapBuffers();
}

void update(int dtime)
{
    glutTimerFunc(20, &update, dtime);
    
    //light_instances->update(dtime);
    my_game_object->update(dtime);
    
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    srand(time(0));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutCreateWindow("TSBK07 Lab 4");
	glutDisplayFunc(display);
	init();
	glutTimerFunc(20, &update, 0);
    
	glutMainLoop();
	exit(0);
}

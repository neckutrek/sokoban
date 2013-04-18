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
#include "ObjectCamera.h"
#include "DebugCamera.h"
#include "CutsceneCamera.h"
#include "CameraManager.h"

#include <iostream>
using namespace std;

mat4 projection_transformation;
GameObject objects[27];
Model* bunnyModel;
DebugCamera* c1 = new DebugCamera();
ObjectCamera* c2 = new ObjectCamera(&objects[0]);
CutsceneCamera* c3 = new CutsceneCamera();
int keyboardMap[256];
GLuint program_ref_id;

void init(void) {
    glClearColor(0.2,0.2,0.5,0);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
    
    program_ref_id = loadShaders("shader_1.vert", "shader_1.frag");
    glUseProgram(program_ref_id);
	
    projection_transformation = frustum(-0.1, 0.1, -0.1, 0.1, 0.1, 100.0);
    
    //projection_transformation = IdentityMatrix();
    glUniformMatrix4fv(glGetUniformLocation(program_ref_id, "projection_transformation"),
                       1, GL_TRUE, projection_transformation.m);
    
    //bunnyModel = LoadModelPlus("bunnyplus.obj");
    
	for(int x=0; x<3; x++)
		for(int y=0; y<3; y++)
			for(int z=0; z<3; z++)
			{
				objects[9*x+3*y+z] = GameObject();
				objects[9*x+3*y+z].loadModel("bunnyplus.obj");
				objects[9*x+3*y+z].setPosition(3*(x-1), 3*(y-1), 3*(z-1));
			}
	
	c3->setStartPos(vec3(6, 5, 4));
	c3->setEndPos(vec3(3.5, 3.5, -1.5));
	c3->setStartViewLoc(objects[0].getPosition());
	c3->setEndViewLoc(objects[24].getPosition());
	c3->setTime(150);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(program_ref_id);
	glUniformMatrix4fv(glGetUniformLocation(program_ref_id, "camera_transformation"),
                       1, GL_TRUE, CameraManager::getInstance().getActiveCamera()->getCameraMatrix().m);
    
	for(int i=0; i<27; i++)
		objects[i].render(program_ref_id);
    
    glutSwapBuffers();
}

void setKeyUp(unsigned char key, int x, int y) {
	keyboardMap[key] = 0;
}

void setKeyDown(unsigned char key, int x, int y) {
	keyboardMap[key] = 1;
}

void updateKeyboard() {
	if (keyboardMap['1'] == 1)
		CameraManager::getInstance().setActiveCamera(c1);
	if (keyboardMap['2'] == 1)
		CameraManager::getInstance().setActiveCamera(c2);
	if (keyboardMap['3'] == 1)
		CameraManager::getInstance().setActiveCamera(c3);
	CameraManager::getInstance().getActiveCamera()->updateKeyboard(keyboardMap);
}

void update(int dtime)
{
    glutTimerFunc(20, &update, dtime);
	for(int i=0; i<27; i++)
		objects[i].update(dtime);
	Camera* activeCamera = CameraManager::getInstance().getActiveCamera();
	activeCamera->update(dtime);
	CameraManager::getInstance().update();
	updateKeyboard();
	std::cout << "viewDirection = " << activeCamera->getViewDirection() << std::endl;
	std::cout << "position = " << activeCamera->getPosition() << std::endl << std::endl;
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
	glutKeyboardFunc(setKeyDown);
	glutKeyboardUpFunc(setKeyUp);
	init();
	glutTimerFunc(20, &update, 0);
    
	glutMainLoop();
	exit(0);
}

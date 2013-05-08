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
#include "GO_Wall.h"
#include "ObjectCamera.h"
#include "DebugCamera.h"
#include "CutsceneCamera.h"
#include "CameraManager.h"
#include "LevelGenerator.h"
#include "LightManager.h"
#include "GameObjectManager.h"
#include "GO_Billboard.h"

#include <iostream>
using namespace std;

mat4 projection_transformation;
Model* bunnyModel;
DebugCamera* c1 = new DebugCamera();
CutsceneCamera* c3 = new CutsceneCamera();
int keyboardMap[256];
GLuint program_ref_id;
LightContainer* light_instances;

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
    
    
    light_instances = new LightContainer();
    light_instances->addLight(vec3(-5.0, 0.0, 0.0), vec3(1.0, 0.0, 0.0), 1.0);
    light_instances->addLight(vec3(0.0, 0.0, 5.0), vec3(0.0, 1.0, 0.0), 0.5);
    light_instances->addLight(vec3(5.0, 0.0, 0.0), vec3(0.0, 0.0, 1.0), 1.0);
	GameObjectManager::getInstance().addObject(GameObjectFactory::getInstance().createBillboard(vec3(0,10,0)));
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // upload light information to shader
    glUniform1i(glGetUniformLocation(program_ref_id, "light_counter"), light_instances->getLightCounter());
    glUniform3fv(glGetUniformLocation(program_ref_id, "light_sources_pos_array"),
                 8, light_instances->getLightSourcesPositionArray());
    glUniform3fv(glGetUniformLocation(program_ref_id, "light_sources_color_array"),
                 8, light_instances->getLightSourcesColorArray());
    glUniform1fv(glGetUniformLocation(program_ref_id, "light_sources_lux_array"),
                 8, light_instances->getLightSourcesLuxArray());
    
	glUseProgram(program_ref_id);
	glUniformMatrix4fv(glGetUniformLocation(program_ref_id, "camera_transformation"),
                       1, GL_TRUE, CameraManager::getInstance().getActiveCamera()->getCameraMatrix().m);
	
	GameObjectManager::getInstance().render(program_ref_id);
    
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
	if (keyboardMap['3'] == 1)
		CameraManager::getInstance().setActiveCamera(c3);
	CameraManager::getInstance().getActiveCamera()->updateKeyboard(keyboardMap);
}

void updateMouse(int x, int y) {
	GLfloat dx = x - 500/2;
	GLfloat dy = y - 500/2;
	ObjectCamera* oc = dynamic_cast<ObjectCamera*>(CameraManager::getInstance().getActiveCamera());
	if(oc)
		oc->setViewDirection(dy/100, dx/100);
}

void update(int dtime)
{
    glutTimerFunc(20, &update, dtime);
	Camera* activeCamera = CameraManager::getInstance().getActiveCamera();
	activeCamera->update(dtime);
	CameraManager::getInstance().update(dtime);
	GameObjectManager::getInstance().update(dtime);
	updateKeyboard();
	//std::cout << "viewDirection = " << activeCamera->getViewDirection() << std::endl;
	//std::cout << "position = " << activeCamera->getPosition() << std::endl << std::endl;
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    srand(time(0));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitContextVersion(3,2);
	glutInitWindowSize(500, 500);
	glutCreateWindow("TSBK07 Lab 4");
	glutDisplayFunc(display);
	glutPassiveMotionFunc(updateMouse);
	glutKeyboardFunc(setKeyDown);
	glutKeyboardUpFunc(setKeyUp);
	init();
	glutTimerFunc(20, &update, 0);
    
	if(LevelGenerator::getInstance().fileExists("level1.txt"))
	{
		LevelGenerator::getInstance().load("level1.txt");
	}
	
	glutMainLoop();
	exit(0);
}

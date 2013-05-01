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
#include "LightContainer.h"
#include "MaterialManager.h"
#include "Wall.h"

#include <iostream>
using namespace std;

mat4 projection_transformation;
GameObject* objects[27];
Model* bunnyModel;
DebugCamera* c1 = new DebugCamera();
ObjectCamera* c2 = new ObjectCamera(objects[0]);
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
    
    MaterialManager::getInstance().initialize(program_ref_id);
	
    projection_transformation = frustum(-0.1, 0.1, -0.1, 0.1, 0.1, 100.0);
    
    //projection_transformation = IdentityMatrix();
    glUniformMatrix4fv(glGetUniformLocation(program_ref_id, "projection_transformation"),
                       1, GL_TRUE, projection_transformation.m);
    
    //bunnyModel = LoadModelPlus("bunnyplus.obj");
    
    string models[5] =
    {"bunnyplus.obj", "cow.obj", "klingon.obj", "plutt.obj", "teddy.obj"};
    
    string skins[8] =
    {"bilskissred.tga", "conc.tga", "dirt.tga", "grass.tga", "maskros512.tga",
    "rutor.tga", "SkyBox512.tga", "wall_512_1_05.tga"};
    
    int i=0;
    int j=0;
	for(int x=0; x<3; x++)
		for(int y=0; y<3; y++)
			for(int z=0; z<3; z++)
			{
				objects[9*x+3*y+z] = new Wall(vec3(3*(x-1), 3*(y-1), 3*(z-1)));
				objects[9*x+3*y+z]->loadModel(models[j].c_str());
                objects[9*x+3*y+z]->addMaterial(skins[i].c_str(), 0.5, 200);
                objects[9*x+3*y+z]->addMaterial(skins[i+1].c_str(), 0.5, 50);
                i++; j++;
                if (i>=7) i=0;
                if (j>=5) j=0;
			}
	
	c3->addWaypoint(vec3(5.5,5.5,-3.5), objects[13]->getPosition(), 250);
	c3->addWaypoint(vec3(6,5,4), objects[0]->getPosition(), 20);
	c3->addWaypoint(vec3(3.5,3.5,-1.5), objects[24]->getPosition(), 150);
	c3->addWaypoint(vec3(0,0,-8), objects[13]->getPosition(), 400);
	c3->addWaypoint(vec3(0,0,-8), objects[13]->getPosition(), 450);
    
    light_instances = new LightContainer();
    light_instances->addLight(vec3(-5.0, 0.0, 0.0), vec3(1.0, 1.0, 1.0), 1.0);
    light_instances->addLight(vec3(0.0, 0.0, 5.0), vec3(1.0, 1.0, 1.0), 1.0);
//    light_instances->addLight(vec3(5.0, 0.0, 0.0), vec3(1.0, 1.0, 1.0), 1.0);
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
    
	for(int i=0; i<27; i++)
		objects[i]->render(program_ref_id);
    
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
		objects[i]->update(dtime);
	Camera* activeCamera = CameraManager::getInstance().getActiveCamera();
	activeCamera->update(dtime);
	CameraManager::getInstance().update(dtime);
	updateKeyboard();
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    srand(time(0));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitContextVersion(3,2);
	glutInitWindowSize(800, 800);
	glutCreateWindow("TSBK07 Lab 4");
	glutDisplayFunc(display);
	glutKeyboardFunc(setKeyDown);
	glutKeyboardUpFunc(setKeyUp);
	init();
	glutTimerFunc(20, &update, 0);
    
	glutMainLoop();
	exit(0);
}

//
//
//


#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include "MicroGlut.h"
#endif

#include <ctime>

#include "GL_utilities.h"
#include "VectorUtils3Addons.h"
#include "loadobj.h"
#include "LoadTGA2.h"

#include "CameraManager.h"
#include "ObjectCamera.h"
#include "DebugCamera.h"
#include "CutsceneCamera.h"

#include "LightManager.h"
#include "MaterialManager.h"
#include "GameObjectManager.h"

#include "GameObjectFactory.h"
#include "GameObject.h"

#include <string>
using namespace std;

//#include "SigmaGameEngine.h"

GLuint shaderProgramID_;
DebugCamera* c1 = new DebugCamera();
CutsceneCamera* c3 = new CutsceneCamera();
int keyboardMap[256];

void _display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    LightManager lm = LightManager::getInstance();
    
    glUniform1i(glGetUniformLocation(shaderProgramID_, "light_counter"),
                lm.getLightCounter());
    glUniform3fv(glGetUniformLocation(shaderProgramID_, "light_sources_pos_array"),
                 8, lm.getLightSourcesPositionArray());
    glUniform3fv(glGetUniformLocation(shaderProgramID_, "light_sources_color_array"),
                 8, lm.getLightSourcesColorArray());
    glUniform1fv(glGetUniformLocation(shaderProgramID_, "light_sources_lux_array"),
                 8, lm.getLightSourcesLuxArray());
    
	glUseProgram(shaderProgramID_);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramID_, "camera_transformation"),
                       1, GL_TRUE,
                       CameraManager::getInstance().getActiveCamera()->getCameraMatrix().m);
    
    //std::cerr << "camera_transformation:\n" << CameraManager::getInstance().getActiveCamera()->getCameraMatrix() << std::endl;
    
    GameObjectManager::getInstance().render(shaderProgramID_);
    
    glutSwapBuffers();
}

void updateKeyboard() {
    
    //std::cerr << "updateKeyboard" << std::endl;
    
	if (keyboardMap['1'] == 1)
		CameraManager::getInstance().setActiveCamera(c1);
	if (keyboardMap['3'] == 1)
		CameraManager::getInstance().setActiveCamera(c3);
    
	CameraManager::getInstance().getActiveCamera()->updateKeyboard(keyboardMap);
    
}

void _update(int timeStep)
{
    glutTimerFunc(20, _update, timeStep);
    
    //LightManager::getInstance().update(timeStep);
    GameObjectManager::getInstance().update(timeStep);
	CameraManager::getInstance().update(timeStep);
	
    updateKeyboard();
    glutWarpPointer(50, 50);
    glutPostRedisplay();
}


void setKeyUp(unsigned char key, int x, int y) {
	keyboardMap[key] = 0;
}

void setKeyDown(unsigned char key, int x, int y) {
	keyboardMap[key] = 1;
}

void constructSGE(int argc,
                  char *argv[],
                  std::string vertShaderFileName,
                  std::string fragShaderFileName,
                  int windowWidth,
                  int windowHeight,
                  std::string windowName) {
    srand(time(0));
    
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitContextVersion(3,2);
    
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow(windowName.c_str());
    
    glutDisplayFunc(_display);
	glutKeyboardFunc(setKeyDown);
	glutKeyboardUpFunc(setKeyUp);
    
    glClearColor(0.3, 0.3, 0.5, 0.0);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
    
    shaderProgramID_ = loadShaders(vertShaderFileName.c_str(),
                                   fragShaderFileName.c_str());
    glUseProgram(shaderProgramID_);
    
    MaterialManager::getInstance().initialize(shaderProgramID_);
    //LightManager::getInstance();
    CameraManager::getInstance().setActiveCamera(c1);
	
    mat4 projection_transformation = frustum(-0.1, 0.1, -0.1, 0.1, 0.1, 100.0);
    
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID_, "projection_transformation"),
                       1, GL_TRUE, projection_transformation.m);
}


void init27Objects()
{
    string models[5] =
    {"bunnyplus.obj", "button.obj", "crate.obj", "ground.obj", "sphere.obj"};
    
    string skins[3] =
    {"button_c.tga", "crate.tga", "robot_c.tga"};
    
    int i=0;
    int j=0;
	for(int x=0; x<3; x++)
		for(int y=0; y<3; y++)
			for(int z=0; z<3; z++)
			{
                GameObject* go = new GO_Wall(vec3(3*(x-1), 3*(y-1), 3*(z-1)));
                go->loadModel(models[j].c_str());
                go->addMaterial(skins[i].c_str(), 0.5, 200);
                go->addMaterial(skins[i+1].c_str(), 0.5, 50);
                go->setRotVelocity(0.5, 0.5, 0.5, 0.5);
                GameObjectManager::getInstance().addObject(go);
                
                i++; j++;
                if (i>=5-2) i=0;
                if (j>=3) j=0;
			}
}

void init1Object()
{
    GameObject* go = new GO_Wall(vec3(0.0, 0.0, 0.0));
    go->loadModel("bunnyplus.obj");
    go->addMaterial("button_c.tga", 1.0, 200);
    go->setRotVelocity(0.5, 0.5, 0.5, 0.05);
    GameObjectManager::getInstance().addObject(go);
    
    LightManager::getInstance().addLight(vec3(1.0, 1.0, 1.0), vec3(1., 1., 1.), 1.0);
}

int main(int argc, char *argv[])
{
    constructSGE(argc, argv,
                 "shader_1.vert", "shader_1.frag",
                 800, 800, "SigmaGameEngine running . . .");
    
    init1Object();
    
    glutTimerFunc(20, _update, 20);
    glutMainLoop();
}
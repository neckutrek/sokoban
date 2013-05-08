//
//
//

#include <string>
using namespace std;

#include "SigmaGameEngine.h"

DebugCamera* c1 = new DebugCamera();
//ObjectCamera* c2 = new ObjectCamera(objects[0]);
CutsceneCamera* c3 = new CutsceneCamera();
int keyboardMap[256];

void setKeyUp(unsigned char key, int x, int y) {
	keyboardMap[key] = 0;
}

void setKeyDown(unsigned char key, int x, int y) {
	keyboardMap[key] = 1;
}
/*
void updateKeyboard() {
    
    //std::cerr << "updateKeyboard" << std::endl;
    
	if (keyboardMap['1'] == 1)
		CameraManager::getInstance().setActiveCamera(c1);
    //	if (keyboardMap['2'] == 1)
    //		CameraManager::getInstance().setActiveCamera(c2);
	if (keyboardMap['3'] == 1)
		CameraManager::getInstance().setActiveCamera(c3);
    
	CameraManager::getInstance().getActiveCamera()->updateKeyboard(keyboardMap);
    
}
*/
void _display() {
    //std::cerr << "SigmaGameEngine::display()" << std::endl;
    GLuint shaderProgramID_ = SigmaGameEngine::getInstance().getShaderProgramID();
    glUseProgram(shaderProgramID_);
    
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
    
	
    CameraManager::getInstance().setActiveCamera(c1);
    
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramID_, "camera_transformation"),
                       1, GL_TRUE,
                       CameraManager::getInstance().getActiveCamera()->getCameraMatrix().m);
    
    //std::cerr << "camera_transformation:\n" << CameraManager::getInstance().getActiveCamera()->getCameraMatrix() << std::endl;
    
    GameObjectManager::getInstance().render(shaderProgramID_);
    
    glutSwapBuffers();
}

void _update(int timeStep)
{
    //std::cerr << "SigmaGameEngine::update()" << std::endl;
    glutTimerFunc(20, _update, timeStep);
    
    LightManager::getInstance().update(timeStep);
    GameObjectManager::getInstance().update(timeStep);
	CameraManager::getInstance().update(timeStep);
	
    //updateKeyboard();
    glutWarpPointer(50, 50);
    glutPostRedisplay();
}


void init1Object()
{
    GameObject* go = new GO_Wall(vec3(0.0, 0.0, 0.0));
    go->loadModel("bunnyplus.obj");
    go->addMaterial("button_c.tga", 1.0, 200);
    go->setRotVelocity(0.5, 0.5, 0.5, 0.5);
    GameObjectManager::getInstance().addObject(go);
    
    LightManager::getInstance().addLight(vec3(1., 1., 1.), vec3(1., 1., 1.), 1.0);
}

int main(int argc, char *argv[])
{
    SigmaGameEngine game = SigmaGameEngine::getInstance();
    game.initialize(argc, argv,
                    "shader_1.vert", "shader_1.frag",
                    800, 800, "SigmaGameEngine running . . .",
                    _display, _update);
    
    init1Object();
        
    game.run();
}




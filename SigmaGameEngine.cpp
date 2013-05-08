//
//
//

#include "SigmaGameEngine.h"
#include <iostream>

void _setKeyUp(unsigned char key, int x, int y) {
    SigmaGameEngine::getInstance().setKeyUp(key);
}

void _setKeyDown(unsigned char key, int x, int y) {
	SigmaGameEngine::getInstance().setKeyDown(key);
}

void _update(int timeStep) {
    SigmaGameEngine::getInstance().update(timeStep);
}

void _display(void) {
    SigmaGameEngine::getInstance().display();
}


SigmaGameEngine& SigmaGameEngine::getInstance()
{
    static SigmaGameEngine instance;
    return instance;
}
SigmaGameEngine::~SigmaGameEngine() {}

SigmaGameEngine::SigmaGameEngine()
{}

SigmaGameEngine::SigmaGameEngine(const SigmaGameEngine&) {}
SigmaGameEngine& SigmaGameEngine::operator=(const SigmaGameEngine&)
{
    return *this;
}

void SigmaGameEngine::initialize(int argc,
                                 char *argv[],
                                 std::string vertShaderFileName,
                                 std::string fragShaderFileName,
                                 int windowWidth,
                                 int windowHeight,
                                 std::string windowName)
{
    this->displayCallback = _display;
    this->updateCallback = _update;
    
    srand(time(0));
    
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitContextVersion(3,2);
    
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow(windowName.c_str());
    
    glutDisplayFunc(_display);
	glutKeyboardFunc(_setKeyDown);
	glutKeyboardUpFunc(_setKeyUp);
    
    glClearColor(0.2, 0.2, 0.6, 0.0);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
    
    this->shaderProgramID_ = loadShaders(vertShaderFileName.c_str(),
                                   fragShaderFileName.c_str());
    glUseProgram(shaderProgramID_);
    
    MaterialManager::getInstance().initialize(shaderProgramID_);
    LightManager::getInstance();
    
    mat4 projection_transformation = frustum(-0.133333, 0.133333, -0.1, 0.1, 0.1, 100.0);
    
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID_, "projection_transformation"),
                       1, GL_TRUE, projection_transformation.m);
}

void SigmaGameEngine::run()
{
    glutTimerFunc(20, _update, 20);
    glutMainLoop();
}

void SigmaGameEngine::display() {
    glUseProgram(this->shaderProgramID_);
    
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
    
	
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramID_, "camera_transformation"),
                       1, GL_TRUE,
                       CameraManager::getInstance().getActiveCamera()->getCameraMatrix().m);
    
    GameObjectManager::getInstance().render(shaderProgramID_);
    
    glutSwapBuffers();
}

void SigmaGameEngine::update(int timeStep)
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

void SigmaGameEngine::setKeyUp(unsigned char key)
{
    keyboardMap[key] = 1;
}

void SigmaGameEngine::setKeyDown(unsigned char key)
{
    keyboardMap[key] = 0;
}




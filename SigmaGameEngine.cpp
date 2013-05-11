//
//
//

#include "SigmaGameEngine.h"
#include <iostream>

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
SigmaGameEngine::~SigmaGameEngine() {
}

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
    srand(time(0));
    InputManager::getInstance().init(); // run this first to put the sdl window behind the glut window!
    
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitContextVersion(3,2);
    
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow(windowName.c_str());
    
    glutDisplayFunc(_display);
    
    glClearColor(0.2, 0.2, 0.6, 0.0);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
    
    this->shaderProgramID_ = loadShaders(vertShaderFileName.c_str(),
                                   fragShaderFileName.c_str());
    glUseProgram(shaderProgramID_);
    
    MaterialManager::getInstance().initialize(shaderProgramID_);
    LightManager::getInstance();
    
    float proj_width = 0.2 * static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
    mat4 projection_transformation = frustum(-proj_width/2, proj_width/2, -0.1, 0.1, 0.1, 100.0);
    
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID_, "projection_transformation"),
                       1, GL_TRUE, projection_transformation.m);
}

void SigmaGameEngine::run()
{
    glutTimerFunc(20, _update, 20);
    glutMainLoop();
}

void SigmaGameEngine::quit()
{
    SDL_Quit();
    exit(0);
}

void SigmaGameEngine::display() {
    glUseProgram(this->shaderProgramID_);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    LightManager& lm = LightManager::getInstance();
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
    glutTimerFunc(20, _update, timeStep);
    
    LightManager::getInstance().update(timeStep);
    GameObjectManager::getInstance().update(timeStep);
	CameraManager::getInstance().update(timeStep);
    InputManager::getInstance().update(timeStep);

    glutPostRedisplay();
}



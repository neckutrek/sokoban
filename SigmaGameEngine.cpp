//
//
//

#include "SigmaGameEngine.h"

// TODO: Take these away!
DebugCamera* c1 = new DebugCamera();
//ObjectCamera* c2 = new ObjectCamera(objects[0]);
CutsceneCamera* c3 = new CutsceneCamera();

void setKeyUp(unsigned char key, int x, int y) {
	//keyboardMap[key] = 0;
}

void setKeyDown(unsigned char key, int x, int y) {
	//keyboardMap[key] = 1;
}

void updateKeyboard() {
    /*
	if (keyboardMap['1'] == 1)
		CameraManager::getInstance().setActiveCamera(c1);
	if (keyboardMap['2'] == 1)
		CameraManager::getInstance().setActiveCamera(c2);
	if (keyboardMap['3'] == 1)
		CameraManager::getInstance().setActiveCamera(c3);
	CameraManager::getInstance().getActiveCamera()->updateKeyboard(keyboardMap);
     */
}


void _update(int timeStep) {
    SigmaGameEngine::getInstance().update(timeStep);
}

void _display(void) {
    SigmaGameEngine::getInstance().display();
}

SigmaGameEngine::SigmaGameEngine()
{}

void SigmaGameEngine::initialize(int argc,
                                 char *argv[],
                                 std::string vertShaderFileName,
                                 std::string fragShaderFileName,
                                 int windowWidth,
                                 int windowHeight,
                                 std::string windowName)
{
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
    LightManager::getInstance();
	
    mat4 projection_transformation = frustum(-0.1, 0.1, -0.1, 0.1, 0.1, 100.0);
    
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID_, "projection_transformation"),
                       1, GL_TRUE, projection_transformation.m);
}

void SigmaGameEngine::run()
{
    glutTimerFunc(20, _update, 0);
    glutMainLoop();
}

void SigmaGameEngine::display() {
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
    
    GameObjectManager::getInstance().render(shaderProgramID_);
    
    glutSwapBuffers();
}

void SigmaGameEngine::update(int timeStep)
{
    glutTimerFunc(20, _update, timeStep);
    
    LightManager::getInstance().update(timeStep);
    GameObjectManager::getInstance().update(timeStep);
	CameraManager::getInstance().update(timeStep);
	
    updateKeyboard();
    glutWarpPointer(50, 50);
    glutPostRedisplay();
}

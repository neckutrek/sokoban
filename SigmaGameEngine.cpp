//
//
//

#include "SigmaGameEngine.h"
#include <iostream>

#define FPS 30

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
    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
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
    glutTimerFunc(1000/FPS, _update, 1000/FPS);
    glutMainLoop();
}

void SigmaGameEngine::quit()
{
    SDL_Quit();
    exit(0);
}

vec3 SigmaGameEngine::check_collision_along_line(const BoundingBox & bb,
                                                 const vec3 &origin,
                                                 const vec3 &motion)
{
    // 1. Check the actual position
    if (!GameObjectManager::getInstance().check_boundingbox_collision(bb + origin + motion))
        return motion;
    
    
    // 2. Check the x and z components of the motion
    bool x_motion_ok = false;
    vec3 x_motion = vec3(motion.x, 0.0, 0.0);
    if (!GameObjectManager::getInstance().check_boundingbox_collision(bb + origin + x_motion))
        x_motion_ok = true;
    
    bool z_motion_ok = false;
    vec3 z_motion = vec3(0.0, 0.0, motion.z);
    if (!GameObjectManager::getInstance().check_boundingbox_collision(bb + origin + z_motion))
        z_motion_ok = true;
    
    
    // 3. Get to know the best approximation of x_motion and z_motion
    double x_high_bound = 1.0;
    double x_low_bound = 0.0;
    double z_high_bound = 1.0;
    double z_low_bound = 0.0;
    double precision = 0.01;
    
    if ( !x_motion_ok ) {
        while (x_high_bound - x_low_bound > precision) {
            double middle = ( x_high_bound + x_low_bound ) / 2.0;
            if (GameObjectManager::getInstance().check_boundingbox_collision(bb + origin + middle * x_motion))
                x_high_bound = middle;
            else
                x_low_bound = middle;
        }
    } else {
        x_low_bound = x_high_bound;
    }
    
    if ( !z_motion_ok ) {
        while (z_high_bound - z_low_bound > precision) {
            double middle = ( z_high_bound + z_low_bound ) / 2.0;
            if (GameObjectManager::getInstance().check_boundingbox_collision(bb + origin + middle * z_motion))
                z_high_bound = middle;
            else
                z_low_bound = middle;
        }
    } else {
        z_low_bound = z_high_bound;
    }
    
    /*
    if (GameObjectManager::getInstance().check_boundingbox_collision(bb +
                                                                     origin +
                                                                     x_low_bound * x_motion +
                                                                     z_low_bound * z_motion))
        std::cerr << "COLLISIONG DETECTION ERROR: Algorithm failed!\n";
     */
    
    return x_low_bound * x_motion + z_low_bound * z_motion;
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
    glutTimerFunc(1000/FPS, _update, 1000/FPS);
    
    LightManager::getInstance().update(timeStep);
    InputManager::getInstance().update(timeStep);
    GameObjectManager::getInstance().update(timeStep);
	CameraManager::getInstance().update(timeStep);

    glutPostRedisplay();
}



//
//
//
//

#ifndef SIGMAGAMEENGINE_H
#define SIGMAGAMEENGINE_H

#ifdef __APPLE__
    #include <OpenGL/gl3.h>
    #include "MicroGlut.h"
#endif

#include <SDL/SDL.h>

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
#include "InputManager.h"

#include "GameObjectFactory.h"
#include "GameObject.h"

class SigmaGameEngine
{
public:
    static SigmaGameEngine& getInstance();
    ~SigmaGameEngine();
    
    void initialize(int argc,
                    char *argv[],
                    std::string vertShaderFileName,
                    std::string fragShaderFileName,
                    int windowWidth,
                    int windowHeight,
                    std::string windowName);
    void run();
    void quit();
    
    vec3 check_collision_along_line(const BoundingBox & bb,
                                    const vec3 &origin,
                                    const vec3 &motion);
    
    GLuint getShaderProgramID() { return shaderProgramID_; }
    
    friend void _display();
    friend void _update(int);
    
private:
    SigmaGameEngine();
    SigmaGameEngine(const SigmaGameEngine&);
    SigmaGameEngine& operator=(const SigmaGameEngine&);
    
    GLuint shaderProgramID_;
    
    void display();
    void update(int timeStep);
    
};


#endif
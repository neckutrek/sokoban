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
    
    GLuint getShaderProgramID() { return shaderProgramID_; }
    
    friend void _display();
    friend void _update(int);
    
    // Link the friendship from InputManager onto the global callback
    // functions that picks up user input
    friend void _setKeyUp(unsigned char, int, int);
    friend void _setKeyDown(unsigned char, int, int);
    friend void _updateMouse(int, int, int, int);
    friend void _updateMouse(int, int);
    
private:
    SigmaGameEngine();
    SigmaGameEngine(const SigmaGameEngine&);
    SigmaGameEngine& operator=(const SigmaGameEngine&);
    
    GLuint shaderProgramID_;
    
    void display();
    void update(int timeStep);
    
};


#endif
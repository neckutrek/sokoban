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

//#include "GO_Wall.h"

class SigmaGameEngine
{
public:
    static SigmaGameEngine& getInstance()
    {
        static SigmaGameEngine instance;
        return instance;
    }
    ~SigmaGameEngine() {}
    
    void initialize(int argc,
                    char *argv[],
                    std::string vertShaderFileName,
                    std::string fragShaderFileName,
                    int windowWidth,
                    int windowHeight,
                    std::string windowName);
    void run();
    
    GLuint getShaderProgramID() { return shaderProgramID_; }
    
    friend void _display();
    friend void _update(int);
    
private:
    SigmaGameEngine();
    
    GLuint shaderProgramID_;
    
    void display();
    void update(int timeStep);
    
};


#endif
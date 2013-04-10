//
//  Renderable.h
//  OpenGLGLUTApp
//
//  Created by Marcus Johansson on 4/10/13.
//
//

#ifndef __OpenGLGLUTApp__Renderable__
#define __OpenGLGLUTApp__Renderable__

#include <string>

#ifdef __APPLE__
    #include <OpenGL/gl3.h>
    #include "MicroGlut.h"
#endif

//#include "GL_utilities.h"
#include "VectorUtils3.h"
#include "loadobj.h"
//#include "LoadTGA2.h"

class Renderable {
public:
    Renderable() : _is_model_loaded(false) {};
    
    int loadModel(std::string model_filename)
    virtual int render(GLuint program_reference_id);
    
protected:
    virtual mat4 getModelTransformation() = 0;
    
private:
    Model* _model;
    bool _is_model_loaded;
    
};

#endif /* defined(__OpenGLGLUTApp__Renderable__) */
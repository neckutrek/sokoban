//
//  GameObject.h
//  OpenGLGLUTApp
//
//  Created by Marcus Johansson on 4/10/13.
//
//

#ifndef __OpenGLGLUTApp__GameObject__
#define __OpenGLGLUTApp__GameObject__

#include <string>
#include "Renderable.h"
#include "Body.h"

class GameObject : virtual public Renderable, virtual public Body {
public:
    GameObject() = default;
    ~GameObject() = default;
    
    int loadModel(std::string model_filename);
    
protected:
    virtual mat4 getModelTransformationMatrix();
    
private:
    
    
};

#endif /* defined(__OpenGLGLUTApp__GameObject__) */

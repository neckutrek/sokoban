//
//  Light.h
//  OpenGLGLUTApp
//
//  Created by Marcus Johansson on 4/16/13.
//
//

#ifndef __OpenGLGLUTApp__Light__
#define __OpenGLGLUTApp__Light__

#include <iostream>

#include "GameComponent.h"
#include "VectorUtils3Addons.h"

/*
 *  An interface for 
 */
class Light : public GameComponent
{
public:
    Light();
    virtual ~Light();
    
    virtual vec3 getPosition() const = 0;
    virtual vec4 getLightColor() const = 0;
    virtual float getLuxLevel() const = 0;
    
    bool isDirectional = false;
};

#endif /* defined(__OpenGLGLUTApp__Light__) */

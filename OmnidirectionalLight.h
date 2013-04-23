//
//  OmnidirectionalLight.h
//  OpenGLGLUTApp
//
//  Created by Marcus Johansson on 4/16/13.
//
//

#ifndef __OpenGLGLUTApp__OmnidirectionalLight__
#define __OpenGLGLUTApp__OmnidirectionalLight__

#include <iostream>

#include "Light.h"
#include "Particle.h"

class OmnidirectionalLight : virtual public Light, virtual public Particle
{
public:
    OmnidirectionalLight(vec3 position = vec3(0.0, 0.0, 0.0),
                         vec4 light_color = vec4(1.0, 1.0, 1.0, 1.0),
                         float lux_level = 1.0);
    
    virtual ~OmnidirectionalLight() {}
    
    virtual vec3 getPosition() const;
    
    virtual vec4 getLightColor() const;
    virtual float getLuxLevel() const;
    
protected:
    vec4 _light_color;
    float _lux_level;
    
    mat4 getModelMatrix() const; // hide this Particle-function
    
};

#endif /* defined(__OpenGLGLUTApp__OmnidirectionalLight__) */

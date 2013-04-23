//
//  OmnidirectionalLight.cpp
//  OpenGLGLUTApp
//
//  Created by Marcus Johansson on 4/16/13.
//
//

#include "OmnidirectionalLight.h"

OmnidirectionalLight::OmnidirectionalLight(vec3 position = vec3(0.0, 0.0, 0.0),
                                           vec4 light_color = vec4(1.0, 1.0, 1.0, 1.0),
                                           float lux_level = 1.0)
    : Particle(position.x, position.y, position.z),
        _light_color(light_color),
        _lux_level(lux_level)
{}

virtual vec3 getPosition() const
{
    return Particle::getPosition();
}

virtual vec4 OmnidirectionalLight::getLightColor() const
{
    return _light_color;
}

virtual float OmnidirectionalLight::getLuxLevel() const
{
    return _lux_level;
}

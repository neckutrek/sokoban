//
//  LightContainer.cpp
//  OpenGLGLUTApp
//
//  Created by Marcus Johansson on 4/22/13.
//
//

#include "LightContainer.h"

void LightContainer::addLight(vec3 position, vec3 color, float lux_level)
{
    if (_light_counter < MAX_LIGHT_SOURCES) {
        _light_sources_position_array[_light_counter] = position;
        _light_sources_velocity_array[_light_counter] = vec3(0.0, 0.0, 0.0);
        _light_sources_acceleration_array[_light_counter] = vec3(0.0, 0.0, 0.0);
        
        _light_sources_color_array[_light_counter] = color;
        
        _light_sources_lux_array[_light_counter] = lux_level;
        
        _light_counter++;
    }
}

int LightContainer::update_function(unsigned int time)
{
    return 0;
}

void LightContainer::setLightPosition(int light_index, vec3 position)
{
    
}

void LightContainer::setLightVelocity(int light_index, vec3 velocity)
{
    
}

void LightContainer::setLightAcceleration(int light_index, vec3 acceleration)
{
    
}

void LightContainer::setLightColor(int light_index, vec3 color)
{
    
}

void LightContainer::addLightColor(int light_index, vec3 color)
{
    
}

void LightContainer::setLightLuxLevel(int light_index, float lux_level)
{
    
}

vec3 LightContainer::getLightPosition(int light_index)
{
    return vec3();
}

vec3 LightContainer::getLightVelocity(int light_index)
{
    return vec3();
}

vec3 LightContainer::getLightAcceleration(int light_index)
{
    return vec3();
}

vec3 LightContainer::getLightColor(int light_index)
{
    return vec3();
}

float LightContainer::getLightLuxLevel(int light_index)
{
    return 0.0;
}

unsigned int LightContainer::getLightCounter()
{
    return _light_counter;
}

GLfloat* LightContainer::getLightSourcesPositionArray()
{
    if (_light_counter <= 0) return 0;
    return &_light_sources_position_array[0].x;
}

GLfloat* LightContainer::getLightSourcesColorArray()
{
    if (_light_counter <= 0) return 0;
    return &_light_sources_color_array[0].x;
}

GLfloat* LightContainer::getLightSourcesLuxArray()
{
    if (_light_counter <= 0) return 0;
    return &_light_sources_lux_array[0];
}

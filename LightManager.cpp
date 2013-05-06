//
//  LightContainer.cpp
//  OpenGLGLUTApp
//
//  Created by Marcus Johansson on 4/22/13.
//
//

#include "LightManager.h"

LightManager& LightManager::getInstance()
{
    static LightManager instance;
    return instance;
}

void LightManager::addLight(vec3 position, vec3 color, float lux_level)
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

int LightManager::update_function(unsigned int time)
{
    return 0;
}

void LightManager::setLightPosition(int light_index, vec3 position)
{
    
}

void LightManager::setLightVelocity(int light_index, vec3 velocity)
{
    
}

void LightManager::setLightAcceleration(int light_index, vec3 acceleration)
{
    
}

void LightManager::setLightColor(int light_index, vec3 color)
{
    
}

void LightManager::addLightColor(int light_index, vec3 color)
{
    
}

void LightManager::setLightLuxLevel(int light_index, float lux_level)
{
    
}

vec3 LightManager::getLightPosition(int light_index)
{
    return vec3();
}

vec3 LightManager::getLightVelocity(int light_index)
{
    return vec3();
}

vec3 LightManager::getLightAcceleration(int light_index)
{
    return vec3();
}

vec3 LightManager::getLightColor(int light_index)
{
    return vec3();
}

float LightManager::getLightLuxLevel(int light_index)
{
    return 0.0;
}

unsigned int LightManager::getLightCounter()
{
    return _light_counter;
}

GLfloat* LightManager::getLightSourcesPositionArray()
{
    if (_light_counter <= 0) return 0;
    return &_light_sources_position_array[0].x;
}

GLfloat* LightManager::getLightSourcesColorArray()
{
    if (_light_counter <= 0) return 0;
    return &_light_sources_color_array[0].x;
}

GLfloat* LightManager::getLightSourcesLuxArray()
{
    if (_light_counter <= 0) return 0;
    return &_light_sources_lux_array[0];
}

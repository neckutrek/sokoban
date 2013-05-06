//
//  LightContainer.h
//  OpenGLGLUTApp
//
//  Created by Marcus Johansson on 4/22/13.
//
//

#ifndef __OpenGLGLUTApp__LightContainer__
#define __OpenGLGLUTApp__LightContainer__

#include "GameComponent.h"
#include "VectorUtils3Addons.h"

const unsigned int MAX_LIGHT_SOURCES = 8;

class LightManager
{
public:
    static LightManager& getInstance();
    
    ~LightManager() {}
    
    // from GameComponent
    virtual int update_function(unsigned int time);
    
    void addLight(vec3 position, vec3 color, float lux_level);
    
    void setLightPosition(int light_index, vec3 position);
    void setLightVelocity(int light_index, vec3 velocity);
    void setLightAcceleration(int light_index, vec3 acceleration);
    void setLightColor(int light_index, vec3 color);
    void addLightColor(int light_index, vec3 color);
    void setLightLuxLevel(int light_index, float lux_level);
    
    vec3 getLightPosition(int light_index);
    vec3 getLightVelocity(int light_index);
    vec3 getLightAcceleration(int light_index);
    vec3 getLightColor(int light_index);
    float getLightLuxLevel(int light_index);
    unsigned int getLightCounter();
    
    //FOR RENDERING
    GLfloat* getLightSourcesPositionArray();
    GLfloat* getLightSourcesColorArray();
    GLfloat* getLightSourcesLuxArray();
    
    
private:
    LightManager()
    : _light_counter(0)
    {}
    
    unsigned int _light_counter;
    
    vec3 _light_sources_position_array[MAX_LIGHT_SOURCES];
    vec3 _light_sources_velocity_array[MAX_LIGHT_SOURCES];
    vec3 _light_sources_acceleration_array[MAX_LIGHT_SOURCES];
    
    vec3 _light_sources_color_array[MAX_LIGHT_SOURCES];
    float _light_sources_lux_array[MAX_LIGHT_SOURCES];
     
    
};

#endif /* defined(__OpenGLGLUTApp__LightContainer__) */

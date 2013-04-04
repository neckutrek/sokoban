//
//  Particle.h
//  OpenGLGLUTApp
//
//  Created by Marcus Johansson on 4/4/13.
//
//

#ifndef __OpenGLGLUTApp__Particle__
#define __OpenGLGLUTApp__Particle__

#include "VectorUtils3.h"
#include "GameComponent.h"

class Particle : virtual public GameComponent {
public:
    //Constructor
    //Destructor
    
    void setPosition(GLfloat x, GLfloat y, GLfloat z);
    void setVelocity(GLfloat x, GLfloat y, GLfloat z);
    void setAcceleration(GLfloat x, GLfloat y, GLfloat z);
	
	vec3 getPosition();
	vec3 getVelocity();
	vec3 getAcceleration();
    
    int update_function(unsigned int time);
    
protected:
    
    
private:
    vec3 _position;
    vec3 _velocity;
    vec3 _acceleration;
    
};

#endif /* defined(__OpenGLGLUTApp__Particle__) */

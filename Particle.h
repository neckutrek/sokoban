//
//  Particle.h
//  OpenGLGLUTApp
//
//  Created by Marcus Johansson on 4/4/13.
//
//

#ifndef __OpenGLGLUTApp__Particle__
#define __OpenGLGLUTApp__Particle__

#include <iostream>
#include "GameComponent.h"
#include "VectorUtils3.h"
#include "VectorUtils3Addons.h"

class Particle : virtual public GameComponent {
public:
    Particle(GLfloat x=0, GLfloat y=0, GLfloat z=0);
	~Particle() {}
	
    void setPosition(GLfloat x, GLfloat y, GLfloat z);
    void setVelocity(GLfloat dx, GLfloat dy, GLfloat dz);
    void setAcceleration(GLfloat ddx, GLfloat ddy, GLfloat ddz);
	
	vec3 getPosition() const;
	vec3 getVelocity() const;
	vec3 getAcceleration() const;
    mat4 getModelMatrix() const;
    
    virtual int update_function(unsigned int time);
    
    friend std::ostream& operator<<(std::ostream& os, const Particle& p);
    
protected:
    
    
private:
    mat4 _translation;
    vec3 _velocity;
    vec3 _acceleration;
};

#endif /* defined(__OpenGLGLUTApp__Particle__) */

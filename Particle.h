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
	
	mat4 generateResultMatrix();
    
    void setPosition(GLfloat x, GLfloat y, GLfloat z);
    void setVelocity(GLfloat dx, GLfloat dy, GLfloat dz);
    void setAcceleration(GLfloat ddx, GLfloat ddy, GLfloat ddz);
	
	vec3 getPosition();
	vec3 getVelocity();
	vec3 getAcceleration();
    
    int update_function(unsigned int time);
    
protected:
    
    
private:
	mat4 resultMatrix;
    mat4 _translation;
    vec3 _velocity;
    vec3 _acceleration;
};

#endif /* defined(__OpenGLGLUTApp__Particle__) */

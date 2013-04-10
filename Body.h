//
//  Body.h
//  OpenGLGLUTApp
//
//  Created by Marcus Johansson on 4/4/13.
//
//

#ifndef __OpenGLGLUTApp__Body__
#define __OpenGLGLUTApp__Body__

#include "Particle.h"

class Body : public Particle {
public:
	//Constructor
	//Destructor
	
	void setRot(GLfloat x, GLfloat y, GLfloat z, GLfloat a);
	void setRotVelocity(GLfloat dx, GLfloat dy, GLfloat dz, GLfloat da);
	void setRotAcceleration(GLfloat ddx, GLfloat ddy, GLfloat ddz, GLfloat dda);
	
	mat4 getRot();
	mat4 getRotVelocity();
	mat4 getRotAcceleration();
	
	int update_function(unsigned int time);
	
protected:
	
private:
    mat4 rotMatrix;
    mat4 rotVelMatrix;
    mat4 rotAccMatrix;
};

#endif /* defined(__OpenGLGLUTApp__Body__) */

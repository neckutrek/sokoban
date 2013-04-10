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
	Body(GLfloat x=0, GLfloat y=0, GLfloat z=0);
	
	//Destructor
	~Body() = default;
	
	mat4 getModelMatrix();
	
	void setRot(GLfloat x, GLfloat y, GLfloat z, GLfloat a);
	void setRotVelocity(GLfloat x, GLfloat y, GLfloat z, GLfloat da);
	void setRotAcceleration(GLfloat x, GLfloat y, GLfloat z, GLfloat dda);
	void setScaling(GLfloat x, GLfloat y, GLfloat z);
	
	mat4 getRot();
	mat4 getRotVelocity();
	mat4 getRotAcceleration();
	mat4 getScaling();
	
	int update_function(unsigned int time);
	
protected:
	
private:
    mat4 _rotation;
    mat4 _rotationVelocity;
    mat4 _rotationAcceleration;
	mat4 _scaling;
};

#endif /* defined(__OpenGLGLUTApp__Body__) */

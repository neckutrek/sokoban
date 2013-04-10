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
	Body(GLfloat x=0, GLfloat y=0, GLfloat z=0);
	~Body() = default;
	
	void setRot(GLfloat x, GLfloat y, GLfloat z, GLfloat a);
	void setRotVelocity(GLfloat x, GLfloat y, GLfloat z, GLfloat da);
	void setRotAcceleration(GLfloat x, GLfloat y, GLfloat z, GLfloat dda);
	void setScaling(GLfloat x, GLfloat y, GLfloat z);
	
	mat4 getRot() const;
	mat4 getRotVelocity() const;
	mat4 getRotAcceleration() const;
	mat4 getScaling() const;
    mat4 getModelMatrix() const;
	
	virtual int update_function(unsigned int time);
	
protected:
	
private:
    mat4 _rotation;
    mat4 _rotationVelocity;
    mat4 _rotationAcceleration;
	mat4 _scaling;
};

#endif /* defined(__OpenGLGLUTApp__Body__) */

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
	virtual ~Body() {}
	
	virtual void setRot(GLfloat x, GLfloat y, GLfloat z, GLfloat a);
	virtual void setRotVelocity(GLfloat x, GLfloat y, GLfloat z, GLfloat da);
	virtual void setRotAcceleration(GLfloat x, GLfloat y, GLfloat z, GLfloat dda);
	virtual void setScaling(GLfloat x, GLfloat y, GLfloat z);
	virtual void setScaling(vec3 v);
	
	mat4 getRot() const;
	mat4 getRotVelocity() const;
	mat4 getRotAcceleration() const;
	mat4 getScaling() const;
	
	virtual int update_function(unsigned int time);
	
protected:
    mat4 getModelMatrix() const;
	
private:
    mat4 _rotation;
    mat4 _rotationVelocity;
    mat4 _rotationAcceleration;
	mat4 _scaling;
};

#endif /* defined(__OpenGLGLUTApp__Body__) */

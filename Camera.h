//
//  Camera.h
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-04-10.
//
// hej

#ifndef __OpenGLGLUTApp__Camera__
#define __OpenGLGLUTApp__Camera__

#include <iostream>
#include "Particle.h"

class Camera : public Particle
{
public:
	Camera(GLfloat x=0, GLfloat y=0, GLfloat z=0);
	
	~Camera() {}
	
	void setViewDirection(GLfloat x, GLfloat y, GLfloat z);
	void setViewLocation(GLfloat x, GLfloat y, GLfloat z);
	void setViewLocation(vec3 v);
	void setViewLocation(Particle* p);
	void setUpDirection(GLfloat x, GLfloat y, GLfloat z);
	
	vec3 getUpDirection() const;
	vec3 getViewDirection() const;
	
	virtual void updateKeyboard(int *keyboardMap) {}
	
	mat4 getCameraMatrix() const;
	
protected:
	
private:
	vec3 _upDirection;
	vec3 _viewDirection;
};

#endif /* defined(__OpenGLGLUTApp__Camera__) */

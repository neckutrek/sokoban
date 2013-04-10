//
//  Camera.h
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-04-10.
//
//

#ifndef __OpenGLGLUTApp__Camera__
#define __OpenGLGLUTApp__Camera__

#include <iostream>
#include "Body.h"

class Camera : protected Body
{
public:
	Camera(GLfloat x=0, GLfloat y=0, GLfloat z=0);
	
	~Camera() = default;
	
	void setViewDirection(GLfloat theta, GLfloat phi);
	void setViewDirection(GLfloat x, GLfloat y, GLfloat z);
	void setUpDirection(GLfloat x, GLfloat y, GLfloat z);
	
	vec3 getUpDirection() const;
	vec3 getViewDirection() const;
	
	mat4 getCameraMatrix() const;
	
protected:
	
private:
	vec3 _upDirection;
	vec3 _viewDirection;
};

#endif /* defined(__OpenGLGLUTApp__Camera__) */

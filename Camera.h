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

class Camera : public Body
{
	Camera(GLfloat x=0, GLfloat y=0, GLfloat z=0);
	
	void setViewLocation(GLfloat x, GLfloat y, GLfloat z);
	void setViewDirection(GLfloat theta, GLfloat phi);
	void setViewDirection(GLfloat x, GLfloat y, GLfloat z);
	
	mat4 getCameraMatrix;
};

#endif /* defined(__OpenGLGLUTApp__Camera__) */

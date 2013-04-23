//
//  FPSCamera.h
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-04-16.
//
// hej

#ifndef __OpenGLGLUTApp__FPSCamera__
#define __OpenGLGLUTApp__FPSCamera__

#include <iostream>
#include "Camera.h"

class DebugCamera : public Camera
{
public:
	DebugCamera(GLfloat x=0, GLfloat y=0, GLfloat z=0);
	
	~DebugCamera() {}
	
	void setRelPosition(GLfloat dx, GLfloat dy, GLfloat dz);
	void setViewDirection(GLfloat theta, GLfloat phi);
	void setRelViewDirection(GLfloat dtheta, GLfloat dphi);
	
	virtual void updateKeyboard(int *keyboardMap);
	
protected:
	
private:
	GLfloat _theta;
	GLfloat _phi;
};

#endif /* defined(__OpenGLGLUTApp__FPSCamera__) */

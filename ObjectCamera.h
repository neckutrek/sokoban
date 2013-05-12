//
//  ObjectCamera.h
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-04-18.
//
// hej

#ifndef __OpenGLGLUTApp__ObjectCamera__
#define __OpenGLGLUTApp__ObjectCamera__

#include <iostream>
#include "Camera.h"
#include "GO_Player.h"

class ObjectCamera : public Camera
{
public:
	ObjectCamera(Particle* object);
	
	void setViewDirection(GLfloat theta, GLfloat phi);
	void setRelViewDirection(GLfloat dtheta, GLfloat dphi);
	void setDistance(GLfloat d);
	void setRelDistance(GLfloat dd);
	void setMinDistance(GLfloat minDistance);
	void setMaxDistance(GLfloat maxDistance);
	void setMinTheta(GLfloat minTheta);
	void setMaxTheta(GLfloat maxTheta);
	
    virtual void updateKeyboard(unsigned char keyboardMap[256]);
    
    virtual int update_function(unsigned int time);
	
protected:
	
private:
	Particle* _object;
	
	GLfloat _distance;
	GLfloat _theta;
	GLfloat _phi;
	GLfloat _minDistance;
	GLfloat _maxDistance;
	GLfloat _minTheta;
	GLfloat _maxTheta;
	vec3 _displacement;
};

#endif /* defined(__OpenGLGLUTApp__ObjectCamera__) */

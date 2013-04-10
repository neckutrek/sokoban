//
//  Body.cpp
//  OpenGLGLUTApp
//
//  Created by Marcus Johansson on 4/4/13.
//
//

#include "Body.h"

void Body::setRot(GLfloat x, GLfloaty, GLfloat z, GLfloat a)
{
	rotMatrix = ArbRotate(vec3(x, y, z), a);
}

void Body::setRotVelocity(GLfloat dx, GLfloat dy, GLfloat dz, GLfloat da)
{
	rotVelMatrix = ArbRotate(vec3(x, y, z), a);
}

void Body::setRotAcceleration(GLfloat dx, GLfloat dy, GLfloat dz, GLfloat da)
{
	rotAccMatrix = ArbRotate(vec3(x, y, z), a);
}

void Body::setScaling(GLfloat x, GLfloat y, GLfloat z)
{
	_scaling = S(x, y, z);
}

mat4 Body::getRot()
{
	return _rotation;
}

mat4 Body::getRotVelocity()
{
	return _rotationVelocity;
}

mat4 Body::getRotAcceleration()
{
	return _rotationAcceleration;
}

mat4 Body::generateResultMatrix()
{
	return Particle::generateResultMatrix() * _rotation;
}

int Body::update_function(unsigned int time)
{
	Particle::update_function(time);
	_rotationVelocity *= _rotationAcceleration * time;
	_rotation *= _rotationVelocity * time;
	
	return 0;
}
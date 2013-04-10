//
//  Body.cpp
//  OpenGLGLUTApp
//
//  Created by Marcus Johansson on 4/4/13.
//
//

#include "Body.h"

Body::Body(GLfloat x, GLfloat y, GLfloat z)
: Particle(x, y, z), _rotation(IdentityMatrix()), _rotationVelocity(IdentityMatrix()), _rotationAcceleration(IdentityMatrix()), _scaling(IdentityMatrix())
{}

void Body::setRot(GLfloat x, GLfloat y, GLfloat z, GLfloat a)
{
	_rotation = ArbRotate(vec3(x, y, z), a);
}

void Body::setRotVelocity(GLfloat x, GLfloat y, GLfloat z, GLfloat da)
{
	_rotationVelocity = ArbRotate(vec3(x, y, z), da);
}

void Body::setRotAcceleration(GLfloat x, GLfloat y, GLfloat z, GLfloat dda)
{
	_rotationAcceleration = ArbRotate(vec3(x, y, z), dda);
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

mat4 Body::getModelMatrix()
{
	return Particle::getModelMatrix() * _rotation;
}

int Body::update_function(unsigned int time)
{
	Particle::update_function(time);
	_rotationVelocity *= _rotationAcceleration * time;
	_rotation *= _rotationVelocity * time;
	
	return 0;
}
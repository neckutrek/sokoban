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
	setScaling(vec3(x, y, z));
}

void Body::setScaling(vec3 v)
{
	_scaling = S(v.x, v.y, v.z);
}

mat4 Body::getRot() const
{
	return _rotation;
}

mat4 Body::getRotVelocity() const
{
	return _rotationVelocity;
}

mat4 Body::getRotAcceleration() const
{
	return _rotationAcceleration;
}

mat4 Body::getModelMatrix() const
{
	return Particle::getModelMatrix() * _rotation * _scaling;
}

int Body::update_function(unsigned int time)
{
	Particle::update_function(time);
	_rotation *= _rotationVelocity;
    _rotationVelocity *= _rotationAcceleration;
	return 0;
}
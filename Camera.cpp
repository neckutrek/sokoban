//
//  Camera.cpp
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-04-10.
//
// hej

#include "Camera.h"
#include <cmath>

Camera::Camera(GLfloat x, GLfloat y, GLfloat z)
: Particle(x, y, z), _upDirection(0,1,0), _viewDirection(0,0,-1)
{}

void Camera::setViewDirection(GLfloat x, GLfloat y, GLfloat z)
{
	_viewDirection.x = x;
	_viewDirection.y = y;
	_viewDirection.z = z;
}

void Camera::setUpDirection(GLfloat x, GLfloat y, GLfloat z)
{
	_upDirection.x = x;
	_upDirection.y = y;
	_upDirection.z = z;
}

void Camera::setViewLocation(GLfloat x, GLfloat y, GLfloat z)
{
	setViewLocation(vec3(x, y, z));
}

void Camera::setViewLocation(vec3 v)
{
	_viewDirection = v - getPosition();
}

void Camera::setViewLocation(Particle* p)
{
	setViewLocation(p->getPosition());
}

vec3 Camera::getViewDirection() const
{
	return _viewDirection;
}

vec3 Camera::getUpDirection() const
{
	return _upDirection;
}

mat4 Camera::getCameraMatrix() const
{
	return lookAtv(getPosition(), getPosition() + _viewDirection, _upDirection);
}
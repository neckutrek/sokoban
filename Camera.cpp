//
//  Camera.cpp
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-04-10.
//
//

#include "Camera.h"
#include <cmath>

Camera::Camera(GLfloat x, GLfloat y, GLfloat z)
: Body(x, y, z), _upDirection(0,1,0), _viewDirection(0,0,-1)
{}

void Camera::setViewDirection(GLfloat theta, GLfloat phi)
{
	theta = (theta < 0 ? 0 : (theta > M_PI ? M_PI : theta));
	phi = fmod(phi,2*M_PI);
	if (phi < 0)
		phi += 2*M_PI;
	_viewDirection.x = -sin(theta)*sin(phi);
	_viewDirection.y = cos(theta);
	_viewDirection.z = sin(theta)*cos(phi);
}

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
	return lookAtv(getPosition(), _viewDirection, _upDirection);
}
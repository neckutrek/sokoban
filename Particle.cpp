//
//  Particle.cpp
//  OpenGLGLUTApp
//
//  Created by Marcus Johansson on 4/4/13.
//
//

#include "Particle.h"

void Particle::setPosition(GLfloat x, GLfloat y, GLfloat z)
{
	_translation = T(x, y, z);
}

void Particle::setVelocity(GLfloat dx, GLfloat dy, GLfloat dz)
{
	_velocity.x = dx;
	_velocity.y = dy;
	_velocity.z = dz;
}

void Particle::setAcceleration(GLfloat ddx, GLfloat ddy, GLfloat ddz)
{
	_acceleration.x = ddx;
	_acceleration.y = ddy;
	_acceleration.z = ddz;
}

vec3 Particle::getPosition()
{
	return vec3(_translation.m[0], _translation.m[5], _translation.m[10]);
}

vec3 Particle::getVelocity()
{
	return _velocity;
}

vec3 Particle::getAcceleration()
{
	return _acceleration;
}

mat4 Particle::generateResultMatrix()
{
	return _translation;
}

int Particle::update_function(unsigned int time)
{
	_velocity += _acceleration * time;
	_translation *= T(_velocity.x, _velocity.y, _velocity.z);
	return 0;
}

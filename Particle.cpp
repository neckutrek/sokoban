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
	_position.x = x;
	_position.y = y;
	_position.z = z;
}

void Particle::setVelocity(GLfloat x, GLfloat y, GLfloat z)
{
	_velocity.x = x;
	_velocity.y = y;
	_velocity.z = z;
}

void Particle::setAcceleration(GLfloat x, GLfloat y, GLfloat z)
{
	_acceleration.x = x;
	_acceleration.y = y;
	_acceleration.z = z;
}

int Particle::update_function(unsigned int time)
{
	_velocity += _acceleration;
	_position += _velocity;
	
	return 0;
}

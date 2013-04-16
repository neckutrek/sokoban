//
//  Particle.cpp
//  OpenGLGLUTApp
//
//  Created by Marcus Johansson on 4/4/13.
//
//

#include "Particle.h"

Particle::Particle(GLfloat x, GLfloat y, GLfloat z)
: _velocity(0.0, 0.0, 0.0), _acceleration(0.0, 0.0, 0.0), _translation(T(x, y, z))
{}

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

vec3 Particle::getPosition() const
{
	return vec3(_translation.m[3], _translation.m[7], _translation.m[11]);
}

vec3 Particle::getVelocity() const
{
	return _velocity;
}

vec3 Particle::getAcceleration() const
{
	return _acceleration;
}

mat4 Particle::getModelMatrix() const
{
	return _translation;
}

int Particle::update_function(unsigned int time)
{
	_translation *= T(_velocity.x, _velocity.y, _velocity.z);
    _velocity += _acceleration;
	return 0;
}
/*
std::ostream& operator<<(std::ostream& os, const Particle& p)
{
    os << "T: " << p.getPosition()
    << " V: " << p._velocity
    << " A: " << p._acceleration;
    return os;
}
 */

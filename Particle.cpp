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
	setPosition(vec3(x, y, z));
}

void Particle::setPosition(vec3 v)
{
	_translation = T(v.x, v.y, v.z);
}

void Particle::setVelocity(GLfloat dx, GLfloat dy, GLfloat dz)
{
	setVelocity(vec3(dx, dy, dz));
}

void Particle::setVelocity(vec3 v)
{
	_velocity = v;
}

void Particle::setAcceleration(GLfloat ddx, GLfloat ddy, GLfloat ddz)
{
	setAcceleration(vec3(ddx, ddy, ddz));
}

void Particle::setAcceleration(vec3 v)
{
	_acceleration = v;
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

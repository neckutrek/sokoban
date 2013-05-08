//
//  ObjectCamera.cpp
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-04-18.
//
// hej

#include "ObjectCamera.h"

ObjectCamera::ObjectCamera(Particle* object) : Camera(), _theta(M_PI/4), _phi(M_PI), _object(object), _distance(3),
_minDistance(1), _maxDistance(10), _minTheta(0.00001), _maxTheta(M_PI/2)
{}

void ObjectCamera::setViewDirection(GLfloat theta, GLfloat phi)
{
	_theta = clamp(theta, _minTheta, _maxTheta);
	phi = fmod(phi,2*M_PI);
	if (phi < 0)
		phi += 2*M_PI;
	_phi = phi;
}

void ObjectCamera::setRelViewDirection(GLfloat dtheta, GLfloat dphi)
{
	setViewDirection(_theta + dtheta, _phi + dphi);
}

void ObjectCamera::setDistance(GLfloat d)
{
	_distance = clamp(d, _minDistance, _maxDistance);
}

void ObjectCamera::setRelDistance(GLfloat dd)
{
	setDistance(_distance + dd);
}

void ObjectCamera::setMinDistance(GLfloat minDistance)
{
	_minDistance = (minDistance < 0 ? 0 : minDistance);
	if(_minDistance > _maxDistance)
		_maxDistance = _minDistance;
	if(_distance < _minDistance)
		_distance = _minDistance;
}

void ObjectCamera::setMaxDistance(GLfloat maxDistance)
{
	_maxDistance = maxDistance;
	if(_maxDistance < _minDistance)
		_minDistance = _maxDistance;
	if(_distance > _maxDistance)
		_distance = _maxDistance;
}

void ObjectCamera::setMinTheta(GLfloat minTheta)
{
	_minTheta = clamp(minTheta, 0, M_PI);
	if(_minTheta > _maxTheta)
		_maxTheta = _minTheta;
	if(_theta < _minTheta)
		_theta = _minTheta;
}

void ObjectCamera::setMaxTheta(GLfloat maxTheta)
{
	_maxTheta = clamp(maxTheta, 0, M_PI);
	if(_maxTheta < _minTheta)
		_minTheta = _maxTheta;
	if(_theta > _maxTheta)
		_theta = _maxTheta;
}

void ObjectCamera::updateKeyboard(unsigned char keyboardMap[256])
{
	if (keyboardMap['W'] == 1 || keyboardMap['w'] == 1) {
		setRelViewDirection(-0.05, 0);
	} else if (keyboardMap['S'] == 1 || keyboardMap['s'] == 1) {
		setRelViewDirection(0.05, 0);
	}
	
	if (keyboardMap['A'] == 1 || keyboardMap['a'] == 1) {
		setRelViewDirection(0, 0.05);
	} else if (keyboardMap['D'] == 1 || keyboardMap['d'] == 1) {
		setRelViewDirection(0, -0.05);
	}
	
	if (keyboardMap['I'] == 1 || keyboardMap['i'] == 1) {
		setRelDistance(-0.1);
	} else if (keyboardMap['K'] == 1 || keyboardMap['k'] == 1) {
		setRelDistance(0.1);
	}
}

int ObjectCamera::update_function(unsigned int time)
{
	setPosition(_object->getPosition() +
				_distance * vec3(sin(_theta)*cos(_phi), cos(_theta), sin(_theta)*sin(_phi)));
	setViewLocation(_object);
	return 0;
}
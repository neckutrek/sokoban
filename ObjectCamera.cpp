//
//  ObjectCamera.cpp
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-04-18.
//
// hej

#include "ObjectCamera.h"

ObjectCamera::ObjectCamera(Particle* object) : Camera(), _theta(M_PI/4), _phi(M_PI/2), _object(object), _distance(3),
_minDistance(1), _maxDistance(10), _minTheta(0.00001), _maxTheta(M_PI/2), _displacement(vec3(0, 1, 0))
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
	
 
 
    //Inte helsnyggt att detta ligger här, men tidspress...
 
    
}

int ObjectCamera::update_function(unsigned int time)
{
    InputManager& im = InputManager::getInstance();
    
    if (im.isKeyDown('<')) setRelDistance(-0.1);
    else if (im.isKeyDown(' ')) setRelDistance(0.1);
	
    setRelViewDirection(-0.008 * im.getMouseSpeedY(),
                        0.008 * im.getMouseSpeedX());

    GO_Player* player = dynamic_cast<GO_Player*>(_object);
    if(player)
    {
        vec3 totalMovement;
        vec3 v = _distance * vec3(sin(_theta)*cos(_phi), 0, sin(_theta)*sin(_phi));
        
        if (im.isKeyDown('w')) totalMovement.z -= 1;
        else if (im.isKeyDown('s')) totalMovement.z += 1;
        
        if (im.isKeyDown('a')) totalMovement.x -= 1;
        else if (im.isKeyDown('d')) totalMovement.x += 1;
        
        if (totalMovement != vec3(0))
        {
            totalMovement = Normalize(totalMovement)/10;
            player->setRelPosToVector(v, totalMovement);
        }
        
        player->setRot(0, 1, 0, -_phi-M_PI/2);
    }
    
    setPosition(_object->getPosition() + _displacement +
				_distance * vec3(sin(_theta)*cos(_phi), cos(_theta), sin(_theta)*sin(_phi)));
	setViewLocation(_object);
    
	return 0;
}


//
//  Player.cpp
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-04-30.
//
//

#include "GO_Player.h"
#include "LightManager.h"

GO_Player::GO_Player(vec3 pos) : GameObject(BoundingBox(0.5))
{
	loadModel("robot.obj");
	addMaterial("robot_c.tga", 1, 50);
	setPosition(pos);
	setRot(0, 1, 0, M_PI);
	_playerBase = new GO_PlayerBase();
	GameObjectManager::getInstance().addObject(_playerBase);
    my_light_index = LightManager::getInstance().addLight(getPosition(), vec3(1, 0.8, 0.6), 1.5);
    _is_affected_by_light = false;
}

std::string GO_Player::getType()
{
	return "player";
}

void GO_Player::setRot(GLfloat x, GLfloat y, GLfloat z, GLfloat a)
{
	_myRot = a;
	Body::setRot(x, y, z, a);
}

void GO_Player::setRelPosToVector(vec3 v, vec3 pos)
{
	v = Normalize(v);
	vec3 xVec = CrossProduct(v, vec3(0,1,0));
	vec3 currPos = getPosition();
	vec3 displacement = vec3(- pos.x*xVec + pos.z*v);
	setPosition(currPos + displacement);
	_playerBase->setPosition(getPosition());
	if (displacement != vec3(0))
		_playerBase->setRot(0, 1, 0, atan2(displacement.x, displacement.z));
}

void GO_Player::push()
{
	mat4 rot = getRot();
	vec3 facing = Normalize(vec3(rot.m[3], rot.m[7], rot.m[11]));
	vec3 point = getPosition() + 0.8*facing;
	std::vector<GameObject* > objects = GameObjectManager::getInstance().getObjectsWithinBox(BoundingBox(0) + point);
	if(objects.size() > 0 && objects.front()->getType() == "block")
	{
		GLfloat clampedRot = _myRot;
		int quadrant = 0;
		while (clampedRot - M_PI/2 >= 0) {
			clampedRot -= M_PI/2;
			quadrant++;
		}
		if(clampedRot>M_PI/12 && clampedRot<M_PI/6)
			break;
		dynamic_cast<GO_Block*>(objects.front())->push(quadrant + (clampedRot>M_PI/6 ? 1 : 0));
	}
}

int GO_Player::update_function(unsigned int time)
{
	_playerBase->setPosition(getPosition());
	Body::update_function(time);
    vec3 pos = getPosition();
    pos.y += 0;
    LightManager::getInstance().setLightPosition(my_light_index, pos);
	return 0;
}

GO_Player::GO_PlayerBase::GO_PlayerBase() : GameObject(BoundingBox(0))
{
	loadModel("treads.obj");
	addMaterial("tracks_c.tga", 1, 50);
    _is_affected_by_light = false;
}

std::string GO_Player::GO_PlayerBase::getType()
{
	return "playerBase";
}
//
//  Player.cpp
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-04-30.
//
//

#include "GO_Player.h"

GO_Player::GO_Player(vec3 pos) : GameObject(BoundingBox(0.5))
{
	loadModel("robot.obj");
	addMaterial("robot_c.tga", 1, 50);
	setPosition(pos);
	_playerBase = new GO_PlayerBase();
	GameObjectManager::getInstance().addObject(_playerBase);
}

std::string GO_Player::getType()
{
	return "player";
}

int GO_Player::update_function(unsigned int time)
{
	_playerBase->setPosition(getPosition());
	Body::update_function(time);
	return 0;
}

GO_Player::GO_PlayerBase::GO_PlayerBase() : GameObject(BoundingBox(0))
{
	loadModel("treads.obj");
	addMaterial("tracks_c.tga", 1, 50);
}

std::string GO_Player::GO_PlayerBase::getType()
{
	return "playerBase";
}
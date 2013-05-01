//
//  Player.cpp
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-04-30.
//
//

#include "Player.h"

Player::Player(vec3 pos) : GameObject(BoundingBox(0.5))
{
	loadModel("bunnyplus.obj");
	setPosition(pos);
}

std::string Player::getType()
{
	return "player";
}
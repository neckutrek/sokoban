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
	loadModel("bunnyplus.obj");
	setPosition(pos);
}

std::string GO_Player::getType()
{
	return "player";
}
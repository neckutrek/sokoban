//
//  Wall.cpp
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-04-28.
//
//

#include "Wall.h"

Wall::Wall(vec3 position) : GameObject(BoundingBox(0.5))
{
	loadModel("bunnyplus.obj");
	setPosition(position);
}

std::string Wall::getType()
{
	return "wall";
}
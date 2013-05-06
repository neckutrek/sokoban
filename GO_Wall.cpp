//
//  Wall.cpp
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-04-28.
//
//

#include "GO_Wall.h"

GO_Wall::GO_Wall(vec3 pos) : GameObject(BoundingBox(0.5))
{
	loadModel("crate.obj");
	setPosition(pos);
	setRotVelocity(0, 1, 0, 0.02);
	setScaling(0.5, 0.5, 0.5);
}

std::string GO_Wall::getType()
{
	return "wall";
}
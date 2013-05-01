//
//  Ground.cpp
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-04-30.
//
//

#include "Ground.h"

Ground::Ground() : GameObject(BoundingBox(0))
{
	loadModel("ground.obj");
}

std::string Ground::getType()
{
	return "ground";
}
//
//  Ground.cpp
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-04-30.
//
//

#include "GO_Ground.h"

GO_Ground::GO_Ground() : GameObject(BoundingBox(0))
{
	loadModel("ground.obj");
}

std::string GO_Ground::getType()
{
	return "ground";
}
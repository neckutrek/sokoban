//
//  Block.cpp
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-05-01.
//
//

#include "GO_Block.h"

GO_Block::GO_Block(vec3 pos) : GameObject(BoundingBox(0.5))
{
	loadModel("crate.obj");
	setPosition(pos);
}

std::string GO_Block::getType()
{
	return "block";
}
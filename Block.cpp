//
//  Block.cpp
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-05-01.
//
//

#include "Block.h"

Block::Block(vec3 pos) : GameObject(BoundingBox(0.5))
{
	loadModel("crate.obj");
	setPosition(pos);
}

std::string Block::getType()
{
	return "block";
}
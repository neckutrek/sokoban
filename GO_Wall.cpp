//
//  Wall.cpp
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-04-28.
//
//

#include "GO_Wall.h"

GO_Wall::GO_Wall(vec3 pos, GLfloat rot, std::string fileName) : GameObject(BoundingBox(0.5))
{
	loadModel(fileName.c_str());
	addMaterial("wall_c.tga", 1, 10);
	setPosition(pos);
	setRot(0, 1, 0, rot);
}

std::string GO_Wall::getType()
{
	return "wall";
}
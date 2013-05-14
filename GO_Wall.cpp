//
//  Wall.cpp
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-04-28.
//
//

#include "GO_Wall.h"

GO_Wall::GO_Wall(vec3 pos, GLfloat rot, std::string modelType) : GameObject(BoundingBox(vec3(-0.5, 0, -0.5), vec3(0.5, 1, 0.5)))
{
	loadModel(("wall"+modelType+"n.obj").c_str());
	addMaterial(("wall"+modelType+"n.tga").c_str(), 1, 1);
	setPosition(pos);
	setRot(0, 1, 0, rot);
}

std::string GO_Wall::getType()
{
	return "wall";
}
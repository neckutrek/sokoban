//
//  GameObjectFactory.cpp
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-04-28.
//
//

#include "GameObjectFactory.h"

GameObjectFactory::GameObjectFactory()
{}

Wall* GameObjectFactory::createWall(vec3 pos)
{
	return new Wall(pos);
}

/*
GameObject* GameObjectFactory::createPlayer(vec3 pos)
{
	
}

GameObject* GameObjectFactory::createBlock(vec3 pos)
{
	
}

GameObject* GameObjectFactory::createPlate(vec3 pos)
{
	
}
*/
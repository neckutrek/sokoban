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

Ground* GameObjectFactory::createGround()
{
	return new Ground();
}

Player* GameObjectFactory::createPlayer(vec3 pos)
{
	Player* player = new Player(pos);
	ObjectCamera* cam = new ObjectCamera(player);
	CameraManager::getInstance().setActiveCamera(cam);
	return player;
}

Block* GameObjectFactory::createBlock(vec3 pos)
{
	return new Block(pos);
}

Billboard* GameObjectFactory::createBillboard(vec3 pos)
{
	return new Billboard(pos);
}
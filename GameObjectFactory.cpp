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

GO_Wall* GameObjectFactory::createWall(vec3 pos)
{
	return new GO_Wall(pos);
}

GO_Ground* GameObjectFactory::createGround()
{
	return new GO_Ground();
}

GO_Player* GameObjectFactory::createPlayer(vec3 pos)
{
	GO_Player* player = new GO_Player(pos);
	ObjectCamera* cam = new ObjectCamera(player);
	CameraManager::getInstance().setActiveCamera(cam);
	return player;
}

GO_Block* GameObjectFactory::createBlock(vec3 pos)
{
	return new GO_Block(pos);
}

GO_Billboard* GameObjectFactory::createBillboard(vec3 pos)
{
	return new GO_Billboard(pos);
}
//
//  GameObjectFactory.h
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-04-28.
//
//

#ifndef __OpenGLGLUTApp__GameObjectFactory__
#define __OpenGLGLUTApp__GameObjectFactory__

#include <iostream>
#include "Wall.h"
#include "Ground.h"
#include "Player.h"
#include "Block.h"
#include "CameraManager.h"
#include "ObjectCamera.h"
#include "Billboard.h"

class GameObjectFactory
{
public:
	static GameObjectFactory& getInstance()
	{
		static GameObjectFactory instance;
		return instance;
	}
	
	Wall* createWall(vec3 pos);
	Ground* createGround();
	Player* createPlayer(vec3 pos);
	Block* createBlock(vec3 pos);
	Billboard* createBillboard(vec3 pos); 
	
protected:
	
private:
	GameObjectFactory();
	GameObjectFactory(const GameObjectFactory&);
	GameObjectFactory& operator=(const GameObjectFactory&);
	
};

#endif /* defined(__OpenGLGLUTApp__GameObjectFactory__) */

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
#include "GO_Wall.h"
#include "GO_Ground.h"
#include "GO_Player.h"
#include "GO_Block.h"
#include "CameraManager.h"
#include "ObjectCamera.h"
#include "GO_Billboard.h"

class GameObjectFactory
{
public:
	static GameObjectFactory& getInstance()
	{
		static GameObjectFactory instance;
		return instance;
	}
	
	GO_Wall* createWall(vec3 pos);
	GO_Ground* createGround();
	GO_Player* createPlayer(vec3 pos);
	GO_Block* createBlock(vec3 pos);
	GO_Billboard* createBillboard(vec3 pos); 
	
protected:
	
private:
	GameObjectFactory();
	GameObjectFactory(const GameObjectFactory&);
	GameObjectFactory& operator=(const GameObjectFactory&);
	
};

#endif /* defined(__OpenGLGLUTApp__GameObjectFactory__) */

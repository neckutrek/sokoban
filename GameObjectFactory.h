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

class GameObjectFactory
{
public:
	static GameObjectFactory& getInstance()
	{
		static GameObjectFactory instance;
		return instance;
	}
	
	Wall* createWall(vec3 pos);
	/*
	GameObject* createPlayer(vec3 pos);
	GameObject* createBlock(vec3 pos);
	GameObject* createPlate(vec3 pos);
	 */
	
protected:
	
private:
	GameObjectFactory();
	GameObjectFactory(const GameObjectFactory&);
	GameObjectFactory& operator=(const GameObjectFactory&);
	
};

#endif /* defined(__OpenGLGLUTApp__GameObjectFactory__) */

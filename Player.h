//
//  Player.h
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-04-30.
//
//

#ifndef __OpenGLGLUTApp__Player__
#define __OpenGLGLUTApp__Player__

#include <iostream>
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player(vec3 pos);
	~Player() {}
	std::string getType();
	
protected:
	
private:
	
};

#endif /* defined(__OpenGLGLUTApp__Player__) */

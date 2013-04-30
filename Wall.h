//
//  Wall.h
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-04-28.
//
//

#ifndef __OpenGLGLUTApp__Wall__
#define __OpenGLGLUTApp__Wall__

#include <iostream>
#include "GameObject.h"

class Wall : public GameObject
{
public:
	Wall(vec3 pos);
	~Wall() {}
	std::string getType();
	
protected:
	
private:
	
};

#endif /* defined(__OpenGLGLUTApp__Wall__) */

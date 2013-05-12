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

class GO_Wall : public GameObject
{
public:
	GO_Wall(vec3 pos, GLfloat rot, std::string modelType);
	~GO_Wall() {}
	std::string getType();
	
protected:
	
private:
	
};

#endif /* defined(__OpenGLGLUTApp__Wall__) */

//
//  Block.h
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-05-01.
//
//

#ifndef __OpenGLGLUTApp__Block__
#define __OpenGLGLUTApp__Block__

#include <iostream>
#include "GameObject.h"

class GO_Block : public GameObject
{
public:
	GO_Block(vec3 pos);
	~GO_Block() {}
	std::string getType();
	
protected:
	
private:
	
};

#endif /* defined(__OpenGLGLUTApp__Block__) */

//
//  GO_Button.h
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-05-08.
//
//

#ifndef __OpenGLGLUTApp__GO_Button__
#define __OpenGLGLUTApp__GO_Button__

#include <iostream>
#include "GameObject.h"

class GO_Button : public GameObject
{
public:
	GO_Button(vec3 pos);
	~GO_Button() {}
	std::string getType();
	
protected:
	
private:
	
};

#endif /* defined(__OpenGLGLUTApp__GO_Button__) */

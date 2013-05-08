//
//  GO_Skybox.h
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-05-08.
//
//

#ifndef __OpenGLGLUTApp__GO_Skybox__
#define __OpenGLGLUTApp__GO_Skybox__

#include <iostream>
#include "GameObject.h"

class GO_Skybox : public GameObject
{
public:
	GO_Skybox();
	~GO_Skybox() {}
	std::string getType();
	
    virtual int render(GLuint program_reference_id);
	
protected:
	
private:
	
};

#endif /* defined(__OpenGLGLUTApp__GO_Skybox__) */

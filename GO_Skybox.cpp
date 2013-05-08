//
//  GO_Skybox.cpp
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-05-08.
//
//

#include "GO_Skybox.h"

GO_Skybox::GO_Skybox() : GameObject(BoundingBox(0))
{
	loadModel("skybox.obj");
	addMaterial("skybox_c.tga", 1, 0);
	setScaling(100, 100, 100);
	_is_affected_by_light = false;
}

std::string GO_Skybox::getType()
{
	return "skybox";
}

int GO_Skybox::render(GLuint program_reference_id)
{
	glDisable(GL_DEPTH_TEST);
	Renderable::render(program_reference_id);
	glEnable(GL_DEPTH_TEST);
}

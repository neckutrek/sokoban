//
//  GameObject.cpp
//  OpenGLGLUTApp
//
//  Created by Marcus Johansson on 4/10/13.
//
//

#include "GameObject.h"

virtual mat4 GameObject::getModelTransformationMatrix()
{
    return Body::getModelMatrix();
}
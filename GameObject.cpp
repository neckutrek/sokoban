//
//  GameObject.cpp
//  OpenGLGLUTApp
//
//  Created by Marcus Johansson on 4/10/13.
//
//

#include "GameObject.h"

mat4 GameObject::getModelTransformationMatrix()
{
    return Body::getModelMatrix();
}


//
//  RenderableMultilayer.cpp
//  OpenGLGLUTApp
//
//  Created by Marcus Johansson on 4/28/13.
//
//

#include "RenderableMultilayer.h"

void addMaterial(const char *texture_file_name,
                 float transparency,
                 float specularity)
{
    
}

int render(GLuint program_reference_id)
{
    MaterialManager::getInstance().setMaterialsCounter(materials_counter);
    MaterialManager::getInstance().setTexureIDs(&texture_ids[0]);
    MaterialManager::getInstance().setTransparencies(&transparencies[0]);
    MaterialManager::getInstance().setSpecularities(&specularities[0]);
    
    MaterialManager::getInstance().render(program_reference_id);
    Renderable::render(program_reference_id);
}
//
//  RenderableMultilayer.cpp
//  OpenGLGLUTApp
//
//  Created by Marcus Johansson on 4/28/13.
//
//

#include "RenderableMultilayer.h"

RenderableMultilayer::RenderableMultilayer()
: materials_counter(0)
{
    for (int i=0; i<MAX_LAYERS; ++i)
    {
        texture_ids[i] = 0;
        transparencies[i] = 1.0;
        specularities[i] = 100.0;
    }
}

void RenderableMultilayer::addMaterial(char *texture_file_name,
                 float transparency,
                 float specularity)
{
    if (materials_counter >= MAX_LAYERS) return;
    
    LoadTGATextureSimple(texture_file_name, &texture_ids[materials_counter]);
    transparencies[materials_counter] = transparency;
    specularities[materials_counter] = specularity;
    materials_counter++;
}

int RenderableMultilayer::render(GLuint program_reference_id)
{
    MaterialManager::getInstance().setMaterialsCounter(materials_counter);
    MaterialManager::getInstance().setTexureIDs(&texture_ids[0]);
    MaterialManager::getInstance().setTransparencies(&transparencies[0]);
    MaterialManager::getInstance().setSpecularities(&specularities[0]);
    
    MaterialManager::getInstance().render(program_reference_id);
    Renderable::render(program_reference_id);
}
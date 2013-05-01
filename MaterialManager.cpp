//
//  Material.cpp
//  OpenGLGLUTApp
//
//  Created by Marcus Johansson on 4/28/13.
//

#include <iostream>
#include "MaterialManager.h"

MaterialManager& MaterialManager::getInstance()
{
    static MaterialManager instance;
    return instance;
}

MaterialManager::~MaterialManager() {}

void MaterialManager::initialize(GLuint program_reference_id)
{
    glUniform1iv(glGetUniformLocation(program_reference_id, "texture_units"),
                 MAX_LAYERS,
                 &texture_units_array[0]);
}

void MaterialManager::setTransparencies(GLfloat *transparencies)
{
    transparency_array = transparencies;
}

void MaterialManager::setSpecularities(GLfloat *specularities)
{
    specularity_array = specularities;
}

void MaterialManager::setTexureIDs(GLuint *texture_ids)
{
    texture_id_array = texture_ids;
}

void MaterialManager::setMaterialsCounter(GLint count)
{
    materials_counter = count;
    if (materials_counter > MAX_LAYERS)
        materials_counter = MAX_LAYERS;
}

int MaterialManager::render(GLuint program_reference_id)
{
    glUniform1i(glGetUniformLocation(program_reference_id, "materials_counter"),
                materials_counter);
    glUniform1fv(glGetUniformLocation(program_reference_id, "material_transparencies"),
                 materials_counter, &transparency_array[0]);
    glUniform1fv(glGetUniformLocation(program_reference_id, "material_specularities"),
                 materials_counter, &specularity_array[0]);
    
    for (unsigned int i=0; i<materials_counter; ++i) {
        switch (i) {
            case 0: glActiveTexture(GL_TEXTURE0); break;
            case 1: glActiveTexture(GL_TEXTURE1); break;
            case 2: glActiveTexture(GL_TEXTURE2); break;
            case 3: glActiveTexture(GL_TEXTURE3); break;
            case 4: glActiveTexture(GL_TEXTURE4); break;
            case 5: glActiveTexture(GL_TEXTURE5); break;
            case 6: glActiveTexture(GL_TEXTURE6); break;
            case 7: glActiveTexture(GL_TEXTURE7); break;
            default: break;
        }
        glBindTexture(GL_TEXTURE_2D, texture_id_array[i]);
    }
    return 0;
}

MaterialManager::MaterialManager()
{
    materials_counter = 0;
    for (unsigned int i=0; i<MAX_LAYERS; ++i)
    {
        texture_units_array[i] = i;
    }
}
MaterialManager::MaterialManager(const MaterialManager&) {}
MaterialManager& MaterialManager::operator=(const MaterialManager&)
{
    return *this;
}

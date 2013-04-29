//
//  Material.h
//  OpenGLGLUTApp
//
//  Created by Marcus Johansson on 4/28/13.
//
//

#ifndef __OpenGLGLUTApp__Material__
#define __OpenGLGLUTApp__Material__


#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include "MicroGlut.h"
#endif

const unsigned int MAX_LAYERS = 8;

class MaterialManager
{
public:
    static MaterialManager& getInstance()
    {
        static MaterialManager instance;
        return instance;
    }
    
    ~MaterialManager() {}
    
    void initialize(GLuint program_reference_id)
    {
        glUniform1iv(glGetUniformLocation(program_reference_id, "texture_units"),
                     MAX_LAYERS,
                     &texture_units_array[0]);
    }
    
    void setTransparencies(float *transparencies)
    {
        transparency_array = transparencies;
    }
    
    void setSpecularities(float *specularities)
    {
        specularity_array = specularities;
    }
    
    void setTexureIDs(unsigned int *texture_ids)
    {
        texture_id_array = texture_ids;
    }
    
    void setMaterialsCounter(unsigned int count)
    {
        materials_counter = count;
        if (materials_counter > MAX_LAYERS)
            materials_counter = MAX_LAYERS;
    }
    
    int render(GLuint program_reference_id)
    {
        glUniform1i(glGetUniformLocation(program_reference_id, "materials_counter"),
                    materials_counter);
        
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
    
    
private:
    MaterialManager()
    {
        materials_counter = 0;
        for (unsigned int i=0; i<MAX_LAYERS; ++i)
        {
            texture_units_array[i] = i;
        }
    }
    MaterialManager(const MaterialManager&) {}
    MaterialManager& operator=(const MaterialManager&) {}
    
    unsigned int texture_units_array[MAX_LAYERS];
    float *transparency_array;
    float *specularity_array;
    unsigned int *texture_id_array;
    unsigned int materials_counter;
};

#endif /* defined(__OpenGLGLUTApp__Material__) */

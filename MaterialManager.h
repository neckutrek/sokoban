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

#include "GL_utilities.h"
#include "VectorUtils3Addons.h"
#include "loadobj.h"

const unsigned int MAX_LAYERS = 8;

class MaterialManager
{
public:
    static MaterialManager& getInstance();
    
    ~MaterialManager();
    
    void initialize(GLuint program_reference_id);
    
    void setTransparencies(float *transparencies);
    
    void setSpecularities(float *specularities);
    
    void setTexureIDs(unsigned int *texture_ids);
    
    void setMaterialsCounter(unsigned int count);
    
    int render(GLuint program_reference_id);
    
    
private:
    MaterialManager();
    MaterialManager(const MaterialManager&);
    MaterialManager& operator=(const MaterialManager&);
    
    unsigned int texture_units_array[MAX_LAYERS];
    float *transparency_array;
    float *specularity_array;
    unsigned int *texture_id_array;
    unsigned int materials_counter;
};

#endif /* defined(__OpenGLGLUTApp__Material__) */

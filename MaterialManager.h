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

//#include "GL_utilities.h"
//#include "VectorUtils3Addons.h"

const unsigned int MAX_LAYERS = 8;

class MaterialManager
{
public:
    static MaterialManager& getInstance();
    
    ~MaterialManager();
    
    void initialize(GLuint program_reference_id);
    
    void setTransparencies(GLfloat *transparencies);
    
    void setSpecularities(GLfloat *specularities);
    
    void setTexureIDs(GLuint *texture_ids);
    
    void setMaterialsCounter(GLint count);
    
    int render(GLuint program_reference_id);
    
    
private:
    MaterialManager();
    MaterialManager(const MaterialManager&);
    MaterialManager& operator=(const MaterialManager&);
    
    GLint texture_units_array[MAX_LAYERS];
    GLfloat *transparency_array;
    GLfloat *specularity_array;
    GLuint *texture_id_array;
    GLint materials_counter;
};

#endif /* defined(__OpenGLGLUTApp__Material__) */

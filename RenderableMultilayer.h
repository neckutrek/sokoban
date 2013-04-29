//
//  RenderableMultilayer.h
//  OpenGLGLUTApp
//
//  Created by Marcus Johansson on 4/28/13.
//
//

#ifndef __OpenGLGLUTApp__RenderableMultilayer__
#define __OpenGLGLUTApp__RenderableMultilayer__

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include "MicroGlut.h"
#endif

#include "Renderable.h"
#include "MaterialManager.h"

class RenderableMultilayer : public Renderable
{
public:
    RenderableMultilayer()
    : materials_counter(0)
    {
        for (int i=0; i<MAX_LAYERS; ++i)
        {
            texture_ids[i] = 0;
            transparencies[i] = 1.0;
            specularities[i] = 100.0;
        }
    }
    virtual ~RenderableMultilayer() {}
    
    void addMaterial(const char *texture_file_name,
                     float transparency,
                     float specularity);
    
    virtual int render(GLuint program_reference_id);
    
    
private:
    GLuint texture_ids[MAX_LAYERS];
    float transparencies[MAX_LAYERS];
    float specularities[MAX_LAYERS];
    
    unsigned int materials_counter;
};

#endif /* defined(__OpenGLGLUTApp__RenderableMultilayer__) */

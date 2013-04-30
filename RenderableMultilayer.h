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
#include "LoadTGA2.h"

class RenderableMultilayer : virtual public Renderable
{
public:
    RenderableMultilayer();
    virtual ~RenderableMultilayer() {}
    
    void addMaterial(char *texture_file_name,
                     float transparency,
                     float specularity);
    
    virtual int render(GLuint program_reference_id);
    
    
private:
    GLuint texture_ids[MAX_LAYERS];
    GLfloat transparencies[MAX_LAYERS];
    GLfloat specularities[MAX_LAYERS];
    
    GLint materials_counter;
};

#endif /* defined(__OpenGLGLUTApp__RenderableMultilayer__) */

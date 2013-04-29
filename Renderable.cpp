//
//  Renderable.cpp
//  OpenGLGLUTApp
//
//  Created by Marcus Johansson on 4/10/13.
//
//

#include <iostream>
#include "Renderable.h"
#include "loadobj.h"

int Renderable::loadModel(const char* model_filename)
{
    _model = LoadModelPlus(model_filename);
    _is_model_loaded = true;
    return 0;
}

int Renderable::render(GLuint program_reference_id)
{
    if (_is_model_loaded) {
        glUniformMatrix4fv(glGetUniformLocation(program_reference_id,
                                                "model_transformation"),
                           1, GL_TRUE, getModelTransformationMatrix().m);
        DrawModel(_model,
                  program_reference_id,
                  "in_vertex_coordinate",
                  "in_vertex_normal_vector",
                  "in_texture_coordinate");
    }
}
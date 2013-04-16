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
        std::cout << "rendering model" << std::endl;
        std::cout << getModelTransformationMatrix() << std::endl;
        glBindVertexArray(_model->vao);
        glUniformMatrix4fv(glGetUniformLocation(program_reference_id,
                                                "model_transformation"),
                           1, GL_TRUE, getModelTransformationMatrix().m);
        //glUniform1i(glGetUniformLocation(program, "nTextures"), o->nTextures);
        /*
        for (int i=0; i<o->nTextures; i++) {
            switch (i) {
                case 0: glActiveTexture(GL_TEXTURE0); break;
                case 1: glActiveTexture(GL_TEXTURE1); break;
                case 2: glActiveTexture(GL_TEXTURE2); break;
                case 3: glActiveTexture(GL_TEXTURE3); break;
                case 4: glActiveTexture(GL_TEXTURE4); break;
                case 5: glActiveTexture(GL_TEXTURE5); break;
                case 6: glActiveTexture(GL_TEXTURE6); break;
                case 7: glActiveTexture(GL_TEXTURE7); break;
                case 8: glActiveTexture(GL_TEXTURE8); break;
                case 9: glActiveTexture(GL_TEXTURE9); break;
            }
            glBindTexture(GL_TEXTURE_2D, o->textures[i]);
        }*/
        
        glDrawElements(GL_TRIANGLES, _model->numIndices, GL_UNSIGNED_INT, 0L);
    }
}
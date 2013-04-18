//
//  VectorUtils3Addons.h
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-04-10.
//
//

#ifndef __OpenGLGLUTApp__VectorUtils3Addons__
#define __OpenGLGLUTApp__VectorUtils3Addons__

#include <iostream>
#include "VectorUtils3.h"

std::ostream& operator<<(std::ostream &os, const mat4 &a);

std::ostream& operator<<(std::ostream &os, const vec3 &a);

//mat4 * scalar

mat4 operator*(const mat4 &a, const float &b);

GLfloat clamp(GLfloat x, GLfloat min, GLfloat max);

#endif /* defined(__OpenGLGLUTApp__VectorUtils3Addons__) */

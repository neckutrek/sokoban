//
//  BoundingBox.h
//  OpenGLGLUTApp
//
//  Created by Marcus Johansson on 4/28/13.
//
//

#ifndef __OpenGLGLUTApp__BoundingBox__
#define __OpenGLGLUTApp__BoundingBox__

#include <iostream>
#include "VectorUtils3Addons.h"

class BoundingBox
{
public:
	BoundingBox(vec3 lows, vec3 highs);
	BoundingBox(vec3 highs);
	BoundingBox(GLfloat high);
	~BoundingBox();
	
	bool intersect(const BoundingBox &boundingBox) const;
    
    BoundingBox operator+(const vec3 &motion) const;
    BoundingBox& operator+=(const vec3 &motion);
	
protected:
	
private:
	vec3 _topLeftBack;
	vec3 _bottomRightFront;
};

#endif /* defined(__OpenGLGLUTApp__BoundingBox__) */

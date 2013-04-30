//
//  BoundingBox.cpp
//  OpenGLGLUTApp
//
//  Created by Marcus Johansson on 4/28/13.
//
//

#include "BoundingBox.h"

BoundingBox::BoundingBox(vec3 lows, vec3 highs) : _topLeftBack(lows), _bottomRightFront(highs)
{}

BoundingBox::BoundingBox(vec3 highs)
{
	BoundingBox(highs, highs);
}

BoundingBox::BoundingBox(GLfloat high)
{
	BoundingBox(vec3(high, high, high), vec3(high, high, high));
}

BoundingBox::~BoundingBox()
{
	
}

bool BoundingBox::intersect(const BoundingBox &boundingBox) const
{
	return ((_topLeftBack.x < boundingBox._bottomRightFront.x) &&
			(_bottomRightFront.x > boundingBox._topLeftBack.x) &&
			(_topLeftBack.y < boundingBox._bottomRightFront.y) &&
			(_bottomRightFront.y > boundingBox._topLeftBack.y) &&
			(_topLeftBack.z < boundingBox._bottomRightFront.z) &&
			(_bottomRightFront.z > boundingBox._topLeftBack.z));
}
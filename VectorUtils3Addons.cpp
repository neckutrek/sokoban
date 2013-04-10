//
//  VectorUtils3Addons.cpp
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-04-10.
//
//

#include "VectorUtils3Addons.h"

std::ostream& operator<<(std::ostream &os, const mat4 &a)
{
	for(int y=0; y<4; y++)
	{
		for(int x=0; x<4; x++)
			os << a.m[4*y + x] << " ";
		os << std::endl;
	}
	return os;
}

std::ostream& operator<<(std::ostream &os, const vec3 &a)
{
	os << a.x << " " << a.y << " " << a.z;
	return os;
}

mat4 operator*(const mat4 &a, const float &b)
{
	mat4 temp = a;
	for (int i=0; i<16; i++)
		temp.m[i] *= b;
	return temp;
}
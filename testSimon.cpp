//
//  testSimon.cpp
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-04-10.
//
//

#include "Body.h"
#include "VectorUtils3.h"
#include "VectorUtils3Addons.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    Body *b = new Body();
	b->setPosition(1, 2, 3);
	b->setRotVelocity(1, 0, 0, 0.5);
	cout << b->getPosition();
}

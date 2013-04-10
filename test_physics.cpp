//
//  testSimon.cpp
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-04-10.
//
//

#include "loadobj.h"
#include "Body.h"
#include "VectorUtils3.h"
#include "VectorUtils3Addons.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    
    Model* m = LoadModelPlus("bunnyplus.obj");
    
    cout << " - Testing a particle - " << endl;
    Body* p = new Body(0, 0, 0);
    p->setPosition(1,1,1);
    p->setVelocity(-2,1,0);
    p->setAcceleration(1,0,1);
    p->setRot(0,0,0,0);
    p->setRotVelocity(1,0,1,0);
    p->setRotAcceleration(-2,3,1,-1);
    
    
    for (int i=0; i<5; i++) {
        cout << "#" << i << ": " << *p << endl;
        p->update(1);
    }
    
    Body *b = new Body();
	b->setPosition(1, 2, 3);
	b->setRotVelocity(1, 0, 0, 0.5);
	cout << b->getPosition();
}

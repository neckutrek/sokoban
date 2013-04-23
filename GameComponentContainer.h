//
//  GameComponentContainer.h
//  OpenGLGLUTApp
//
//  Created by Marcus Johansson on 4/16/13.
//
//

#ifndef __OpenGLGLUTApp__GameComponentContainer__
#define __OpenGLGLUTApp__GameComponentContainer__

#include "GameComponent.h"

#include <iostream>
#include <string>
#include <vector>

class CollisionInformation {};

typedef unsigned int (CollisionCallbackType)(GameComponent& c1, GameComponent& c2, const CollisionInformation& ci);

class GameComponentContainer
{
public:
    GameComponentContainer();
    ~GameComponentContainer();
    
unsigned int registerCollisionFn(std::string component_id_1,
                                 std::string component_id_2,
                                 CollisionCallbackType& fn);
    
private:
    std::vector<CollisionCallbackType*> coll_callback_fns;
};

#endif /* defined(__OpenGLGLUTApp__GameComponentContainer__) */

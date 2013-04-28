//
//  GameComponentContainer.h
//  OpenGLGLUTApp
//
//  Created by Marcus Johansson on 4/16/13.
//
//

#ifndef __OpenGLGLUTApp__GameComponentContainer__
#define __OpenGLGLUTApp__GameComponentContainer__

#include "GameObject.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>

//class CollisionInformation {};

//typedef unsigned int (CollisionCallbackType)(GameComponent& c1, GameComponent& c2, const CollisionInformation& ci);

class GameObjectManager
{
public:
    GameObjectManager();
    ~GameObjectManager();
    
//unsigned int registerCollisionFn(std::string component_id_1,
//                                 std::string component_id_2,
//                                 CollisionCallbackType& fn);
    
    unsigned int addObject(GameObject* go);
    void removeObject(unsigned int id);
    
    GameObject* getObjectFromName(unsigned int id);
    std::vector<GameObject*> getObjectsFromType(std::string type);
    std::vector<GameObject*> getObjectsWithinBox(BoundingBox box);
    std::vector<GameObject*> getObjectsAtPosition(vec3 pos);
    
    
    void update();
    void render();
    
private:
    //std::vector<CollisionCallbackType*> _coll_callback_fns;
    
    struct EntryInfo {
        std::string type;
        GameObject* object;
    };
    
    std::map<unsigned int, EntryInfo> _game_entities_on_id;
};

#endif /* defined(__OpenGLGLUTApp__GameComponentContainer__) */

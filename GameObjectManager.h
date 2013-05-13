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
	static GameObjectManager& getInstance();
    
//unsigned int registerCollisionFn(std::string component_id_1,
//                                 std::string component_id_2,
//                                 CollisionCallbackType& fn);
    
    unsigned int addObject(GameObject* go);
    void removeObject(unsigned int id);
    
    GameObject* getObjectFromId(unsigned int id);
    std::vector<GameObject*> getObjectsFromType(std::string type);
    std::vector<GameObject*> getObjectsWithinBox(const BoundingBox& displaced_box);
    std::vector<GameObject*> getObjectsAtPosition(vec3 pos);
    
    bool check_boundingbox_collision(const BoundingBox &box);
	
	
	
    void update(int dtime);
    void render(GLuint prog_ref_id);
    
private:
	GameObjectManager();
	GameObjectManager(const GameObjectManager&);
	GameObjectManager& operator=(const GameObjectManager&);
	
    //std::vector<CollisionCallbackType*> _coll_callback_fns;
    
    struct EntryInfo {
        std::string type;
        GameObject* object;
    };
    
    std::map<unsigned int, EntryInfo> _game_entities;
	int _id_counter;
};

#endif /* defined(__OpenGLGLUTApp__GameComponentContainer__) */

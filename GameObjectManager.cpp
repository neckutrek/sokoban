//
//  GameComponentContainer.cpp
//  OpenGLGLUTApp
//
//  Created by Marcus Johansson on 4/16/13.
//
//

#include "GameObjectManager.h"

GameObjectManager& GameObjectManager::getInstance()
{
    static GameObjectManager instance;
    return instance;
}

GameObjectManager::GameObjectManager() : _id_counter(0)
{}
GameObjectManager::GameObjectManager(const GameObjectManager&) {}
GameObjectManager& GameObjectManager::operator=(const GameObjectManager&)
{
    return *this;
}

unsigned int GameObjectManager::addObject(GameObject *go)
{
	EntryInfo ei = {go->getType(), go};
	_game_entities.insert(std::pair<int, EntryInfo>(_id_counter, ei));
	return _id_counter++;
}

void GameObjectManager::removeObject(unsigned int id)
{
	delete _game_entities.at(id).object;
	_game_entities.erase(id);
}

GameObject* GameObjectManager::getObjectFromId(unsigned int id)
{
	return _game_entities.at(id).object;
}

std::vector<GameObject*> GameObjectManager::getObjectsFromType(std::string type)
{
	std::vector<GameObject*> objects;
	std::map<unsigned int, EntryInfo>::iterator iter;
	for(iter = _game_entities.begin(); iter != _game_entities.end(); iter++)
	{
		if(iter->second.type == type)
			objects.push_back(iter->second.object);
	}
	return objects;
}

std::vector<GameObject*> GameObjectManager::getObjectsWithinBox(const BoundingBox& displaced_box)
{
	std::vector<GameObject*> objects;
	GameObject* go;
	std::map<unsigned int, EntryInfo>::iterator iter;
	for (iter = _game_entities.begin(); iter != _game_entities.end(); iter++)
	{
		go = iter->second.object;
		if (displaced_box.intersect(go->getDisplacedBoundingBox()))
			objects.push_back(go);
	}
	return objects;
}

bool GameObjectManager::check_boundingbox_collision(const BoundingBox &displaced_box)
{
	std::map<unsigned int, EntryInfo>::iterator iter;
	for (iter = _game_entities.begin(); iter != _game_entities.end(); iter++)
	{
		if ( displaced_box.intersect(iter->second.object->getDisplacedBoundingBox()) )
			return true;
	}
	return false;
}

std::vector<GameObject*> GameObjectManager::getObjectsAtPosition(vec3 pos)
{
	std::vector<GameObject*> objects;
	GameObject* go;
	std::map<unsigned int, EntryInfo>::iterator iter;
	for(iter = _game_entities.begin(); iter != _game_entities.end(); iter++)
	{
		go = iter->second.object;
		if(pos == go->getPosition())
			objects.push_back(go);
	}
	return objects;
}

void GameObjectManager::update(int dtime)
{
	std::map<unsigned int, EntryInfo>::iterator iter;
	for(iter = _game_entities.begin(); iter != _game_entities.end(); iter++)
		iter->second.object->update(dtime);
}

void GameObjectManager::render(GLuint prog_ref_id)
{
    std::map<unsigned int, EntryInfo>::iterator iter;
	for(iter = _game_entities.begin(); iter != _game_entities.end(); iter++)
		if(iter->second.type == "skybox")
			iter->second.object->render(prog_ref_id);
	
	for(iter = _game_entities.begin(); iter != _game_entities.end(); iter++)
		if(iter->second.type != "skybox")
			iter->second.object->render(prog_ref_id);
}
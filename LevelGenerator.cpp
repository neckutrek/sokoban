//
//  LevelGenerator.cpp
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-04-22.
//
//

#include "LevelGenerator.h"

const std::string LevelGenerator::CHAR_MAPPER = " X.pPoO";
const std::string LevelGenerator::EXTRA_MAPPER[] = {"Test extra"};


bool LevelGenerator::fileExists(const std::string &fileName) const
{
	std::ifstream ifs(fileName.c_str());
	if (!ifs || ifs.bad())
		return false;
	return true;
}

bool LevelGenerator::open(const std::string &fileName)
{
	if(!fileExists(fileName))
		return false;
	close();
	_fileStream = new std::ifstream(fileName.c_str());
	if (!*_fileStream || _fileStream->bad()) {
		close();
		return false;
	}
	_fileName = fileName;
	return true;
}

void LevelGenerator::close()
{
	if (_fileStream) 
		delete _fileStream;
	_fileStream = 0;
	_fileName = "";
	_buffer = "";
	_mapWidth = 0;
	_mapHeight = 0;
	for(int y=0; y<MAX_LEVEL_HEIGHT; y++)
		for(int x=0; x<MAX_LEVEL_WIDTH; x++)
			_map[y*MAX_LEVEL_WIDTH+x] = EMPTY;
	for(int i=0; i<MAX_EXTRAS; i++)
	{
		_extras[i].type=EMPTY_EXTRA;
		_extras[i].value="";
	}
}

void LevelGenerator::load(const std::string &fileName)
{
	std::cout << "Loading file " << fileName << "... ";
	open(fileName);
	read();
	//here some map (and extras) checking would be suitable
	generateMap();
	applyExtras();
	close();
	std::cout << "done!" << std::endl;
}

void LevelGenerator::read()
{
	//if(!fileExists(fileName)) Throw stuff
	std::getline(*_fileStream, _buffer);
	while (!_fileStream->eof())
	{
		//if(_buffer.at(0) != '%') Throw stuff
		if(_buffer.substr(0,4) == "%MAP")
			readMap();
		else if (_buffer.substr(0,7) == "%EXTRAS")
			readExtras();
		else
			std::cout << "empty row in level file" << std::cout;
		//should throw some error...
	}
}

void LevelGenerator::readMap()
{
	//for each line
	do
	{
		std::getline(*_fileStream, _buffer);
		//if(y>MAX_LEVEL_HEIGHT) Throw error...2
		//for each character except the last, linebreaking character
		if(_buffer.at(0) == '%')
			return;
		for(int x=0; x<_buffer.length()-(_fileStream->eof() ? 0 : 1); x++)
		{
			//if(x>MAX_LEVEL_WIDTH) Throw error...
			if(x+1>_mapWidth)
				_mapWidth=x+1;
			_map[MAX_LEVEL_WIDTH*_mapHeight + x] = getMapToken(_buffer.at(x));
		}
		_mapHeight++;
	} while(!_fileStream->eof());
}

LevelGenerator::MapToken LevelGenerator::getMapToken(char token)
{
	//if(CHAR_MAPPER.find(token)<0) Throw some error...
	return static_cast<MapToken>(CHAR_MAPPER.find(token));
}

void LevelGenerator::readExtras()
{
	int count=0;
	int equalSignIndex=0;
	do
	{
		std::getline(*_fileStream, _buffer);
		if(_buffer.at(0) == '%')
			return;
		equalSignIndex=_buffer.find('=');
		_extras[count].type = getExtraType(_buffer.substr(0, equalSignIndex));
		_extras[count].value = _buffer.substr(equalSignIndex+1, _buffer.length()-equalSignIndex-(_fileStream->eof() ? 1 : 2));
		count++;
	} while(!_fileStream->eof());
}

LevelGenerator::ExtraType LevelGenerator::getExtraType(std::string extra)
{
	for(int i=0; i<sizeof(EXTRA_MAPPER)/sizeof(std::string); i++)
		if(EXTRA_MAPPER[i].compare(extra)==0)
			return static_cast<ExtraType>(i);
	return EMPTY_EXTRA;
}

void LevelGenerator::generateMap()
{
	GameObject* go;
	GameObjectManager& gom = GameObjectManager::getInstance();
	GameObjectFactory& gof = GameObjectFactory::getInstance();
	for(int x=0; x<_mapWidth; x++)
		for(int y=0; y<_mapHeight; y++)
		{
			switch(_map[y*MAX_LEVEL_HEIGHT+x])
			{
				case EMPTY:
					break;
				case WALL:
					go = gof.createWall(vec3(x, 0.5, y));
					gom.addObject(go);
					break;
				case PLATE:
					break;
				case PLAYER:
					go = gof.createPlayer(vec3(x, 1, y));
					gom.addObject(go);
					break;
				case PLAYER_ON_PLATE:
					break;
				case BLOCK:
					go = gof.createBlock(vec3(x, 0.5, y));
					gom.addObject(go);
				case BLOCK_ON_PLATE:
					break;
			}
		}
	go = gof.createGround();
	gom.addObject(go);
}

void LevelGenerator::applyExtras()
{
	for(int i=0; i<MAX_EXTRAS; i++)
	{
		switch (_extras[i].type)
		{
			case EMPTY_EXTRA:
				return;
			case TEST_EXTRA:
				std::cout << "Test extra(" << _extras[i].value << ")" << std::endl;
				break;
		}
	}
}

std::string& LevelGenerator::getFileName()
{
	return _fileName;
}


LevelGenerator::LevelGenerator()
{}
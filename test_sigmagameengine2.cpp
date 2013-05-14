//
//
//

#include <string>
using namespace std;

#include "SigmaGameEngine.h"
#include "LevelGenerator.h"
#include "GO_Wall.h"
DebugCamera* c1 = new DebugCamera();
CutsceneCamera* c3 = new CutsceneCamera();

void init1Object()
{
    /*
    GameObject* go = new GO_Wall(vec3(0.0, 0.0, 0.0));
    go->loadModel("bunnyplus.obj");
    go->addMaterial("button_c.tga", 1.0, 200);
    go->setRotVelocity(0.5, 0.5, 0.5, 0.05);
    GameObjectManager::getInstance().addObject(go);
    
    */
}

int main(int argc, char *argv[])
{
    SigmaGameEngine& game = SigmaGameEngine::getInstance();
    game.initialize(argc, argv,
                    "shader_1.vert", "shader_1.frag",
                    1024, 768, "SigmaGameEngine running . . .");
    
    
    // add the sun
    LightManager::getInstance().addLight(vec3(5.0, 100.0, 5.0), vec3(1, 1, 1), 300.0);
    LightManager::getInstance().addLight(vec3(5.0, 10.0, 5.0), vec3(1, 1, 1), 5.0);
    LightManager::getInstance().addLight(vec3(5.0, -10.0, 5.0), vec3(1, 1, 1), 5.0);
    LightManager::getInstance().addLight(vec3(5.0, 2.0, 5.0), vec3(1, 1, 1), 1.0);
//    LightManager::getInstance().addLight(vec3(0.0, 5.0, 0.0), vec3(1, 1, 1), 0.3);
//    LightManager::getInstance().addLight(vec3(0.0, 5.0, 10.0), vec3(1, 1, 1), 0.3);
//    LightManager::getInstance().addLight(vec3(10.0, 5.0, 0.0), vec3(1, 1, 1), 0.3);
//    LightManager::getInstance().addLight(vec3(10.0, 5.0, 10.0), vec3(1, 1, 1), 0.3);
    
    if (LevelGenerator::getInstance().fileExists("level3.txt")) {
        LevelGenerator::getInstance().load("level3.txt");
    }

    //CameraManager::getInstance().setActiveCamera(new DebugCamera());
    
    //init27Objects();
    
    game.run();
    
    return 0;
}






//
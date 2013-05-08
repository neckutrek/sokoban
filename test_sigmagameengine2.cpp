//
//
//

#include <string>
using namespace std;

#include "SigmaGameEngine.h"
DebugCamera* c1 = new DebugCamera();
CutsceneCamera* c3 = new CutsceneCamera();

void init27Objects()
{
    string models[5] =
    {"bunnyplus.obj", "button.obj", "crate.obj", "ground.obj", "sphere.obj"};
    
    string skins[3] =
    {"button_c.tga", "crate.tga", "robot_c.tga"};
    
    int i=0;
    int j=0;
	for(int x=0; x<3; x++)
		for(int y=0; y<3; y++)
			for(int z=0; z<3; z++)
			{
                GameObject* go = new GO_Wall(vec3(3*(x-1), 3*(y-1), 3*(z-1)));
                go->loadModel("bunnyplus.obj");//models[j].c_str());
                go->addMaterial("button_c.tga", 0.5, 200);//skins[i].c_str()
                go->addMaterial("button_c.tga", 0.5, 50);//skins[i+1].c_str()
                go->setRotVelocity(0.5, 0.5, 0.5, 0.5);
                GameObjectManager::getInstance().addObject(go);
                
                i++; j++;
                if (i>=5-2) i=0;
                if (j>=3) j=0;
			}
}

void init1Object()
{
    GameObject* go = new GO_Wall(vec3(0.0, 0.0, 0.0));
    go->loadModel("bunnyplus.obj");
    go->addMaterial("button_c.tga", 1.0, 200);
    go->setRotVelocity(0.5, 0.5, 0.5, 0.05);
    GameObjectManager::getInstance().addObject(go);
    
    
}

int main(int argc, char *argv[])
{
    SigmaGameEngine& game = SigmaGameEngine::getInstance();
    game.initialize(argc, argv,
                    "shader_1.vert", "shader_1.frag",
                    800, 600, "SigmaGameEngine running . . .");
    
    init27Objects();
    LightManager::getInstance().addLight(vec3(1.0, 1.0, 1.0), vec3(1., 1., 1.), 1.0);
    DebugCamera *c1 = new DebugCamera();
    c1->setPosition(5,5,5);
    c1->setViewLocation(0, 0, 0);
    CameraManager::getInstance().setActiveCamera(c1);
    
    game.run();
}






//
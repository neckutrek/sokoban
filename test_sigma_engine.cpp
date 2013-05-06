//
//
//

#include <string>
using namespace std;

#include "SigmaGameEngine.h"

int main(int argc, char *argv[])
{
    SigmaGameEngine game = SigmaGameEngine::getInstance();
    game.initialize(argc, argv,
                    "shader_1.vert", "shader_1.frag",
                    800, 800, "SigmaGameEngine running . . .");
    
    string models[4] =
    {"bunnyplus.obj", "klingon.obj", "plutt.obj", "teddy.obj"};
    
    string skins[6] =
    {"dirt.tga", "grass.tga", "maskros512.tga",
        "rutor.tga", "SkyBox512.tga", "wall_512_1_05.tga"};
    
    int i=0;
    int j=0;
	for(int x=0; x<3; x++)
		for(int y=0; y<3; y++)
			for(int z=0; z<3; z++)
			{
                GameObject* go = new GO_Wall(vec3(3*(x-1), 3*(y-1), 3*(z-1)));
                go->loadModel(models[j].c_str());
                go->addMaterial(skins[i].c_str(), 0.5, 200);
                go->addMaterial(skins[i+1].c_str(), 0.5, 50);
                GameObjectManager::getInstance().addObject(go);

                i++; j++;
                if (i>=4) i=0;
                if (j>=4) j=0;
			}
}
class lx_game {
    public:
        int pointer = 0;
        std::vector<std::function<GLFWwindowPtr(GLFWwindowPtr)>> scene = {
        
    };
}game;


#include "scene/main_menu/main_menu.h"
#include "scene/character_selection/character_selection.h"
#include "scene/battle/battle.h"

void scene_init(){
    game.scene.push_back(main_menu);
    game.scene.push_back(character_selection);
    game.scene.push_back(battle);
}
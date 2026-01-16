#include "rul/win/new.h"
#include "scene_tree.h"

void scene_init();

int main() {
    auto win = lxw_new();
    lxw_fixe(win.get());

    char icon[] = "image/icon/icon.png";
    lxw_icon(win.get(), icon);
    glfwSetWindowTitle(win.get(), "记忆之海");

    scene_init();

    shader_init(win.get());
    lxj_zoom(1600);
    while(true){
        win = game.scene[game.pointer](std::move(win));
    }
}
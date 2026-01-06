#include "rul/win/new.h"
#include "scene_tree.h"

template<typename Container>
void cleanupTextures(Container& textureContainer) {
    for(auto& texture : textureContainer) {
        if(texture != 0) {
            glDeleteTextures(1, &texture);  // 从GPU删除纹理
        }
    }
    textureContainer.clear();
}
//场景指针喵
int wasc = 0;
using wscenlise = GLFWwindowPtr(*)(GLFWwindowPtr);
//场景列表喵
wscenlise winscen[] = {
    main_menu,
    character_selection
};

//鼠标位置喵
double mousx = 0, mousy = 0;
//鼠标滚动喵
double moucr = 0;
//鼠标点击喵
bool mouclk = false;
//鼠标位置回调喵
void mouse_callback(GLFWwindow* window, double xpos, double ypos) 
{
    mousx = xpos;
    mousy = ypos;
}
//鼠标点击事件喵
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            mouclk = true;
        } 
        else if (action == GLFW_RELEASE) {
            mouclk = false;
        }
    }
}

// 鼠标滚轮滚动事件回调喵
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    moucr += yoffset;
}


int main(void) {
    auto win = lxw_new();
    lxw_fixe(win.get());
    char icon[] = "image/icon/icon.png";
    lxw_icon(win.get(), icon);
    glfwSetWindowTitle(win.get(), "记忆之海");

    glfwSetCursorPosCallback(win.get(), mouse_callback);
    glfwSetMouseButtonCallback(win.get(), mouse_button_callback);
    glfwSetScrollCallback(win.get(), scroll_callback);
    shader_init();
    wasc = 1;
    while(1){
        win = winscen[wasc](std::move(win));
    }
}


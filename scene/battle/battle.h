
GLFWwindowPtr battle(GLFWwindowPtr win){
    
    while(true){ 
        lxw_run(win.get());
    }

    return std::move(win);
}
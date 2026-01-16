#include "mes_pr.h"

GLFWwindowPtr main_menu(GLFWwindowPtr win){
    lx_image c;
    c.load("scene/main_menu/main_menu.txt");

    std::vector<mes_particle> a;
    a.resize(100); 
    mes_load_pr(a);

    float b = 0,d = 0;
    while(true) {
        lxw_run(win.get());
        b = lxw_gtime();

        lx_draw_image(c.images[1], 0, 0, lxw.zoom, lxw.zoom,0,0,0,1);
        
        if(b >= d )
        {
            d = b + 0.015;
            mes_update_pr(a);
        }

        mes_draw_pr(a,c.images[0]);

        if(lxj_button(1300,1490,440,540))
        {
            lx_draw_image(c.images[4], 0, 0, lxw.zoom, lxw.zoom,0,0,0,1);
            if(mouse.click == 1)
            {
                game.pointer = 1;
                break;
            }
        }
        if(lxj_button(1300,1490,540,640))
        {
            lx_draw_image(c.images[5], 0, 0, lxw.zoom, lxw.zoom,0,0,0,1);
            if(mouse.click == 1)
            {
                exit(0);
            }
        }
        if(lxj_button(1300,1490,640,740))
        {
            lx_draw_image(c.images[6], 0, 0, lxw.zoom, lxw.zoom,0,0,0,1);
            if(mouse.click == 1)
            {
                exit(0);
            }
        }
        if(lxj_button(1300,1490,740,840))
        {
            lx_draw_image(c.images[7], 0, 0, lxw.zoom, lxw.zoom,0,0,0,1);
            if(mouse.click == 1)
            {
                exit(0);
            }
        }
        lx_draw_image(c.images[2], 0, 0, lxw.zoom, lxw.zoom,0,0,0,1);
        lx_draw_image(c.images[3], 0, 0, lxw.zoom, lxw.zoom,0,0,0,1);
    }
    return std::move(win);
}



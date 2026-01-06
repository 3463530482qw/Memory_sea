#include "../../universal.h"

struct mes_particle{
    float x,y,vx,vy,dx,dy,size;
    int mt,mtd;
};
mes_particle pr(mes_particle a);

GLFWwindowPtr main_menu(GLFWwindowPtr win){
    GLint sizew[4];
    glGetIntegerv(GL_VIEWPORT, sizew);
    float sizex = sizew[2] / 1600.0f;
    //资源加载
    auto c = lx_load_image("scene/main_menu/main_menu.txt");
    mes_particle a[100];
    for(int i = 0; i < 100; i++)
    {
        a[i] = pr(a[i]);
    }
    float b = 0,d = 0;
    while(true) {
        lxw_run(win.get());
        lx_draw_image(c[1], 0, 0, sizex, sizex,0,0,0,1);
        b = lxw_gtime();
        if(b >= d )
        {
            
            d = b + 0.015;
            
            for(int i = 0; i < 100; i++)
            {
                a[i].x += a[i].dx;
                a[i].y += a[i].dy;
                a[i].mt--;
                if(a[i].mtd >= 0)
                {
                    a[i].size = a[i].size * 1.025;
                    a[i].mtd = a[i].mtd - 1;
                }
                if(a[i].mt <= 40 && a[i].mt >= 0)
                {
                    a[i].size = a[i].size * 0.975;
                }
                else if(a[i].mt <= 0)
                {
                    a[i] = pr(a[i]);
                }

            }
        }

        for(int i = 0; i < 100; i++) {
            for(int j = i + 1; j < 100; j++) {
                // 获取两个粒子的位置
                float x1 = a[i].x + a[i].size * 8 * sizex;
                float y1 = a[i].y + a[i].size * 8 * sizex;
                float x2 = a[j].x + a[j].size * 8 * sizex;
                float y2 = a[j].y + a[j].size * 8 * sizex;

                // 计算两个粒子间的距离
                float dx = x1 - x2;
                float dy = y1 - y2;
                float distance = sqrt(dx * dx + dy * dy);

                // 如果两点距离小于连线最大距离
                if(distance <= 250) {
                    // 计算连线透明度
                    float alpha = 0.5f;
                    if(distance >= 50) {
                        alpha = (250 - distance) / (distance + 200);
                    }
                    float asize = 2 - distance / 125 ; 
                    lx_draw_line(x1, y1, x2, y2, asize,alpha, 255,255,255);
                    
                }
            }
        }

        
        for(int i = 0; i < 100; i++)
        {
            lx_draw_image(c[0], a[i].x, a[i].y, a[i].size * sizex, a[i].size * sizex,0,0,0,0.5);
        }

        if(mousx >= 1300 * sizex && mousx <= 1490 * sizex && mousy >= 440 * sizex && mousy <= 540 * sizex)
        {
            lx_draw_image(c[4], 0, 0, sizex, sizex,0,0,0,1);
            if(mouclk)
            {
                wasc = 1;
                break;
            }
        }
        if(mousx >= 1300 * sizex && mousx <= 1490 * sizex && mousy >= 540 * sizex && mousy <= 640 * sizex)
        {
            lx_draw_image(c[5], 0, 0, sizex, sizex,0,0,0,1);
            if(mouclk)
            {
                exit(0);
            }
        }
        if(mousx >= 1300 * sizex && mousx <= 1490 * sizex && mousy >= 640 * sizex && mousy <= 740 * sizex)
        {
            lx_draw_image(c[6], 0, 0, sizex, sizex,0,0,0,1);
            if(mouclk)
            {
                exit(0);
            }
        }
        if(mousx >= 1300 * sizex && mousx <= 1490 * sizex && mousy >= 740 * sizex && mousy <= 840 * sizex)
        {
            lx_draw_image(c[7], 0, 0, sizex, sizex,0,0,0,1);
            if(mouclk)
            {
                exit(0);
            }
        }
        lx_draw_image(c[2], 0, 0, sizex, sizex,0,0,0,1);
        lx_draw_image(c[3], 0, 0, sizex, sizex,0,0,0,1);
    }
    cleanupTextures(c);
    return std::move(win);
}

mes_particle pr(mes_particle a)
{
    GLint b[4];
    glGetIntegerv(GL_VIEWPORT, b);
    float sizex = b[2] / 1600.0f;
    a.x = lxw_rand(0, b[2]);
    a.y = lxw_rand(0, b[3]);

    a.vx = (lxw_rand(0, 1) >= 0.5) ? 1 : -1;
    a.vy = (lxw_rand(0, 1) >= 0.5) ? 1 : -1;

    a.dx = (150 + lxw_rand(0, 250 * sizex)) * a.vx + a.x;
    a.dy = (150 + lxw_rand(0, 250 * sizex)) * a.vy + a.y;

    a.mt = lxw_rand(300, 400);
    a.size = lxw_rand(3, 4);

    a.size = a.size * 0.1;
    
    a.dx = (a.dx - a.x) / a.mt;
    a.dy = (a.dy - a.y) / a.mt;

    a.mt = a.mt << 1;
    a.mtd = 40;
    return a;
}

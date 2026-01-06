#include "../../universal.h"

struct chs_particle{
    float x,y,ph;
    int mt;
};
chs_particle chs_pr(chs_particle a);

int button(int a);

GLFWwindowPtr character_selection(GLFWwindowPtr win)
{
    GLint sizew[4];
    glGetIntegerv(GL_VIEWPORT, sizew);

    auto c = lx_load_image("scene/character_selection/character_selection.txt"); //场景构建图片
    chs_particle e[40];
    for(int i = 0;i < 40;i++)
    {
        e[i] = chs_pr(e[i]);
    }
    float width = sizew[2]; // 获取窗口宽度
    int height = sizew[3]; // 获取窗口高度
    float sizex = sizew[2] / 1600.0f; //缩放比
    width = width / 100.0f; //
    float ax[101];            //波浪效果顶点x
    float ay[101];            //波浪效果顶点y
    float adz[101];          //波浪效果压力偏移（y） 
    float adzjj[101];      //波浪效果顶点移动正负取向  
    float ayoff[101],ayoffy[101]; //波浪偏移量，y轴效果绘制点
    
    ax[0] = 0;
    ay[0] = 900 * 0.8 * sizex;
    float dz = 0;                   //效果压力偏移（临时）
    float dzjj = 1;                 //效果顶点移动正负取向（临时）

    auto butim = lx_load_image("scene/character_selection/butt.txt");
    int qbut = butim.size() / 2;             //剧本按钮数量
    int qbutaa = 0;             //解锁检查的检查
    int qbuta[qbut];             //解锁检查
    float mqbut = 0,zmqbut = 0,mzmqbut = 0; //剧本按钮数量位置偏移 
    int butclk = 0;                   //按钮点击检测
    float wmqbut = 0,wzmqbut = 0,wmzmqbut = 0; //剧本文本按钮数量位置偏移 

    qbutaa = button(qbutaa);


    //初始化波浪顶点位置
    for(int i = 1;i < 101;i++)
    {
        ax[i] = ax[i - 1] + width;
        ay[i] = ay[i - 1];
        ay[i] = ay[i] + dz;
        
    }

    for(int i = 0;i < 101;i++)
    {
        dz = dz + dzjj;
        adz[i] = dz;
        if(dz > 10)
        {
            dzjj = -1;
        }
        else if(dz < -10)
        {
            dzjj = 1;
        }
        adzjj[i] = dzjj;
    }
    //初始化波浪顶点位置偏移量
    for(int i = 0;i < 101;i++)
    {
        
        ayoff[i] = 0;
        ayoffy[i] = 0;
    }
    //初始化剧本按钮
    for(int i = 0;i < qbut;i++)
    {
        qbuta[i] = 0;
    }
    for(int i = 0;i < qbutaa; i++)
    {
        qbuta[i] = 1;
    }
    //计算剧本按钮最大偏移量
    mzmqbut = (qbut * 150) * sizex + 150 * sizex - (6 * 150) * sizex + 60 * sizex;
    //计算剧本文本按钮最大偏移量
    wmzmqbut = 0;


    float b = 0,d = 0; //时间控制变量,初始化为0避免随机值
    //粒子效果初始化
    for(int j = 0;j < 1000;j++)
    {
        for(int i = 0;i < 40;i++)
        {
            e[i].y = e[i].y - 1;
            e[i].ph = e[i].ph - 0.01;
            e[i].mt = e[i].mt - 1;
            if(e[i].mt < 0)
            {
                e[i] = chs_pr(e[i]);
            }
        }
    }
    
    while(1)
    {
        lxw_run(win.get());
        b = lxw_gtime();
        lx_draw_image(c[1],0,0,sizex,sizex);
        if(b > d)
        {
            //粒子效果更新
            for(int i = 0;i < 40;i++)
            {
                e[i].y = e[i].y - 1;
                e[i].ph = e[i].ph - 0.01;
                e[i].mt = e[i].mt - 1;
                if(e[i].mt < 0)
                {
                    e[i] = chs_pr(e[i]);
                }
            }
            d = b + 0.015;
            //波浪物理（存疑）效果更新
            if(mouclk)
            {
                for(int i = 0;i < 100;i++)
                {
                    if(ax[i] >= mousx - 100 && ax[i] <= mousx + 100 && mousy >= 620 * sizex && mousy <= 820 * sizex)
                    {
                        if(ayoff[i] <= 100)
                        {
                            ayoff[i] = ayoff[i] + 10;
                        }
                        
                    }
                }
            }
            //波浪效果更新
            for(int i = 0;i < 101;i++)
            {
                ay[i] = ay[i] + adz[i] * 0.1;
                adz[i] = adz[i] + adzjj[i];
                if(adz[i] > 10 && adzjj[i] > 0)
                {
                    adzjj[i] = -1;
                }
                else if(adz[i] < -10 && adzjj[i] < 0)
                {
                    adzjj[i] = 1;
                }
            }
            ayoff[0] = ((ayoff[99] + ayoff[100] + ayoff[0] + ayoff[1] + ayoff[2]) / 5) * 0.99;
            ayoff[1] = ((ayoff[100] + ayoff[0] + ayoff[1] + ayoff[2] + ayoff[3]) / 5) * 0.99;
            ayoff[99] = ((ayoff[97] + ayoff[98] + ayoff[99] + ayoff[100] + ayoff[0]) / 5) * 0.99;
            ayoff[100] = ((ayoff[98] + ayoff[99] + ayoff[100] + ayoff[0] + ayoff[1]) / 5) * 0.99;
            ayoffy[0] = ay[0] + ayoff[0];
            ayoffy[1] = ay[1] + ayoff[1];
            ayoffy[99] = ay[99] + ayoff[99];
            ayoffy[100] = ay[100] + ayoff[100];
            for(int i = 2;i < 99;i++)
            {
                ayoff[i] = ((ayoff[i] + ayoff[i + 1]+ ayoff[i + 2] + ayoff[i - 1] + ayoff[i - 2]) / 5) * 0.99;
                ayoffy[i] = ay[i] + ayoff[i];
            }
        }

        //滚动更新
        if(mousx < 1075 * sizex && mousx > 625 * sizex && mousy > 150 * sizex && mousy < 875 * sizex)
        {
            if(moucr)
            {
                mqbut = mqbut + -(moucr * 5);
            }
        }
        if(mousx < 1580 * sizex && mousx > 1130 * sizex && mousy > 150 * sizex && mousy < 875 * sizex)
        {
            if(moucr)
            {
                wmqbut = wmqbut + -(moucr * 5);
            }
            moucr = 0;
        }
        else
        {
            moucr = 0;
        }
        wmqbut = wmqbut * 0.98;
        wzmqbut = wzmqbut + wmqbut;
        mqbut = mqbut * 0.98;
        zmqbut = zmqbut + mqbut;
        if(zmqbut > mzmqbut)
        {
            zmqbut = zmqbut * 0.98;
            mqbut = -(mqbut * 0.1);
        }
        if(zmqbut < 0)
        {
            zmqbut = zmqbut * 0.98;
        }
        if(wzmqbut > wmzmqbut)
        {
            wzmqbut = wzmqbut * 0.98;
            wmqbut = -(wmqbut * 0.1);
        }
        if(wzmqbut < 0)
        {
            wzmqbut = wzmqbut * 0.98;
        }


        //绘制粒子效果
        for(int i = 0;i < 40;i++)
        {
            lx_draw_image(c[0],e[i].x,e[i].y,1,1,0, 0,0, e[i].ph);
        }
        //波浪效果绘制
        for(int i = 0;i < 100;i++)
        {
            lx_draw_line(ax[i],ayoffy[i] + 100 * sizex,ax[i + 1],ayoffy[i + 1] + 100 * sizex,200 * sizex,0.25);
            lx_draw_line(ax[i],ayoffy[i] - 6,ax[i + 1],ayoffy[i + 1] - 6,13,0.25);
            lx_draw_line(ax[i],ayoffy[i] - 3,ax[i + 1],ayoffy[i + 1] - 3,7,0.25);
            lx_draw_line(ax[i],ayoffy[i] - 1,ax[i + 1],ayoffy[i + 1] - 1,3,0.25);
            lx_draw_line(ax[i],ayoffy[i],ax[i + 1],ayoffy[i + 1]);
        }
        //返回主菜单按钮
        if(mousx < 120 * sizex && mousy < 80 * sizex)
        {
            lx_draw_image(c[3],0,0,sizex,sizex);
            if(mouclk)
            {
                wasc = 0;
                break;
            }
        }
        //左侧选择栏更新绘制
        lx_draw_image(c[2],0,0,sizex,sizex);
        lx_draw_image(c[4],0,0,sizex,sizex);
        for(int i = 0;i < qbut;i++)
        {
            lx_draw_image(c[8],625 * sizex,150 * sizex + (i * 150) * sizex - zmqbut,sizex,sizex);
            if(qbuta[i] == 0)
            {
                lx_draw_image(c[9],625 * sizex,150 * sizex + (i * 150) * sizex - zmqbut,sizex,sizex);
            }
            if(qbuta[i] == 1)
            {
                if(mouclk)
                {
                    lx_draw_image(butim[i * 2],625 * sizex,150 * sizex + (i * 150) * sizex - zmqbut,sizex,sizex);
                    for(int j = 0; j < qbut; j++)
                    {
                        if(mousx < 1075 * sizex && mousx > 625 * sizex && mousy > 150 * sizex && mousy > 150 * sizex + (j * 150) * sizex - zmqbut && mousy < 150 * sizex + (j * 150) * sizex - zmqbut + 150 * sizex )
                        {
                            butclk = j;
                        }
                    }
                    
                    if(butclk == i)
                    {
                        lx_draw_image(c[10],625 * sizex,150 * sizex + (i * 150) * sizex - zmqbut,sizex,sizex);
                        lx_draw_image(butim[i * 2 + 1],625 * sizex,150 * sizex + (i * 150) * sizex - zmqbut,sizex,sizex);
                    }
                    
                }
                else
                {
                    lx_draw_image(butim[i * 2],625 * sizex,150 * sizex + (i * 150) * sizex - zmqbut,sizex,sizex);
                    if(butclk == i)
                    {
                        lx_draw_image(c[10],625 * sizex,150 * sizex + (i * 150) * sizex - zmqbut,sizex,sizex);
                        lx_draw_image(butim[i * 2 + 1],625 * sizex,150 * sizex + (i * 150) * sizex - zmqbut,sizex,sizex);
                    }
                }
            }
        }
        lx_draw_image(c[5],0,0,sizex,sizex);
        
        if(mousx > 1190 * sizex && mousx < 1520 * sizex && mousy < 110 * sizex && mousy > 30 * sizex)
        {
            lx_draw_image(c[6],0,0,sizex,sizex);
            if(mouclk)
            {

            }
        }
        
        lx_draw_image(c[7],0,0,sizex,sizex);
    }
    cleanupTextures(butim);
    cleanupTextures(c);
    return std::move(win);
}

chs_particle chs_pr(chs_particle a)
{
    GLint b[4];
    glGetIntegerv(GL_VIEWPORT, b);
    float sizex = b[2] / 1600.0f;
    a.x = lxw_rand(0, b[2]);
    a.y = b[3];
    a.ph = lxw_rand(10, 13) * 0.1;
    a.mt = lxw_rand(130, 180);
    return a;
}

int button(int a)
{
    std::ifstream button("D:/Memory_sea/cfile_temary/character_selection_butt/butt.txt");

    if(!button.is_open())
    {
        std::ifstream in("D:/Memory_sea/cfile_inil/character_selection_butt/butt.txt");
        std::ofstream out("D:/Memory_sea/cfile_temary/character_selection_butt/butt.txt");
        out << in.rdbuf();
        button.open("D:/Memory_sea/cfile_temary/character_selection_butt/butt.txt");
    }
    button >> a;

    return a;
}
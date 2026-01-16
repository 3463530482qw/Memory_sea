struct chs_particle{
    float x,y,ph;
    int mt;
};
chs_particle chs_pr(chs_particle a);

int button(int a);

GLFWwindowPtr character_selection(GLFWwindowPtr win)
{
    lx_image c,butim,qbuotim;
    c.load("scene/character_selection/character_selection.txt"); //场景构建图片
    chs_particle e[40];
    for(int i = 0;i < 40;i++)
    {
        e[i] = chs_pr(e[i]);
    }
    float width = lxw.w; // 获取窗口宽度
    int height = lxw.h; // 获取窗口高度
    width = width / 100.0f; //
    float ax[101];            //波浪效果顶点x
    float ay[101];            //波浪效果顶点y
    float adz[101];          //波浪效果压力偏移（y） 
    float adzjj[101];      //波浪效果顶点移动正负取向  
    float ayoff[101],ayoffy[101]; //波浪偏移量，y轴效果绘制点
    
    ax[0] = 0;
    ay[0] = 900 * 0.8 * lxw.zoom;
    float dz = 0;                   //效果压力偏移（临时）
    float dzjj = 1;                 //效果顶点移动正负取向（临时）

    butim.load("scene/character_selection/butt.txt");
    int qbut = butim.images.size() / 2;             //剧本按钮数量
    qbuotim.load("scene/character_selection/buotim.txt");                   //剧本文本
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
    mzmqbut = (qbut * 150) * lxw.zoom + 150 * lxw.zoom - (6 * 150) * lxw.zoom + 60 * lxw.zoom;
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
        lx_draw_image(c.images[1],0,0,lxw.zoom,lxw.zoom);
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
            if(mouse.click == 1)
            {
                for(int i = 0;i < 100;i++)
                {
                    if(ax[i] >= mouse.x - 100 * lxw.zoom && ax[i] <= mouse.x + 100 * lxw.zoom && mouse.y >= 620 * lxw.zoom && mouse.y <= 820 * lxw.zoom)
                    {
                        if(ayoff[i] <= 100 * lxw.zoom)
                        {
                            ayoff[i] = ayoff[i] + 8 * lxw.zoom;
                        }
                        
                    }
                }
            }
            //波浪效果更新
            for(int i = 0;i < 101;i++)
            {
                ay[i] = ay[i] + (adz[i] * 0.1) * lxw.zoom;
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
        if(lxj_button(625,1075,150,875))
        {
            if(mouse.scroll)
            {
                mqbut = mqbut + -(mouse.scroll * 5);
            }
        }
        if(lxj_button(1130,1580,150,875))
        {
            if(mouse.scroll)
            {
                wmqbut = wmqbut + -(mouse.scroll * 5);
            }
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
            lx_draw_image(c.images[0],e[i].x,e[i].y,lxw.zoom,lxw.zoom,0, 0,0, e[i].ph);
        }
        //波浪效果绘制
        for(int i = 0;i < 100;i++)
        {
            lx_draw_line(ax[i],ayoffy[i] + 100 * lxw.zoom,ax[i + 1],ayoffy[i + 1] + 100 * lxw.zoom,200 * lxw.zoom,0.25);
            lx_draw_line(ax[i],ayoffy[i] - 6,ax[i + 1],ayoffy[i + 1] - 6,13,0.25);
            lx_draw_line(ax[i],ayoffy[i] - 3,ax[i + 1],ayoffy[i + 1] - 3,7,0.25);
            lx_draw_line(ax[i],ayoffy[i] - 1,ax[i + 1],ayoffy[i + 1] - 1,3,0.25);
            lx_draw_line(ax[i],ayoffy[i],ax[i + 1],ayoffy[i + 1]);
        }
        //返回主菜单按钮
        if(lxj_button(0,120,0,80))
        {
            lx_draw_image(c.images[3],0,0,lxw.zoom,lxw.zoom);
            if(mouse.click == 1)
            {
                game.pointer = 0;
                break;
            }
        }
        //左侧选择栏更新绘制
        lx_draw_image(c.images[2],0,0,lxw.zoom,lxw.zoom);
        lx_draw_image(c.images[4],0,0,lxw.zoom,lxw.zoom);
        for(int i = 0;i < qbut;i++)
        {
            lx_draw_image(c.images[8],625 * lxw.zoom,150 * lxw.zoom + (i * 150) * lxw.zoom - zmqbut,lxw.zoom,lxw.zoom);
            if(qbuta[i] == 0)
            {
                lx_draw_image(c.images[9],625 * lxw.zoom,150 * lxw.zoom + (i * 150) * lxw.zoom - zmqbut,lxw.zoom,lxw.zoom);
            }
            if(qbuta[i] == 1)
            {
                if(mouse.click == 1)
                {
                    lx_draw_image(butim.images[i * 2],625 * lxw.zoom,150 * lxw.zoom + (i * 150) * lxw.zoom - zmqbut,lxw.zoom,lxw.zoom);
                    for(int j = 0; j < qbut; j++)
                    {
                        if(mouse.x < 1075 * lxw.zoom && mouse.x > 625 * lxw.zoom && mouse.y > 150 * lxw.zoom && mouse.y > 150 * lxw.zoom + (j * 150) * lxw.zoom - zmqbut && mouse.y < 150 * lxw.zoom + (j * 150) * lxw.zoom - zmqbut + 150 * lxw.zoom )
                        {
                            butclk = j;
                        }
                    }
                    
                    if(butclk == i)
                    {
                        lx_draw_image(c.images[10],625 * lxw.zoom,150 * lxw.zoom + (i * 150) * lxw.zoom - zmqbut,lxw.zoom,lxw.zoom);
                        lx_draw_image(butim.images[i * 2 + 1],625 * lxw.zoom,150 * lxw.zoom + (i * 150) * lxw.zoom - zmqbut,lxw.zoom,lxw.zoom);
                        lx_draw_image(qbuotim.images[i],1130 * lxw.zoom,150 * lxw.zoom + (i * 150) * lxw.zoom - wzmqbut,lxw.zoom,lxw.zoom);
                    }
                    
                }
                else
                {
                    lx_draw_image(butim.images[i * 2],625 * lxw.zoom,150 * lxw.zoom + (i * 150) * lxw.zoom - zmqbut,lxw.zoom,lxw.zoom);
                    if(butclk == i)
                    {
                        lx_draw_image(c.images[10],625 * lxw.zoom,150 * lxw.zoom + (i * 150) * lxw.zoom - zmqbut,lxw.zoom,lxw.zoom);
                        lx_draw_image(butim.images[i * 2 + 1],625 * lxw.zoom,150 * lxw.zoom + (i * 150) * lxw.zoom - zmqbut,lxw.zoom,lxw.zoom);
                        lx_draw_image(qbuotim.images[i],1130 * lxw.zoom,150 * lxw.zoom + (i * 150) * lxw.zoom - wzmqbut,lxw.zoom,lxw.zoom);
                    }
                }
            }
        }
        lx_draw_image(c.images[5],0,0,lxw.zoom,lxw.zoom);
        
        if(lxj_button(1190,1520,110,30))
        {
            lx_draw_image(c.images[6],0,0,lxw.zoom,lxw.zoom);
            if(mouse.click == 1)
            {
                std::ofstream add("cfile_temary/character_selection_butt/butt.txt");
                add << butclk;
                add.close();

                game.pointer = 2;
                break;
            }
        }
        
        lx_draw_image(c.images[7],0,0,lxw.zoom,lxw.zoom);
    }
    return std::move(win);
}

chs_particle chs_pr(chs_particle a)
{
    a.x = lxw_rand(0, lxw.w);
    a.y = lxw.h;
    a.ph = lxw_rand(6, 9) * 0.1 * lxw.zoom;
    a.mt = lxw_rand(80, 110) * lxw.zoom;
    return a;
}

int button(int a)
{
    std::ifstream button("cfile_temary/character_selection_butt/butt.txt");

    if(!button.is_open())
    {
        std::ifstream in("cfile_inil/character_selection_butt/butt.txt");
        std::ofstream out("cfile_temary/character_selection_butt/butt.txt");
        out << in.rdbuf();
        button.open("cfile_temary/character_selection_butt/butt.txt");
    }
    button >> a;

    return a;
}
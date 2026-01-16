struct mes_particle{
    float x,y,vx,vy,dx,dy,size;
    int mt,mtd;
};

void mes_pr(mes_particle& a)
{
    a.x = lxw_rand(0, lxw.w);
    a.y = lxw_rand(0, lxw.h);

    a.vx = (lxw_rand(0, 1) >= 0.5) ? 1 : -1;
    a.vy = (lxw_rand(0, 1) >= 0.5) ? 1 : -1;

    a.mt = lxw_rand(300, 400);

    a.dx = (((125 * lxw.zoom + lxw_rand(0, 200 * lxw.zoom)) * a.vx + a.x) - a.x) / a.mt;
    a.dy = (((125 * lxw.zoom + lxw_rand(0, 200 * lxw.zoom)) * a.vy + a.y) - a.y) / a.mt;

    
    a.size = lxw_rand(2.5 * lxw.zoom, 3.5 * lxw.zoom) * 0.1;
    a.mt = a.mt << 1;
    a.mtd = 40;
}

std::vector<mes_particle> mes_load_pr(std::vector<mes_particle>& a) 
{
    std::for_each(a.begin(), a.end(), mes_pr); 
    return a;
}

void mes_update_pr(std::vector<mes_particle>& a)
{
    for(size_t i = 0; i < a.size(); i++)
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
            mes_pr(a[i]);
        }
    }
}

void mes_draw_pr(std::vector<mes_particle>& a, GLuint c)
{
    size_t count = a.size();

    for(size_t i = 0; i < count; i++) {
        for(size_t j = i + 1; j < count; j++) {
            float x1 = a[i].x + a[i].size * 8 * lxw.zoom;
            float y1 = a[i].y + a[i].size * 8 * lxw.zoom;
            float x2 = a[j].x + a[j].size * 8 * lxw.zoom;
            float y2 = a[j].y + a[j].size * 8 * lxw.zoom;

            float dx = x1 - x2;
            float dy = y1 - y2;
            float dist_sq = dx * dx + dy * dy;
            
            float max_dist_sq = 62500.0f * lxw.zoom;

            if(dist_sq <= max_dist_sq) {
                float distance = sqrt(dist_sq);
                
                float alpha = 0.5f;
                if(distance >= 50.0f * lxw.zoom) {
                    alpha = (250.0f * lxw.zoom - distance) / (distance + 200.0f * lxw.zoom);
                }
                
                if(alpha < 0) alpha = 0;

                float asize = 2.0f * lxw.zoom - distance / (125.0f * lxw.zoom); 
                if(asize < 0) asize = 0;

                lx_draw_line(x1, y1, x2, y2, asize, alpha, 255, 255, 255);
            }
        }
    }

    for(size_t i = 0; i < count; i++)
    {
        lx_draw_image(c, a[i].x, a[i].y, a[i].size * lxw.zoom, a[i].size * lxw.zoom, 0, 0, 0, 0.5);
    }
}
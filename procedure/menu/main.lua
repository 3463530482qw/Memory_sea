-- LÖVE 2D 游戏引擎主循环函数

-- 游戏更新函数，每帧调用一次
function love.update(dt)
    mouse_update(dt)  -- 调用鼠标状态更新函数
end

-- 游戏绘制函数，每帧调用一次
function love.draw()
    -- 绘制环境背景图片
    for i, _ in ipairs(Environmental_pictures) do
        love.graphics.draw(Environmental_pictures[i], 0, 0, 0, Zoom_Ratio, Zoom_Ratio)
    end
    
    -- 鼠标绘制
    local x, y = love.mouse.getPosition()  -- 获取当前鼠标位置
    
    -- 绘制鼠标光标的第一层（基础层）
    -- 参数：图像, x坐标, y坐标, 旋转角度, x缩放, y缩放, x偏移, y偏移
    love.graphics.draw(mouse[1], x, y, -Environmental_variable[1], Zoom_Ratio, Zoom_Ratio, mouse[1]:getWidth() / 2, mouse[1]:getHeight() / 2)
    
    -- 绘制鼠标光标的第二层（动态效果层）
    -- 使用动态缩放和旋转效果
    love.graphics.draw(mouse[2], x, y, Environmental_variable[1], Zoom_Ratio+Environmental_variable[4], Zoom_Ratio+Environmental_variable[4], mouse[2]:getWidth() / 2, mouse[2]:getHeight() / 2)
end

-- 鼠标按下事件处理函数
function love.mousepressed(x, y, button, istouch, presses)
    -- 如果当前选中第一个菜单项
    if Environmental_variable[2] == 1 then
        scene_switching = 3     -- 设置场景切换标志
        scenario[1]()          -- 执行第一个场景函数
    end
end

-- 鼠标状态更新函数
function mouse_update(dt)
    local x, y = love.mouse.getPosition()  -- 获取当前鼠标位置
    
    -- 检测鼠标是否在第一个菜单按钮区域 (667-932, 555-617)
    if x > 667 * Zoom_Ratio and x < 932 * Zoom_Ratio and y > 555 * Zoom_Ratio and y < 617 * Zoom_Ratio then
        Environmental_variable[2] = 1  -- 设置当前选中的菜单项为1
        -- 鼠标悬停动画效果
        if Environmental_variable[3] < dt * 2 then
            Environmental_variable[3] = Environmental_variable[3] + dt * 0.015  -- 增加旋转速度
        elseif Environmental_variable[4] < 0.2 then
            Environmental_variable[4] = Environmental_variable[4] + dt * 0.15   -- 增加缩放效果
        end
        
    -- 检测鼠标是否在第二个菜单按钮区域 (667-932, 655-717)
    elseif x > 667 * Zoom_Ratio and x < 932 * Zoom_Ratio and y > 655 * Zoom_Ratio and y < 717 * Zoom_Ratio then
        Environmental_variable[2] = 2  -- 设置当前选中的菜单项为2
        -- 同样的悬停动画效果
        if Environmental_variable[3] < dt * 2 then
            Environmental_variable[3] = Environmental_variable[3] + dt * 0.015
        elseif Environmental_variable[4] < 0.2 then
            Environmental_variable[4] = Environmental_variable[4] + dt * 0.15
        end
        
    -- 检测鼠标是否在第三个菜单按钮区域 (667-932, 755-817)
    elseif x > 667 * Zoom_Ratio and x < 932 * Zoom_Ratio and y > 755 * Zoom_Ratio and y < 817 * Zoom_Ratio then
        Environmental_variable[2] = 3  -- 设置当前选中的菜单项为3
        -- 同样的悬停动画效果
        if Environmental_variable[3] < dt * 2 then
            Environmental_variable[3] = Environmental_variable[3] + dt * 0.015
        elseif Environmental_variable[4] < 0.2 then
            Environmental_variable[4] = Environmental_variable[4] + dt * 0.15
        end
        
    -- 检测鼠标是否在第四个菜单按钮区域 (667-932, 855-917)
    elseif x > 667 * Zoom_Ratio and x < 932 * Zoom_Ratio and y > 855 * Zoom_Ratio and y < 917 * Zoom_Ratio then
        Environmental_variable[2] = 4  -- 设置当前选中的菜单项为4
        -- 同样的悬停动画效果
        if Environmental_variable[3] < dt * 2 then
            Environmental_variable[3] = Environmental_variable[3] + dt * 0.015
        elseif Environmental_variable[4] < 0.2 then
            Environmental_variable[4] = Environmental_variable[4] + dt * 0.15
        end
        
    -- 鼠标不在任何菜单按钮区域时
    else
        -- 逐渐减少旋转速度
        if Environmental_variable[3] > 0 then
            Environmental_variable[3] = Environmental_variable[3] - dt * 0.003
        end
        -- 逐渐减少缩放效果
        if Environmental_variable[4] > 0 then
            Environmental_variable[4] = Environmental_variable[4] - dt * 0.15
        end
    end
    
    -- 更新鼠标光标旋转角度
    Environmental_variable[1] = Environmental_variable[1] + dt + Environmental_variable[3]
end

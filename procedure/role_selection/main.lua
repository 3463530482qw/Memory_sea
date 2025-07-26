function love.update(dt)
    Environmental_variable[1] = Environmental_variable[1] + dt
    if love.timer.getTime() > Environmental_variable[6] then
        b()
        Environmental_variable[6] = love.timer.getTime() + 0.01
        for i = #Environmental_variable[5], 1, -1 do
            local rect = Environmental_variable[5][i]
            rect.y = rect.y + 1
            local wave = math.sin(Environmental_variable[1] * 3 + rect.y * 0.02) * 10
            local noiseValue = math.sin(Environmental_variable[1] * 0.7 + rect.y * 0.001) * 0.5
            rect.rx = wave + noiseValue
            rect.l = rect.l - 1
            
            if rect.l <= 0 then
                table.remove(Environmental_variable[5], i)
            end
        end
        c()
        for i = #Environmental_variable[9], 1, -1 do
            local rect = Environmental_variable[9][i]
            rect.y = rect.y + math.random(0, 2) - 1
            rect.x = rect.x + math.random(0, 2) - 1
            rect.z = rect.z + dt + 0.1
            rect.l = rect.l - 1
            if rect.l <= 0 then
                table.remove(Environmental_variable[9], i)
            end
        end
    end
end

function love.draw()
    a()

     -- 鼠标绘制
    local x, y = love.mouse.getPosition()
    love.graphics.draw(mouse[1], x, y, -Environmental_variable[1], Zoom_Ratio, Zoom_Ratio, mouse[1]:getWidth() / 2, mouse[1]:getHeight() / 2)
    love.graphics.draw(mouse[2], x, y, Environmental_variable[1], Zoom_Ratio+Environmental_variable[4], Zoom_Ratio+Environmental_variable[4], mouse[2]:getWidth() / 2, mouse[2]:getHeight() / 2)
end

function a()
    -- 绘制背景
    love.graphics.draw(Environmental_pictures[1], 0, 0, 0, Zoom_Ratio, Zoom_Ratio)
    for _, ev in ipairs(Environmental_variable[5]) do
        if Environmental_variable[7] == 1 then
            love.graphics.setColor(0.75, 0.375, 0.375, 0.5)
        else
            love.graphics.setColor(0.375, 0.5625, 0.75, 0.5)
        end
        love.graphics.rectangle("fill", 0, (ev.y * 2) * Zoom_Ratio, (ev.x + ev.rx) * Zoom_Ratio, 2 * Zoom_Ratio)
        if Environmental_variable[8] == 1 then
            love.graphics.setColor(0.75, 0.375, 0.375, 0.5)
        else
            love.graphics.setColor(0.375, 0.5625, 0.75, 0.5)
        end
        love.graphics.rectangle("fill", 1300 * Zoom_Ratio, (ev.y * 2) * Zoom_Ratio, -((ev.x + ev.rx) * Zoom_Ratio), 2 * Zoom_Ratio)
        love.graphics.setColor(1, 1, 1, 1)
    end

    for _, eva in ipairs(Environmental_variable[9]) do
        if eva.x > 90 then
            eva.x = 90
        end
        if eva.x < 0 then
            eva.x = 0
        end
        love.graphics.draw(Environmental_pictures[7], eva.x * Zoom_Ratio, eva.y * Zoom_Ratio, eva.z, Zoom_Ratio, Zoom_Ratio)
        love.graphics.draw(Environmental_pictures[7], (1300 - eva.x) * Zoom_Ratio, eva.y * Zoom_Ratio, eva.z, Zoom_Ratio, Zoom_Ratio)
    end
    if Environmental_variable[10] == 1 then
        love.graphics.draw(Environmental_pictures[8], 0, 0, 0, Zoom_Ratio, Zoom_Ratio)
        love.graphics.draw(Environmental_pictures[3], 0, 0, 0, Zoom_Ratio, Zoom_Ratio)
        love.graphics.draw(Environmental_pictures[4], 0, 0, 0, Zoom_Ratio, Zoom_Ratio)
    elseif Environmental_variable[10] == 2 then
        love.graphics.draw(Environmental_pictures[3], 0, 0, 0, Zoom_Ratio, Zoom_Ratio)
        love.graphics.draw(Environmental_pictures[5], 0, 0, 0, Zoom_Ratio, Zoom_Ratio)
    elseif Environmental_variable[10] == 3 then
        love.graphics.draw(Environmental_pictures[2], 0, 0, 0, Zoom_Ratio, Zoom_Ratio)
        love.graphics.draw(Environmental_pictures[4], 0, 0, 0, Zoom_Ratio, Zoom_Ratio)
    elseif Environmental_variable[10] == 4 then
        love.graphics.draw(Environmental_pictures[2], 0, 0, 0, Zoom_Ratio, Zoom_Ratio)
        love.graphics.draw(Environmental_pictures[5], 0, 0, 0, Zoom_Ratio, Zoom_Ratio)
    end
    love.graphics.draw(Environmental_pictures[6], 0, 0, 0, Zoom_Ratio, Zoom_Ratio)
end

function b()
    table.insert(Environmental_variable[5], { x = 90, y = 0, l = 1000 * Zoom_Ratio , rx = 0})
end

function c()
    table.insert(Environmental_variable[9], { x = love.math.random(0, 70), y = love.math.random(0, 1000), l = 100 , z = love.math.random(0, 1)})
end
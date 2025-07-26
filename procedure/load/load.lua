require("save_procedure/" .. scene_switching .. "/load_quantity") -- 初始化的初始化
local load_quantity, load_quantity_variable, load_quantity_pictures, i, font = load_quantity() -- 我没意见
love.graphics.setFont(font[1]) -- 字体设置
Environmental_variable = {} -- 环境变量
Environmental_pictures = {} -- 环境图片

scene_switching_two = scene_switching --设置为当前场景

-- 创建文件迭代器（在循环外部）
local var_iter = love.filesystem.lines("save_procedure/" .. scene_switching .. "/Environmental_variable.txt")
local pic_iter = love.filesystem.lines("save_procedure/" .. scene_switching .. "/Environmental_pictures.txt")
-- 
function love.update(dt)
    Load_environmental()
    if i >= load_quantity then
        scenario[scene_switching]()
    end
    Environmental_variable[1] = dt
end


function love.draw()
    local a = math.floor((i / load_quantity + 1) * 100) -- 计算百分比
    love.graphics.print(a .. "%", 755 * Zoom_Ratio, 785 * Zoom_Ratio, 0, 1, 1, 0.5, 0.5) --绘制百分比

    -- 鼠标绘制
    local x, y = love.mouse.getPosition()
    love.graphics.draw(mouse[1], x, y, 0, Zoom_Ratio, Zoom_Ratio, mouse[1]:getWidth() / 2, mouse[1]:getHeight() / 2)
    love.graphics.draw(mouse[2], x, y, Environmental_variable[1], Zoom_Ratio, Zoom_Ratio, mouse[2]:getWidth() / 2, mouse[2]:getHeight() / 2)
end

function Load_environmental()
    local a, b = 0, 0
    if i <= load_quantity_variable then
        local variable = var_iter()
        -- 检查是否是表的标记
        if variable == "{}" then
            -- 如果是表的标记，则插入一个空表
            table.insert(Environmental_variable, {})
        elseif variable:sub(1, 1) == "{" then
            -- 如果以{开头，尝试将其作为表加载
            local success, result = pcall(function()
                return loadstring("return " .. variable)()
            end)
            if success then
                table.insert(Environmental_variable, result)
            else
                -- 如果加载失败，插入空表
                table.insert(Environmental_variable, {})
                print("Failed to load table: " .. variable)
            end
        else
            -- 否则，尝试将其转换为数字
            table.insert(Environmental_variable, tonumber(variable))
        end
    end
    if i <= load_quantity_pictures then
        local pictures = pic_iter()
        --添加图片
        Environmental_pictures[i] = love.graphics.newImage(pictures)
    end
    i = i + 1
end
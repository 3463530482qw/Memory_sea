function love.load()
    love.mouse.setVisible(false) -- 隐藏系统光标
    -- 光标构筑
    mouse = {}
    mouse[1] = love.graphics.newImage("image/Scene_for_play/Menu/mouse_1.png")
    mouse[2] = love.graphics.newImage("image/Scene_for_play/Menu/mouse_2.png")
    
    love.graphics.setDefaultFilter("nearest", "nearest") -- 设置渲染
    love.window.setVSync(1)  -- 根据实际刷新率锁定帧率
    
    scenario = {}
    scene_switching = 2
    scene_switching_two = 1
    scenario[1] = love.filesystem.load("procedure/load/load.lua") 
    scenario[1]()
end

function love.update(dt)

end 

function love.draw()

end

function love.resize(w, h)  --窗口大小改变
    local dx, dy, _ = love.window.getPosition( )  --获取窗口位置
    local _, DHM = love.window.getDesktopDimensions()  --获取桌面高度
    if Current_Window_Width ~= w then  --如果窗口宽度改变
        DHM = DHM * 0.9 / 5 * 8  --限制窗口宽度
        if DHM <= w then  --如果窗口改变后的宽度大于等于宽度限制
            Current_Window_Width = math.floor( DHM / 8 ) * 8  --调整当前窗口宽度为改变后宽度最接近比例的宽度
            Current_Window_Height = Current_Window_Width / 8 * 5  --调整当前窗口高度为改变后高度最接近比例的高度
            love.window.updateMode(Current_Window_Width - 8, Current_Window_Height - 5, {resizable = true})  --调整窗口大小 防止窗口改变后比例错误
            Zoom_Ratio = (Current_Window_Height - 5) / 1000  --调整缩放比例   
        else  --如果窗口改变后的宽度小于宽度限制
            Current_Window_Width = math.floor( w / 8 ) * 8  --调整当前窗口宽度为改变后宽度最接近比例的宽度
            Current_Window_Height = Current_Window_Width / 8 * 5  --调整当前窗口高度为改变后高度最接近比例的高度
            love.window.updateMode(Current_Window_Width + 8, Current_Window_Height + 5, {resizable = true, x = dx , y = dy})  --调整窗口大小 防止updateMode使用桌面大小为窗口大小
            Zoom_Ratio = (Current_Window_Height + 5) / 1000  --调整缩放比例
        end
    else --如果窗口高度改变
            DHM = DHM * 0.9  --限制窗口高度
        if DHM <= h then  --如果窗口改变后的高度大于等于高度限制
            Current_Window_Height = math.floor( DHM / 5 ) * 5  --调整当前窗口高度为改变后高度最接近比例的高度
            Current_Window_Width = Current_Window_Height / 5 * 8  --调整当前窗口宽度为改变后宽度最接近比例的宽度
            love.window.updateMode(Current_Window_Width - 8, Current_Window_Height - 5, {resizable = true, x = dx , y = dy})  --调整窗口大小 防止窗口改变后比例错误
            Zoom_Ratio = (Current_Window_Height - 5) / 1000  --调整缩放比例
        else  --如果窗口改变后的高度小于高度限制
            Current_Window_Height = math.floor( h / 5 ) * 5  --调整当前窗口高度为改变后高度最接近比例的高度
            Current_Window_Width = Current_Window_Height / 5 * 8  --调整当前窗口宽度为改变后宽度最接近比例的宽度
            love.window.updateMode(Current_Window_Width + 8, Current_Window_Height + 5, {resizable = true, x = dx , y = dy})  --调整窗口大小 防止updateMode使用桌面大小为窗口大小
            Zoom_Ratio = (Current_Window_Height + 5) / 1000  --调整缩放比例
        end
    end
    require("save_procedure/" .. scene_switching .. "/load_quantity")
    local _, _, _, _, font = load_quantity()
    love.graphics.setFont(font[1])
end

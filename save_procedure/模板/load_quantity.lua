function load_quantity()
    local load_quantity_variable = 4 --变量数量
    local load_quantity_pictures = 0 --图片数量
    local load_quantity = load_quantity_pictures + load_quantity_variable --加载数量
    scenario[scene_switching] = love.filesystem.load("路径")  --加载指定模块
    local i = 1 --加载计数变量
    local font = {} --字体
    font[1] = love.graphics.newFont("font/LXGWWenKaiLite-Light.ttf", 30*Zoom_Ratio) --默认字体
    return load_quantity, load_quantity_variable, load_quantity_pictures, i, font
end
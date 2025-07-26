function load_quantity()
    local load_quantity_variable = 4
    local load_quantity_pictures = 4
    local load_quantity = load_quantity_pictures + load_quantity_variable
    scenario[scene_switching] = love.filesystem.load("procedure/menu/main.lua") 
    local i = 1
    local font = {}
    font[1] = love.graphics.newFont("font/LXGWWenKaiLite-Light.ttf", 30*Zoom_Ratio)
    return load_quantity, load_quantity_variable, load_quantity_pictures, i, font
end
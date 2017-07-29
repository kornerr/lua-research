-- Just values.
width = 200
height = 300
background = { r = 0.1, g = 0.2, b = 0 }
foreground = BLUE
-- Function that is called from the application.
function f(x, y)
    return mylib.mysin(x * y)
end

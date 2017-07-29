
#include "colors.h"
#include "function.h"

bool loadLuaFile(lua_State *L, const char *fileName)
{
    if (luaL_loadfile(L, fileName) || lua_pcall(L, 0, 0, 0))
    {
        printf(
            "ERROR. Cannot load Lua file '%s': '%s'\n",
            fileName,
            lua_tostring(L, -1));
        lua_pop(L, 1);
        return false;
    }
    return true;
}

void readWidthHeight(lua_State *L, int *width, int *height)
{
    // Width.
    lua_getglobal(L, "width");
    if (!lua_isnumber(L, -1))
    {
        printf("readWidthHeight. 'width' should be a number\n");
    }
    else
    {
        *width = (int)lua_tonumber(L, -1);
    }
    lua_pop(L, 1);

    // Height.
    lua_getglobal(L, "height");
    if (!lua_isnumber(L, -1))
    {
        printf("readWidthHeight. 'height' should be a number\n");
    }
    else
    {
        *height = (int)lua_tonumber(L, -1);
    }
    lua_pop(L, 1);
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s /path/to/cfg.lua\n", argv[0]);
        return 1;
    }

    const char *fileName = argv[1];

    // Create lua state.
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    setupPredefinedColors(L);

    if (loadLuaFile(L, fileName))
    {
        // Read width and height.
        int width = 0;
        int height = 0;
        readWidthHeight(L, &width, &height);
        printf("main. width: '%d' height: '%d'\n", width, height);

        // Read background color.
        unsigned char r = 0;
        unsigned char g = 0;
        unsigned char b = 0;
        readColor(L, "background", &r, &g, &b);
        printf("main. background: '%d, %d, %d'\n", r, g, b);
        readColor(L, "foreground", &r, &g, &b);
        printf("main. foreground: '%d, %d, %d'\n", r, g, b);

        // Execute function.
        double x = 20;
        double y = 3;
        double f = functionF(L, x, y);
        printf("main. '%f' = functionF(%f, %f)\n", f, x, y);
    }

    // Close lua state.
    lua_close(L);

    return 0;
}


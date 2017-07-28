
#include <cstdio>

#include "lua.hpp"

const int MAX_COLOR = 255;

struct ColorTable
{
    const char *name;
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

ColorTable colorTable[] =
{
    {"WHITE", MAX_COLOR, MAX_COLOR, MAX_COLOR},
    {"BLACK", 0, 0, 0},
    {"RED", MAX_COLOR, 0, 0},
    {"GREEN", 0, MAX_COLOR, 0},
    {"BLUE", 0, 0, MAX_COLOR},
    {0, 0, 0, 0}, // Sentinel.
};

// Assume table is at the top of the stack, i.e., it has '-1' index.
int tableField(lua_State *L, const char *key)
{
    int result = -1;
    lua_pushstring(L, key);
    lua_gettable(L, -2);
    if (!lua_isnumber(L, -1))
    {
        printf(
            "ERROR. Table field '%s' must be a number: '%s'",
            key,
            lua_tostring(L, -1));
    }
    else
    {
        result = (int)lua_tonumber(L, -1) * MAX_COLOR;
    }
    lua_pop(L, 1);
    return result;
}

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

    if (loadLuaFile(L, fileName))
    {
        // Read width and height.
        int width = 0;
        int height = 0;
        readWidthHeight(L, &width, &height);
        printf("main. width: '%d' height: '%d'\n", width, height);


    }

    // Close lua state.
    lua_close(L);

    return 0;
}



#include <cstdio>

#include "lua.hpp"

void load(const char *fileName, int *width, int *height)
{
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    if (luaL_loadfile(L, fileName) || lua_pcall(L, 0, 0, 0))
    {
        printf("Cannot run configuration file '%s': '%s'\n", fileName, lua_tostring(L, -1));
        lua_pop(L, 1);
    }

    lua_getglobal(L, "width");
    lua_getglobal(L, "height");
    if (!lua_isnumber(L, -2))
    {
        printf("'width' should be a number\n");
        lua_pop(L, 1);
    }
    if (!lua_isnumber(L, -1))
    {
        printf("'height' should be a number\n");
        lua_pop(L, 1);
    }
    *width = (int)lua_tonumber(L, -2);
    *height = (int)lua_tonumber(L, -1);

    lua_close(L);
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s /path/to/cfg.lua\n", argv[0]);
        return 1;
    }

    const char *fileName = argv[1];

    int width;
    int height;
    load(fileName, &width, &height);

    printf("Width: '%d' height: '%d'\n", width, height);

    return 0;
}


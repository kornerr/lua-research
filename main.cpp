
#include "colors.h"

#include <cstdio>

#include "lua.hpp"

// Assume table is at the top of the stack, i.e., it has '-1' index.
void setTableField(lua_State *L, const char *key, int value)
{
    lua_pushstring(L, key);
    lua_pushnumber(L, (double)value / MAX_COLOR);
    lua_settable(L, -3);
}

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
        result = (double)lua_tonumber(L, -1) * MAX_COLOR;
    }
    lua_pop(L, 1);
    return result;
}

void setColor(lua_State *L, Color *color)
{
    lua_newtable(L);
    setTableField(L, "r", color->red);
    setTableField(L, "g", color->green);
    setTableField(L, "b", color->blue);
    lua_setglobal(L, color->name);
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

void setupPredefinedColors(lua_State *L)
{
    int i = 0;
    while (predefinedColors[i].name)
    {
        setColor(L, &predefinedColors[i++]);
    }
}

void readColor(
    lua_State *L,
    const char *propertyName,
    unsigned char *r,
    unsigned char *g,
    unsigned char *b)
{
    lua_getglobal(L, propertyName);
    if (!lua_istable(L, -1))
    {
        printf("readColor. '%s' should be a table\n", propertyName);
    }
    else
    {
        *r = tableField(L, "r");
        *g = tableField(L, "g");
        *b = tableField(L, "b");
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

    }

    // Close lua state.
    lua_close(L);

    return 0;
}


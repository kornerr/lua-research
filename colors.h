
#ifndef LUA_RESEARCH_COLORS_H
#define LUA_RESEARCH_COLORS_H

#include "table.h"

const int MAX_COLOR = 255;

struct Color
{
    const char *name;
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

Color predefinedColors[] =
{
    {"WHITE", MAX_COLOR, MAX_COLOR, MAX_COLOR},
    {"BLACK", 0, 0, 0},
    {"RED", MAX_COLOR, 0, 0},
    {"GREEN", 0, MAX_COLOR, 0},
    {"BLUE", 0, 0, MAX_COLOR},
    {0, 0, 0, 0}, // Sentinel.
};

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
        *r = tableField(L, "r") * MAX_COLOR;
        *g = tableField(L, "g") * MAX_COLOR;
        *b = tableField(L, "b") * MAX_COLOR;
    }
    lua_pop(L, 1);
}

void setColor(lua_State *L, Color *color)
{
    lua_newtable(L);
    setTableField(L, "r", (double)color->red / MAX_COLOR);
    setTableField(L, "g", (double)color->green / MAX_COLOR);
    setTableField(L, "b", (double)color->blue / MAX_COLOR);
    lua_setglobal(L, color->name);
}

void setupPredefinedColors(lua_State *L)
{
    int i = 0;
    while (predefinedColors[i].name)
    {
        setColor(L, &predefinedColors[i++]);
    }
}

#endif // LUA_RESEARCH_COLORS_H


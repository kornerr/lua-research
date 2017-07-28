
#ifndef LUA_RESEARCH_TABLE_H
#define LUA_RESEARCH_TABLE_H

#include "lua.hpp"

#include <cstdio>

// Assume table is at the top of the stack, i.e., it has '-1' index.
void setTableField(lua_State *L, const char *key, double value)
{
    lua_pushstring(L, key);
    lua_pushnumber(L, value);
    lua_settable(L, -3);
}

// Assume table is at the top of the stack, i.e., it has '-1' index.
double tableField(lua_State *L, const char *key)
{
    double result = 0;
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
        result = lua_tonumber(L, -1);
    }
    lua_pop(L, 1);
    return result;
}


#endif // LUA_RESEARCH_TABLE_H


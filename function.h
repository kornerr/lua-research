
#ifndef LUA_RESEARCH_FUNCTION_H
#define LUA_RESEARCH_FUNCTION_H

#include "lua.hpp"

#include <cmath>

double functionF(lua_State *L, double x, double y)
{
    lua_getglobal(L, "f");
    lua_pushnumber(L, x);
    lua_pushnumber(L, y);
    double result = 0;
    if (lua_pcall(L, 2, 1, 0))
    {
        printf(
            "ERROR. Cannot execute function 'f': '%s'\n",
            lua_tostring(L, -1));
    }
    else if (lua_isnumber(L, -1))
    {
        result = lua_tonumber(L, -1);
    }
    lua_pop(L, 1);
    return result;
}

static int l_sin(lua_State *L)
{
    double value = luaL_checknumber(L, 1);
    double result = sin(value);
    lua_pushnumber(L, result);
    // Return number of results.
    return 1;
}

static const struct luaL_Reg mylib[] =
{
    {"mysin", l_sin},
    {0, 0} // Sentinel.
};

int luaopen_mylib(lua_State *L)
{
    luaL_openlib(L, "mylib", mylib, 0);
    return 1;
}

#endif // LUA_RESEARCH_FUNCTION_H


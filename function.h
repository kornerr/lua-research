
#ifndef LUA_RESEARCH_FUNCTION_H
#define LUA_RESEARCH_FUNCTION_H

#include "lua.hpp"

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

#endif // LUA_RESEARCH_FUNCTION_H


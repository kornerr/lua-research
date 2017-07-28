
#include "lua.hpp"

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


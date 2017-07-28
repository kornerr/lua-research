PROJECT(RESEARCH_LUA)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

FIND_PACKAGE(Lua REQUIRED)

# Use C++11.
ADD_DEFINITIONS("-std=c++11")

# Reference own inlcudes.
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR})

# Create executable.
ADD_EXECUTABLE(researchLua main.cpp)
# Link executable with core library.
TARGET_LINK_LIBRARIES(researchLua lua)


#ifndef CUBE_HPP
#define CUBE_HPP

#ifdef linux
#include <glm/glm.hpp>
#include <GL/glew.h>
#endif

#ifdef _WIN32
#include <glm.hpp>
#include <glew.h>
#endif

// Erzeugung eines Wuerfels
void generateCube();
// Rendern eines Wuerfels mit der Textur texID
void drawCube(int texID);

#endif
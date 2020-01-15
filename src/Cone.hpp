#ifndef CONE_HPP
#define CONE_HPP

#ifdef linux
#include <glm/glm.hpp>
#include <GL/glew.h>
#endif

#ifdef _WIN32
#include <glm.hpp>
#include <glew.h>
#endif

#include <cmath>



constexpr int NumVertices=360;
void calcConeTexCoords(float h, float r, float vertices[][2]);
// Berechnung der Texturkoordinaten fuer einen Kegel
//void calcConeTexCoords(float h, float r, float vertices[][2]);
// Erzeugung eines Kegels
void generateCone(float height=1.0f, float radius=0.5f);

// Rendern eines Kegels mit der Textur texID
void drawCone(int texID);

#endif
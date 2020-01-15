#ifndef DATA_HPP
#define DATA_HPP

#ifdef linux
#include <glm/glm.hpp>
#endif

#ifdef _WIN32
#include <glm.hpp>
#endif

using namespace glm;

enum VAO_IDs { Cube, Cone, Cylinder, NumVAOs };
enum VBO_IDs {CubeVBO, ConeVBO, CylinderVBO, NumVBOs};
enum Buffer_IDs { ArrayBuffer, ConeBuffer, CylinderBuffer, NumBuffers };
enum Attrib_IDs {vPosition, vNormal, vTexture};
extern unsigned int VAOs[NumVAOs];
extern unsigned int VBOs[NumVBOs];
extern unsigned int Buffers[NumBuffers];

#endif
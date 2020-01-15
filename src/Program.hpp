#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <iostream>
#include <string>
using namespace std;

#ifdef linux
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <FreeImage.h>
#include <unistd.h>
#include <sys/time.h>
#endif

#ifdef _WIN32
#include <glm.hpp>
#include <gtx/transform.hpp>
#include <glew.h>
#include <freeglut.h>
#include <FreeImage.h>
#define _USE_MATH_DEFINES
#include <cmath>
#endif

using namespace glm;

void init();
void setViewPoint();
void display();
void renderScene();
void reshape(int w, int h);
void timer(int value);
void keyboard(unsigned char theKey, int mouseX, int mouseY);
void special(int specKey, int mouseX, int mouseY);
void mouse(int theButton, int State, int mouseX, int mouseY);
void motion(int mouseX, int mouseY);
void loadTextures();

extern GLuint program;

// Shader-Variablen
extern GLuint ModelViewProjectionLoc;
extern GLuint ModelLoc;
extern GLuint ViewLoc;
extern GLuint ProjectionLoc;
extern GLuint NormalMatrixLoc;

constexpr int numLights = 4;
extern GLuint lightPosLoc;
extern GLuint lightColorLoc;
extern GLuint lightDirLoc;
extern GLuint isLightSourceLoc;
extern GLuint useSpecularLightLoc;
extern GLuint viewPosLoc;
extern int displayLightLoc;
extern int displayLight[numLights];

// Texturen
constexpr int numTextures = 2;
extern GLuint texIDs[numTextures];
const string texturePaths[numTextures] = {
    "../img/wood.jpg",
    "../img/metal.jpg",
};

// Rotation, Verschiebung, etc.
extern GLint width, height;
extern mat4 Model;
extern mat4 View;
extern mat4 Projection;
extern mat4 ModelViewProjection;
extern GLfloat alpha, beta, dist, DELTA;


#endif
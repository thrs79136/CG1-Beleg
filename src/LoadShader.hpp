#ifndef LOADSHADER_HPP
#define LOADSHADER_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <vector>
#include <GL/glew.h>

GLuint loadShaders(const char* vertexFilePath, const char* fragmentFilePath);

#endif
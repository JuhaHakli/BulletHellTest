#ifndef OPENGLFUNCS_H
#define OPENGLFUNCS_H

#define GLEW_STATIC
#include"gl/glew.h"

#include"sdl2/SDL.h"
#include"sdl2/SDL_opengl.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"
#include"soil2/soil2.h"

#include<stdio.h>
#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include<algorithm>

using namespace std;

GLuint LoadShaders(const char *vertex_file_path, const char *fragment_file_path);

GLuint LoadShadersG(const char *vertex_file_path, const char *fragment_file_path, const char *geometry_file_path);

void drawBulletList();

#endif

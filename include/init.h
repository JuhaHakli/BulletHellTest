#ifndef INIT_H
#define INIT_H

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

bool init_sauna(SDL_Window **window, SDL_GLContext &glcontext);

#endif // INIT_H

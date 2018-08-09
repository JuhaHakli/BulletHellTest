#define GLEW_STATIC
#include"gl/glew.h"

#include"sdl2/SDL.h"
#include"sdl2/SDL_opengl.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"
#include"soil2/soil2.h"

#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include<algorithm>

#include"init.h"
#include"openglfuncs.h"
#include"bulletstruct.h"
#include"bulletlogic.h"
#include"global.h"

using namespace std;

int main(int argc, char *argv[])
{
    //Vakiot
    const int SCREEN_FPS = 60;
    const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
    const int TICKS_PER_SECOND = 60;
	const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
	const int MAX_FRAMESKIP = 5;

    //Luodaan koko suorituksen ajan tarvittavat muuttujat
	SDL_Window *window = NULL;
	SDL_GLContext glcontext;
	bool running = true;

    //Alustetaan ohjelma funktion kautta
	if(!init_sauna(&window, glcontext))
	{
        running = false;
        cout << "Exiting..." << endl;
	}

	int vali = sizeof(aBullet);

    glm::mat4 projectionMatrix = glm::ortho(0.0f, 576.0f, 672.0f, 0.0f);



	GLuint testShader = LoadShadersG("shaders/luotitesti.vshader", "shaders/luotitesti.fshader", "shaders/luotitesti.gshader");

	glUseProgram(testShader);
	GLuint projectionLoc = glGetUniformLocation(testShader, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height;
    unsigned char* image =
    SOIL_load_image("img/luodit.png", &width, &height, 0, SOIL_LOAD_RGBA);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);

    GLint posAttrib = glGetAttribLocation(testShader, "pos");
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, vali, (void*)0);
    glEnableVertexAttribArray(posAttrib);

    GLint angAttrib = glGetAttribLocation(testShader, "ang");
	glVertexAttribPointer(angAttrib, 1, GL_FLOAT, GL_FALSE, vali, (void*)(2*sizeof(GLfloat)));
    glEnableVertexAttribArray(angAttrib);

    GLint spdAttrib = glGetAttribLocation(testShader, "spd");
	glVertexAttribPointer(spdAttrib, 1, GL_FLOAT, GL_FALSE, vali, (void*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(spdAttrib);

    GLint hueAttrib = glGetAttribLocation(testShader, "hue");
	glVertexAttribPointer(hueAttrib, 1, GL_FLOAT, GL_FALSE, vali, (void*)(4*sizeof(GLfloat)));
    glEnableVertexAttribArray(hueAttrib);

    GLint shpAttrib = glGetAttribLocation(testShader, "shp");
	glVertexAttribIPointer(shpAttrib, 1, GL_INT, vali, (void*)(5*sizeof(GLfloat)));
    glEnableVertexAttribArray(shpAttrib);

    GLint tmeAttrib = glGetAttribLocation(testShader, "tme");
	glVertexAttribIPointer(tmeAttrib, 1, GL_INT, vali, (void*)(5*sizeof(GLfloat) + sizeof(GLint)));
    glEnableVertexAttribArray(tmeAttrib);

	//Luodaan luotilistat
	vector<aBullet> aBulletList;
	vector<bBullet> bBulletList;

    int spiral = 0;
    GLint shapeCntr = 0;
    GLfloat tintCntr = 0.0f;

    SDL_Event windowEvent;

    //Loopissa k‰ytett‰v‰t muuttujat
    unsigned long int timestep_nextGameTick = SDL_GetTicks();
	int timestep_loops;
	float timestep_interpolation;

    //P‰‰silmukka
	while(running)
	{
        timestep_loops = 0;
        while(SDL_GetTicks() > timestep_nextGameTick && timestep_loops < MAX_FRAMESKIP)
        {
            //Tapahtumat
            if(SDL_PollEvent(&windowEvent))
            {
                if(windowEvent.type == SDL_QUIT) running = false;
            }
            //Ovatko luodit ulkona?
            for(int i = 0; i < aBulletList.size(); ++i)
            {
                if(aBulletList[i].x > 704 || aBulletList[i].x < -128 || aBulletList[i].y > 800 || aBulletList[i].y < -128)
                    aBulletList[i].is_dead = true;
                if(aBulletList[i].is_dead)
                {
                    aBulletList.erase(aBulletList.begin() + i);
                    --i;
                }
            }

            //Logiikka
            //Luodaan luoteja
            aBullet uusi;
            uusi.x = 288;
            uusi.y = 336;
            uusi.speed = 2.0f;
            uusi.shape = shapeCntr;
            //uusi.shape = 4;
            uusi.time = 0;
            uusi.hue = tintCntr;
            //srand(SDL_GetTicks());
            uusi.angle = spiral;
            uusi.logicPointer = aLinearMove;

            shapeCntr += 1;
            if(shapeCntr > 4) shapeCntr = 0;
            spiral += 185.3f;
            if(spiral >= 360) spiral -= 360;

            tintCntr += 0.05f;
            if(tintCntr >= 0.99f)
            tintCntr = 0.0f;

            //Lis‰t‰‰n luoti vektoriin
            aBulletList.push_back(uusi);

            //K‰yd‰‰n l‰pi luotien liikkeet
            for(int i = 0; i < aBulletList.size(); ++i)
            {
                aBulletList[i].time += 1;
                aBulletList[i].logicPointer(aBulletList[i]);
            }

            //Kerrotaan luotien m‰‰r‰
            cout << "Luoteja on t‰ll‰hetkell‰: " << aBulletList.size() << endl;

            //Aikahypyn asetus
            timestep_nextGameTick += SKIP_TICKS;
			timestep_loops++;
        }

        //Piirto
        //Tyhjennet‰‰n v‰ribufferi
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, aBulletList.size() * sizeof(aBullet), aBulletList.data(), GL_STATIC_DRAW);
        glDrawArrays(GL_POINTS, 0, aBulletList.size());

        SDL_GL_SwapWindow(window);
    }

    return 0;
}

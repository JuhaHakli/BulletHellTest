#ifndef BULLETSTRUCT_H
#define BULLETSTRUCT_H

#include"sdl2/SDL_opengl.h"

//Esinimet‰‰n luodit
struct aBullet;
struct bBullet;

//Funktio osoittimet luotien logiikalle
typedef void (*logicFunction)(aBullet&);

struct aBullet
{
    //Luodin t‰m‰nhetkinen sijainti
    GLfloat x;
    GLfloat y;
    //Luodin kulkusuunta
    GLfloat angle;
    //Luodin nopeus
    GLfloat speed;
    //Luodin s‰vy
    GLfloat hue;
    //Mit‰ luotigrafiikkaa k‰ytet‰‰n ja mink‰ kokoinen on hitbox
    GLint shape;
    //Montako framea luoti on ollut olemassa
    GLint time;
    //Onko luoti merkaattu poistettavaksi
    bool is_dead = false;
    //Pointteri luodin logiikka funktioon
    logicFunction logicPointer;
};

struct bBullet
{
    //Luodin t‰m‰nhetkinen sijainti
    int x;
    int y;
    //Luodin nopeudet akseleittain
    int xSpeed;
    int ySpeed;
    //Mit‰ luotigrafiikkaa k‰ytet‰‰n ja mink‰ kokoinen on hitbox
    int shape;
    //Montako framea luoti on ollut olemassa
    int time = 0;
    //Onko luoti merkaattu poistettavaksi
    bool is_dead = false;
    //Pointteri luodin logiikka funktioon
    unsigned int (*logicFunction)(aBullet);
};


#endif

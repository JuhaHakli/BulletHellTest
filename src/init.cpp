#include "init.h"

bool init_sauna(SDL_Window **window, SDL_GLContext &glcontext)
{
    //Alustus
    //Luodaan ikkuna, konteksti ja versiohallinta.
    //Initialize SDL

    if(SDL_Init( SDL_INIT_EVERYTHING) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);


	*window = SDL_CreateWindow( "Sauna Luotihelvetti", 400, 200, 576, 672, SDL_WINDOW_OPENGL);
	//*window = SDL_CreateWindow( "Sauna Luotihelvetti", 400, 200, 857, 1000, SDL_WINDOW_OPENGL);
	if(*window == NULL)
	{
        cout << "ERROR: Couldn't create window" << endl;
        return false;
	}

    //Luodaan konteksti ja käytetään sitä
	glcontext = SDL_GL_CreateContext(*window);
	SDL_GL_MakeCurrent(*window, glcontext);

    //glViewport(0, 0, 800, 600);

	//Alustetaan Glew
	glewExperimental = GL_TRUE;

	if(glewInit() != GLEW_OK)
	{
        cout << "ERROR: Couldn't initiate GLEW" << endl;
        return false;
	}

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return true;

}

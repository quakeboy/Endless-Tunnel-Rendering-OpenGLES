#include <SDL.h>
#include "RTunnel.h"

#define USEOPENGL
#ifdef USEOPENGL
	#define MY_SDL_FLAGS SDL_OPENGL
#else
	#define MY_SDL_FLAGS SDL_HWSURFACE
#endif


GLuint LoadTexture(const char *texturename)
{
	GLuint textid = 0;
	SDL_Surface *imagesurface = SDL_LoadBMP(texturename);
	SDL_LockSurface(imagesurface);

	glGenTextures(1, &textid);
	glBindTexture(GL_TEXTURE_2D, textid);	
	
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 512, 512, 0, 
	//	GL_BGR_EXT, GL_UNSIGNED_BYTE, imagesurface->pixels);

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, 512, 512, GL_BGR_EXT, GL_UNSIGNED_BYTE, imagesurface->pixels);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SDL_UnlockSurface(imagesurface);
	SDL_FreeSurface(imagesurface);

	return textid;
}

int main(int argc, char*argv[])
{
	// initing the SDL stuff
	SDL_Surface *screen;

    if((SDL_Init(SDL_INIT_VIDEO)==-1)) { 
        printf("Could not initialize SDL: %s.\n", SDL_GetError());
        exit(-1);
    }
	atexit(SDL_Quit);

    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	screen = SDL_SetVideoMode(800, 800, 8, MY_SDL_FLAGS);
    if ( screen == NULL ) {
        fprintf(stderr, "Couldn't set video mode: %s\n", SDL_GetError());
        exit(1);
    }

	initOGL();
	texture1 = LoadTexture("plasma2.bmp");	

	while(1)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch(event.type){
				case SDL_QUIT:
					SDL_Quit();
					exit(0);
					break;
			}
		}
		
		render();
		SDL_GL_SwapBuffers();
	}

	return 0;
}

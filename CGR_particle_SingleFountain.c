/*
 *	UDESC - Universidade do Estado de Santa Catarina
 *	Computação Gráfica - CGR0001
 *	T1 - Partículas
 *	Nadyan Suriel Pscheidt
 */

// Compile:
// gcc CGR_particle_SingleFountain.c -lGL -lGLU -lSDL -lm -o cgr_particleS
// ./cgr_particleS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <unistd.h>

/* screen width, height, and bit depth */
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP     16

/* Define our booleans */
#define TRUE  1
#define FALSE 0

/* for the particles */
#define NUM_PARTICLES 4000
#define GRAVITY 0.0006

/* This is our SDL surface */
SDL_Surface *surface;
int qtdParticles1, qtdParticles2;

struct s_pf{
	float x, y, veloc_x, veloc_y;
	unsigned lifetime;
}particles[NUM_PARTICLES];

struct s_pf2{
	float x2, y2, veloc_x2, veloc_y2;
	unsigned lifetime2;
}particles2[NUM_PARTICLES];

// Initialize the fountain
void InitParticle(int pause){
	int i;

	qtdParticles1 = (rand() % NUM_PARTICLES);	//each interation has a random qt of particles (center)
	qtdParticles2 = (rand() % NUM_PARTICLES);	//each interation has a random qt of particles (right)

	
	//left fountain
	for(i = 0; i < qtdParticles1; i++) {
		float velocity = (float)(rand() % 100)/2000.0;
		int angle = rand() % 180; //angulo da circunferencia que a particula vai		
		
		//if(angle > 110 && angle < 150){
		if(angle > 80 && angle < 100){			
			particles[i].veloc_x = cos((M_PI * angle/180.0)) * (1.5 * velocity);
			particles[i].veloc_y = sin((M_PI * angle/180.0)) * (1.5 * velocity);
			particles[i].lifetime = rand() % 150;
			particles[i].x = 0.0;
			particles[i].y = -2.5;
		}
	}
	/*
	//right side fountain
	for(i = 0; i < qtdParticles2; i++) {
		float velocity = (float)(rand() % 100)/2000.0;
		int angle = rand() % 180; //particle angle		
		
		if(angle > 80 && angle < 100){		
			particles2[i].veloc_x2 = cos((M_PI * angle/180.0)) * (1.7 * velocity);
			particles2[i].veloc_y2 = sin((M_PI * angle/180.0)) * (1.7 * velocity);
			particles2[i].lifetime2 = rand() % 250;
			particles2[i].x2 = 1.2;
			particles2[i].y2 = -2.5;
		}
	}*/
}

/* function to release/destroy our resources and restoring the old desktop */
void Quit(int returnCode){
	SDL_Quit();
	exit(returnCode);
}

/* function to reset our viewport after a window resize */
int resizeWindow( int width, int height ){
	GLfloat ratio;

	if(height == 0) 
		height = 1;

	ratio = ( GLfloat )width / ( GLfloat )height;
	glViewport( 0, 0, ( GLsizei )width, ( GLsizei )height );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	gluPerspective( 45.0f, ratio, 0.1f, 100.0f );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );

	return( TRUE );
}

/* function to handle key press events */
void handleKeyPress(SDL_keysym *keysym){
    switch(keysym->sym){
		case SDLK_ESCAPE:
			Quit(0);
			break;
		case SDLK_F1:
			SDL_WM_ToggleFullScreen( surface );
			break;
		default:
			break;
	}

	return;
}

/* general OpenGL initialization function */
int initGL(GLvoid){
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	InitParticle(0); // first firework

	return(TRUE);
}

/* Here goes our drawing code */
int drawGLScene( GLvoid ){
	int i, ative_particles1 = 0, ative_particles2 = 0;

	/* Clear The Screen And The Depth Buffer */
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glLoadIdentity();
	glTranslatef(0.0f,0.0f,-6.0f);		// Move particles 6.0 units into the screen
	
	glBegin(GL_POINTS);
	
	//left fountain
	for(i = 0; i < qtdParticles1; i++) {
		if(particles[i].lifetime) {
			ative_particles1++;
			particles[i].veloc_y -= GRAVITY;
			particles[i].x += particles[i].veloc_x;
			particles[i].y += particles[i].veloc_y;
			particles[i].lifetime--;

			glVertex3f( particles[i].x, particles[i].y, 0.0f); // draw pixel
		}
	}
	/*
	//right fountain
	for(i = 0; i < qtdParticles2; i++) {
		if(particles2[i].lifetime2) {
			ative_particles2++;
			particles2[i].veloc_y2 -= GRAVITY;
			particles2[i].x2 += particles2[i].veloc_x2;
			particles2[i].y2 += particles2[i].veloc_y2;
			particles2[i].lifetime2--;

			glVertex3f( particles2[i].x2, particles2[i].y2, 0.0f); // draw pixel
		}
	}*/

	glEnd();

	/* Draw it to the screen */
	SDL_GL_SwapBuffers( );
	
	//if((ative_particles1 < 1200) || (ative_particles2 < 1200)){
	if(ative_particles1 < 1200){				
		InitParticle(1);
	}

	usleep(10000); /* **Uncomment usleep when running on a dedicated GPU ** 
								for frame rate optimization					*/
	return( TRUE );
}

int main( int argc, char **argv ){
	int videoFlags;
	int done = FALSE;
	SDL_Event event;
	const SDL_VideoInfo *videoInfo;
	int isActive = TRUE;

	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		fprintf( stderr, "Video initialization failed: %s\n",
			SDL_GetError( ) );
		Quit(1);
	}

	videoInfo = SDL_GetVideoInfo( );
	
	if(!videoInfo){
		fprintf( stderr, "Video query failed: %s\n",
			SDL_GetError( ) );
		Quit( 1 );
	}

	/* the flags to pass to SDL_SetVideoMode */
	videoFlags  = SDL_OPENGL;          /* Enable OpenGL in SDL */
	videoFlags |= SDL_GL_DOUBLEBUFFER; /* Enable double buffering */
	videoFlags |= SDL_HWPALETTE;       /* Store the palette in hardware */
	videoFlags |= SDL_RESIZABLE;       /* Enable window resizing */

	/* This checks to see if surfaces can be stored in memory */
	if(videoInfo->hw_available)
		videoFlags |= SDL_HWSURFACE;
	else
		videoFlags |= SDL_SWSURFACE;

	/* This checks if hardware blits can be done */
	if(videoInfo->blit_hw)
		videoFlags |= SDL_HWACCEL;

	/* Sets up OpenGL double buffering */
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	/* get a SDL surface */
	surface = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,
								videoFlags );

	/* Verify there is a surface */
	if(!surface){
		fprintf( stderr,  "Video mode set failed: %s\n", SDL_GetError( ) );
		Quit( 1 );
	}

	/* initialize OpenGL */
	initGL( );

	/* resize the initial window */
	resizeWindow( SCREEN_WIDTH, SCREEN_HEIGHT );

	/* wait for events */
	while (!done){
		/* handle the events in the queue */
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_ACTIVEEVENT:
					if ( event.active.gain == 0 )
						isActive = FALSE;
					else
						isActive = TRUE;
					break;			    

				case SDL_VIDEORESIZE: // handle resize event
					surface = SDL_SetVideoMode( event.resize.w,
								event.resize.h,
								16, videoFlags );
					if (!surface){
						fprintf( stderr, "Could not get a surface after resize: %s\n", SDL_GetError( ) );
						Quit(1);
					}
					resizeWindow(event.resize.w, event.resize.h);
					break;
				case SDL_KEYDOWN: // handle key presses
					handleKeyPress(&event.key.keysym);
					break;
				case SDL_QUIT: // handle quit requests
					done = TRUE;
					break;
				default:
					break;
			}
		}

		/* draw the scene */
		drawGLScene( );
	}

	Quit(0);
	return 0;
}

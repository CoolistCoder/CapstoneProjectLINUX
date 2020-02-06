#ifndef ENGINE_ENGINE_H_
#define ENGINE_ENGINE_H_
#include <iostream>
#include <SDL2/SDL_image.h> //SDL is included in here, containing everything needed to handle the window and load graphics
#include <SDL2/SDL_mixer.h>	//the library needed to load music and sound properly

class Engine {
private:
	bool isrunning; //determines whether the window is still active
	bool success;	//determines if the engine's initialization function ran correctly
	SDL_Window* window;	//the window all entities are sent to
	SDL_GLContext context;	//the opengl context of the window
	unsigned int framerate;	//the rate at which the window updates in seconds

public:
	void init();	//sets up the engine in order for it to run properly
	void end();	//cleans up all components created by the engine
	void makeWindow(unsigned int, unsigned int, std::string);	//create the window for the engine
	void setGLDefaults();	//set the default opengl values so the components can run correctly.

	bool getRunning();	//get whether or not the window is running correctly
	void clearScreen();	//clear the screen of all graphics
	void drawScreen();	//draw all graphics to the screen

	void setPosition(unsigned int, unsigned int);	//set the position of the window
	void setSize(unsigned int, unsigned int);	//set the size of the window
	void setName(std::string);	// set the title of the window

	void setFPS(unsigned int);	//set how many times the engine's screen updates per second

	Engine();			//the constructor automatically calls the init routine
	virtual ~Engine();	//the destructor destroys all of the components opened by SDL2
};

#endif /* ENGINE_ENGINE_H_ */
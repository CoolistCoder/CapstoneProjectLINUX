#ifndef ENGINE_ENGINE_H_
#define ENGINE_ENGINE_H_
#include <iostream>
#include <SDL2/SDL_image.h> //SDL is included in here, containing everything needed to handle the window and load graphics
#include <SDL2/SDL_mixer.h>	//the library needed to load music and sound properly

#include <GL/gl.h>
#include <GL/glu.h>

//We need the Joystick so we will include it with the engine
#include "Joystick.h"
#include <vector> //We can use vectors for mass joystick detection among other features

//We will keep the image class in the engine header to make it easier to share it everywhere
#include "Image.h"

//we also need error logging capabilities
#include "ErrorLog.h"

class Engine {
private:
	bool isrunning; //determines whether the window is still active
	bool success;	//determines if the engine's initialization function ran correctly
	SDL_Window* window;	//the window all entities are sent to
	SDL_GLContext context;	//the opengl context of the window
	unsigned int framerate;	//the rate at which the window updates in seconds
	Uint32 firsttick;	//the first tick of the loop (used for updating the screen)
	ErrorLog* log; //the error log that the engine will know about (TODO IMPLEMENT THIS)

	unsigned int windowW, windowH;	//the width and height of the window recorded
	unsigned int rendererW, rendererH;	//the 'renderer' is where the graphics will be adjusted to fit a specific resolution

	void recalcRenderer();	//this is to resize the renderer dynamically so the picture isn't stretched

	//This is just for detecting the joysticks that are created
	std::vector<Joystick*> alljoysticks;


public:
	void init();	//sets up the engine in order for it to run properly
	void end();	//cleans up all components created by the engine
	void makeWindow(unsigned int, unsigned int, std::string);	//create the window for the engine
	void setGLDefaults();	//set the default opengl values so the components can run correctly.

	bool getRunning();	//get whether or not the window is running correctly
	void clearScreen();	//clear the screen of all graphics
	void drawScreen();	//draw all graphics to the screen

	void setPosition(int, int);	//set the position of the window
	void setSize(unsigned int, unsigned int);	//set the size of the window
	void setName(std::string);	// set the title of the window
	void setResolution(unsigned int, unsigned int);	//adjusts the renderer's size
	unsigned int getResW() { return this->rendererW; }; //get the renderer's width
	unsigned int getResH() { return this->rendererH; }; //get the renderer's height

	void maximizeWindow();	//maximizes the window to the size of the monitor
	void restoreWindow();	//puts the window back where it was prior to maximization
	void fullscreenWindow();	//this fullscreens the window
	void normalscreenWindow();	//this will put the window back to its original size and position

	void stop();	//this will cause the isrunning variable to become false

	void setFPS(unsigned int);	//set how many times the engine's screen updates per second

	static bool getKey(SDL_Scancode); //check whether a particular keyboard key is down

	void addJoystick(Joystick*); //This simply adds a joystick to the engine
	Joystick* getJoystick(unsigned int); //retrieves a joystick based on its index

	Engine();			//the constructor automatically calls the init routine
	virtual ~Engine();	//the destructor destroys all of the components opened by SDL2
};

#endif /* ENGINE_ENGINE_H_ */

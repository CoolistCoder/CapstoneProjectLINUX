/*
 * Capstone Engine developed by Alec Roberts and Steven Cole.
 * Started Jan 22 2020
 */

#include <iostream>
using namespace std;

//we only need to include the Engine.h file
#include "Engine/Engine.h"

//Define commandline parameters for SDL2
int main(int, char**) {
	//create a simple instance of the engine
	Engine* mainEng = new Engine();
	mainEng->makeWindow(640, 480, "Hello, World!");	//create the window for the engine
	//we want to use a different resolution for the scene
	mainEng->setResolution(160,120);

	//simple demonstration variables for input
	int x = 0, y = 0;

	//SIMPLE TEST OF THE JOYSTICK
	Joystick testjoy;
	mainEng->addJoystick(&testjoy); //now add the joystick to the engine

	//Now fullscreen the window
	//mainEng->fullscreenWindow();

	//TODO This is a test of the audio so we don't need it until the next milestone
	//This is our code for testing audio
	Mix_Music* musicdata = nullptr; //We load in our music data to a pointer
	musicdata = Mix_LoadMUS("robomb.wav");	//load in the music (in this case a WAV created by me)
	if (!musicdata){	//if the music data was not found, we can display a message in the terminal for now
		cout << "could not find music" << endl;
	}
	Mix_VolumeMusic(50);	//lower the volume a bit, it's quite loud!





	//create the while loop for the 'game' logic
	while(mainEng->getRunning()){
		//until the X in the top right is clicked, it will keep updating the screen
		mainEng->clearScreen();

		//get joystick input to move the square on the screen
		if (testjoy.getRightStickY() > 100 || mainEng->getKey(SDL_SCANCODE_DOWN))
			y++;
		if (testjoy.getRightStickY() < -100 || mainEng->getKey(SDL_SCANCODE_UP))
			y--;
		if (testjoy.getRightStickX() < -100 || mainEng->getKey(SDL_SCANCODE_LEFT))
			x--;
		if (testjoy.getRightStickX() > 100 || mainEng->getKey(SDL_SCANCODE_RIGHT))
			x++;

		//set up an exit key
		if (mainEng->getKey(SDL_SCANCODE_ESCAPE)){
			mainEng->stop();
		}

		//We might wanna play the music here
		if (!Mix_PlayingMusic())	//This will cause the music to loop
			Mix_PlayMusic(musicdata, 0);


		//create a simple square to test this
		glMatrixMode(GL_MODELVIEW);	//change the matrix to the modelview matrix to modify objects drawn to the screen
		glLoadIdentity();			//change the active identity to the modelview matrix
		glBegin(GL_QUADS);			//draw quads
			glVertex2i(x,y);		//top left
			glVertex2i(x+10,y);		//bottom left
			glVertex2i(x+10,y+10);		//bottom right
			glVertex2i(x,y+10);		//top right
		glEnd();					//stop drawing
		//this will produce a simple square in the top left corner

		mainEng->drawScreen();
	}

	//we can delete the music now that we're done with it
	if (musicdata){
		Mix_FreeMusic(musicdata); //because of the nature of the file, we need a specific function to free it
	}

	//clean up the engine (this will clean it up on its own)
	delete mainEng;

	return 0;
}

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

	//create the while loop for the 'game' logic
	while(mainEng->getRunning()){
		//until the X in the top right is clicked, it will keep updating the screen
		mainEng->clearScreen();

		//create a simple square to test this
		glMatrixMode(GL_MODELVIEW);	//change the matrix to the modelview matrix to modify objects drawn to the screen
		glLoadIdentity();			//change the active identity to the modelview matrix
		glBegin(GL_QUADS);			//draw quads
			glVertex2i(0,0);		//top left
			glVertex2i(10,0);		//bottom left
			glVertex2i(10,10);		//bottom right
			glVertex2i(0,10);		//top right
		glEnd();					//stop drawing
		//this will produce a simple square in the top left corner

		mainEng->drawScreen();
	}

	//clean up the engine (this will clean it up on its own)
	delete mainEng;

	return 0;
}

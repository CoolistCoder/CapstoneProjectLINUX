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
	mainEng->addJoystick(&testjoy); //now add the joystick

	//create the while loop for the 'game' logic
	while(mainEng->getRunning()){
		//until the X in the top right is clicked, it will keep updating the screen
		mainEng->clearScreen();

		//get joystick input to move the square on the screen
		if (testjoy.getRightStickY() > 100)
			y++;
		if (testjoy.getRightStickY() < -100)
			y--;
		if (testjoy.getRightStickX() < -100)
			x--;
		if (testjoy.getRightStickX() > 100)
			x++;




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

	//clean up the engine (this will clean it up on its own)
	delete mainEng;

	return 0;
}

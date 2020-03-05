/*
 * Capstone Engine developed by Alec Roberts and Steven Cole.
 * Started Jan 22 2020
 */

#include <iostream>
using namespace std;

//we only need to include the Engine.h file
#include "Engine/Engine.h"
#include "Engine/Scene.h"

void boxBehavior(Entity*);
void lineBehavior(Entity*);

//Define commandline parameters for SDL2
int main(int, char**) {
	//create a simple instance of the engine
	Engine* mainEng = new Engine();
	mainEng->makeWindow(640, 480, "Hello, World!");	//create the window for the engine
	mainEng->setSize(1920/2, 1080/2);	//testing for setSize
	//we want to use a different resolution for the scene
	mainEng->setResolution(1920/4,1080/4);

	//SIMPLE TEST OF THE JOYSTICK
	Joystick testjoy;
	mainEng->addJoystick(&testjoy); //now add the joystick to the engine

	//create a scene instance
	Scene* scene1 = new Scene(mainEng);

	//create an entity
	Entity* newbox = new Box;

	//give the entity something to do
	newbox->giveJoystick(&testjoy);
	newbox->setBehavior(boxBehavior);

	//give the box to the scene
	scene1->addEntity(newbox);

	//create a line
	Entity* newline = new Line;

	//also give the line the box
	newline->attachEntity(newbox);

	//give the line something to do
	newline->setBehavior(lineBehavior);

	//give the scene the line
	scene1->addEntity(newline);


	//Now fullscreen the window
	//mainEng->fullscreenWindow();

	//TODO This is a test of the audio so we don't need it until the next milestone
	//This is our code for testing audio
	/*
	Mix_Music* musicdata = nullptr; //We load in our music data to a pointer
	musicdata = Mix_LoadMUS("robomb.wav");	//load in the music (in this case a WAV created by me)
	if (!musicdata){	//if the music data was not found, we can display a message in the terminal for now
		cout << "could not find music" << endl;
	}
	Mix_VolumeMusic(50);	//lower the volume a bit, it's quite loud!
	*/




	//create the while loop for the 'game' logic
	while(mainEng->getRunning()){

		scene1->execute();
	}

	/*
	//we can delete the music now that we're done with it
	if (musicdata){
		Mix_FreeMusic(musicdata); //because of the nature of the file, we need a specific function to free it
	}
	*/

	//delete any scenes
	delete scene1;

	//clean up the engine (this will clean it up on its own)
	delete mainEng;

	return 0;
}

void boxBehavior(Entity* b){
	Box* temp = static_cast<Box*>(b);

	//save the position of the square into variables
	int x = temp->getX(), y = temp->getY();

	//alternate between keyboard and joystick based on what's available
	if (temp->getJoystick() && temp->getJoystick()->getPluggedIn()){
		//allow us to modify those variables with the keyboard
		if (temp->getJoystick()->getLeftStickY() > 100)
			y++;
		if (temp->getJoystick()->getLeftStickY() < -100)
			y--;
		if (temp->getJoystick()->getLeftStickX() < -100)
			x--;
		if (temp->getJoystick()->getLeftStickX() > 100)
			x++;
	}
	else{
		//allow us to modify those variables with the keyboard
		if (Engine::getKey(SDL_SCANCODE_DOWN))
			y++;
		if (Engine::getKey(SDL_SCANCODE_UP))
			y--;
		if (Engine::getKey(SDL_SCANCODE_LEFT))
			x--;
		if (Engine::getKey(SDL_SCANCODE_RIGHT))
			x++;
	}



	//put those modified variables into the box
	temp->setPosition(x, y);
	temp->setSize(10, 10); //make the box bigger

	//draw the box
	temp->draw();

}


void lineBehavior(Entity* e){
	//I want to create four lines that extend to each corner of the renderer and attach to the box at each corner
	Line* temp = static_cast<Line*>(e); //store the line in a temporary variable
	Box* attachedBox = static_cast<Box*>(e->getAttachedEntity(0)); //store the box we attached to the line to a variable

	//now set the line's position
	temp->setLinePosition(0,0,attachedBox->getX(),attachedBox->getY());
	//and draw
	temp->draw();

	//repeat the last two calls for each corner to demonstrate flexibility
	//now set the line's position
	temp->setLinePosition(temp->getEngine()->getResW(),0,attachedBox->getX() + attachedBox->getW(),attachedBox->getY());
	//and draw
	temp->draw();

	//now set the line's position
	temp->setLinePosition(temp->getEngine()->getResW(),temp->getEngine()->getResH(),attachedBox->getX() + attachedBox->getW(),attachedBox->getY() + attachedBox->getH());
	//and draw
	temp->draw();

	//now set the line's position
	temp->setLinePosition(0,temp->getEngine()->getResH(),attachedBox->getX(),attachedBox->getY() + attachedBox->getH());
	//and draw
	temp->draw();
}



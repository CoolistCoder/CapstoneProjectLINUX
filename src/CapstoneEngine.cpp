/*
 * Capstone Engine developed by Alec Roberts and Steven Cole.
 * Started Jan 22 2020
 */
#include <random>
#include <iostream>
using namespace std;

//we only need to include the Engine.h file
#include "Engine/CapstoneEngine.h"

//Define commandline parameters for SDL2
int main(int, char**) {
	//create the game engine and set the values we want for the game engine
	Engine* gameEngine = new Engine(); //instantiate the game engine
	gameEngine->makeWindow(1920/2, 1080/2, "Laser Avenger"); //create our window
	gameEngine->setResolution(1920/4, 1080/4); //set our resolution

	//instantiate a joystick so we can use at least 1
	Joystick* mainJoystick = new Joystick();
	//give the game engine the joystick
	gameEngine->addJoystick(mainJoystick);

	//we have two scenes: the title, and the gameplay scenes
	Scene* titleScene = new Scene(gameEngine);
	Scene* gameScene = new Scene(gameEngine);

	//use some text to see if the program works



	//delete the scenes in reverse order from which they appeared
	delete gameScene;
	delete titleScene;

	delete gameEngine; //delete the game engine

	return 0;
}







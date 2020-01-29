/*
 * Capstone Engine developed by Alec Roberts and Steven Cole.
 * Started Jan 22 2020
 */

#include <iostream>
using namespace std;

//include SDL2 and OpenGL
#include <SDL2/SDL.h>		//SDL2	 (remove if using SDL_image or SDL_mixer)
#include <GL/gl.h>			//OpenGL

//Define commandline parameters for SDL2
int main(int, char**) {
	//temporary main to see if everything connected properly TODO clear out this entire main
	//first init SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
		cout << "Failed to init" << endl;
	}

	//create a window and then close it shortly afterwards
	SDL_Window* tempwindow = SDL_CreateWindow("TEST", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 128, 128, SDL_WINDOW_SHOWN);
	SDL_Delay(3000);	//delay for 3 seconds to see if the window can be seen
	SDL_DestroyWindow(tempwindow);
	SDL_Quit();

	return 0;
}

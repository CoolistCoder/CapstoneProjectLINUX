

#include "Engine.h"

void Engine::init(){
	//first, begin the process of initialization
	//because we want to initialize SDL as a whole for now,
	//we'll use the everything flag for initializing SDL2
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
		//failure to init occurs if the value of SDL_Init is less than 0
		//we want to show a simple message box that will tell the user that something went wrong
		SDL_ShowSimpleMessageBox(
		SDL_MESSAGEBOX_ERROR,	//create a messagebox with an error icon
		"ERROR",				//the title of the error should just be "error" to describe what kind of box it is
		"UNABLE TO INIT SDL",	//a simple description of the error
		nullptr					//our window is currently null, so we should just use nullptr
		);
		//we must break from the init
		return;
	}

	//if the first init phase works, then we can move onto step two
	//we must initialize the image module
	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)<1){
		//IMG init fails if the value returned is 0
		//the error message is largely the same
		SDL_ShowSimpleMessageBox(
		SDL_MESSAGEBOX_ERROR,	//create a messagebox with an error icon
		"ERROR",				//the title of the error should just be "error" to describe what kind of box it is
		"UNABLE TO INIT SDL IMAGE",	//a simple description of the error
		nullptr					//our window is currently null, so we should just use nullptr
		);
		//break the function
		return;
	}

	//the final step is similar to the first two steps
	//we must initialize the mixer module
	if (Mix_Init(MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG)<1){
		//MIX init also fails if the value returned is 0
		//the error message is still mostly the same
		SDL_ShowSimpleMessageBox(
		SDL_MESSAGEBOX_ERROR,	//create a messagebox with an error icon
		"ERROR",				//the title of the error should just be "error" to describe what kind of box it is
		"UNABLE TO INIT SDL MIXER",	//a simple description of the error
		nullptr					//our window is currently null, so we should just use nullptr
		);
		//break the function
		return;
	}

	//if all of these initialization processes have been successfully run, we can set the success variable to true
	this->success = true;
}

void Engine::end(){
	//this occurs at the end of the engine's run
	//once finished, the engine needs to be able to free all of its elements
	//first, clear out the context
	if (this->context){
		//if the context is not empty, we need to clean it out
		SDL_GL_DeleteContext(this->context);
		//this function deletes the active context
	}
	//now we can delete the window
	if (this->window){
		//we can't just delete this however, we need a special function to clear it out
		SDL_DestroyWindow(this->window);
		//this function will clear out the window and all of its properties without causing leaks
	}
	//finally, we may implement the quit function
	SDL_Quit();
	//this function will close any resources that SDL uses
	//this will finish up the exit process, and the program will quit without any leaks
}

void Engine::makeWindow(unsigned int w, unsigned int h, std::string title){

}

void Engine::setGLDefaults(){
	//TODO implement this during the make window routine
}

bool Engine::getRunning(){
	//not much to it, just get the isrunning variable and return it
	return this->isrunning;
}

void Engine::clearScreen(){

}

void Engine::drawScreen(){

}

void Engine::setPosition(unsigned int x, unsigned int y){

}

void Engine::setSize(unsigned int w, unsigned int h){

}

void Engine::setName(std::string newname){

}

void Engine::setFPS(unsigned int newFPS){

}

Engine::Engine() {
	//begin by setting the defaults of everything
	this->context = 0; //don't need the context yet
	this->window = nullptr;		//no window has been created
	this->isrunning = false;	//the window is not running, therefore this is false for now
	this->success = false;	//the engine has not been initialized, therefore it is not successfully initialized
	this->framerate = 60;	//by default, the engine runs at 60 hrz

	this->init();	//perform the init after the engine's default values have been set

}

Engine::~Engine() {
	//clear out the engine once it has been deleted
	this->end();
}


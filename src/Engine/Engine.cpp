

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
	if (this->success){ //we only want to create a window if we can successfully initialize the engine!
		//now, the window needs to be initialized
		//we need to use a particular function to achieve this
		this->window = SDL_CreateWindow( //this function will properly set the window's properties
			title.c_str(),	//because the library was written in C, the title must be converted to a c string
			SDL_WINDOWPOS_CENTERED, //we want the window to appear in the center of the screen horizontally
			SDL_WINDOWPOS_CENTERED,	//we also want the window to appear in the center of the screen vertically
			w,						//we want the window to be set to the specified width
			h,						//as well as a specified height
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE	//finally, we need the window to be our OpenGL target, and we want to resize it
		);
		//we must check to see if this was done correctly, otherwise we cannot complete the window init
		if (!this->window){
			//we must check to see if the window is empty
			//if it is, then we display a messagebox like before
			SDL_ShowSimpleMessageBox(
				SDL_MESSAGEBOX_ERROR,			//the messagebox is an error box
				"ERROR",						//the title
				"COULD NOT CREATE THE WINDOW",	//the description telling us that the window init was a failure
				nullptr							//we still don't have a window to use, so nullptr
			);
			return;	//we need to leave this process before anything else happens
		}
		else{
			//if the window was properly initialized, we can call the opengl setup function, which preps
			//the window for OpenGL
			this->setGLDefaults();	//this will properly set up the window so we can use it for OpenGL
		}
	}

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
	//SDL contains simple functions for modifying the window's properties
	SDL_SetWindowPosition(this->window, x, y);
	//these are extremely simple, and are based on the pixel position of a window's border
}

void Engine::setSize(unsigned int w, unsigned int h){
	//like the previous position function, we can do the same with the size
	SDL_SetWindowSize(this->window, w, h);
}

void Engine::setName(std::string newname){
	//make sure the newname variable is not empty before setting the window's title!!!
	if (!newname.empty()){
		//we can again, use a simple function to set the title of the window
		SDL_SetWindowTitle(this->window, newname.c_str());
	}
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


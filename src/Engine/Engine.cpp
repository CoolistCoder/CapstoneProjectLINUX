

#include "Engine.h"

void Engine::recalcRenderer(){
	//TODO implement this
	//side note: this is a function that implements a lot of mathematical logic so don't worry until slightly later
}

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
	//this function just needs to run in the window creation function
	//first, we need to set the context
	this->context = SDL_GL_CreateContext(this->window);
	//this will give OpenGL information on our window so we can draw to it

	//TODO modify the bits depth in case we want to change how much depth our graphics need
	//we need to tell our engine what the color depth is so we can fine tune the color depth of our graphics
	const int bitsdepth = 8;	//this is used to set the color depth of our engine for RGBA
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, bitsdepth);	//this will set the bits of our red channel to the value of bitsdepth
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, bitsdepth);	//this will set the bits of our green channel to the value of bitsdepth
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, bitsdepth);	//this will set the bits of our blue channel to the value of bitsdepth
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, bitsdepth);	//this will set the bits of our alpha channel to the value of bitsdepth
	//if all is done right, the color values will range from 0 to 255, with 255 being max opacity

	//the highest version of OpenGL we want to develop for is 3.3, so we want to tell OpenGL that is the highest we will go
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);	//OpenGL 3
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);	//OpenGL 3.3

	//now we need to tell OpenGL how often we want it to update
	SDL_GL_SetSwapInterval(1);	//Every 1 millisecond the screen will be updated

	//we also want to avoid any sort of hard edges where the triangles meet
	//we will tell OpenGL directly to use the smooth shading model
	glShadeModel(GL_SMOOTH);	//this will make the sprites we load look much less divided

	//we always want the backs of any triangles drawn to be ignored for performance
	glCullFace(GL_BACK); //this will ignore the back side of the triangles drawn
	//when any triangle is drawn to the screen, draw it in a clockwise formation
	glFrontFace(GL_CW);
	//now enable culling
	glEnable(GL_CULL_FACE);

	//we want to be able to adjust the color values of our sprites on the fly and enable transparency
	//we will enable color blending for this
	glEnable(GL_BLEND); //enable the engine to do color blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//enable the source image's alpha to be read and allow it to be transparent

	//the clear color for the engine will be black
	glClearColor(0,0,0,255);	//use a solid black, hence why the alpha is at 255 (full opacity)

	//we need to set the viewport for the engine
	//the viewport will show us how much of the scene we can see
	//it is effectively the resolution of the scene
	//before we do this, we'll want to get the current size of the window
	int w,h;	//we need to create two integers to retrieve the height
	//the function we use is a pass by reference SDL function that will get the current size of the window
	SDL_GetWindowSize(this->window, &w, &h);	//this will put the size in the w and h variables
	//now we can set the viewport
	glViewport(0,0,w,h); //because the window is just created, we don't need to call the recalc function to modify it yet

	//now we want to make sure that we are modifying the perspective of the scene
	//the modes where we modify our OpenGL scene or objects is known as a matrix
	//in this case, we are modifying our projection matrix, which will change how objects are seen from the camera
	glMatrixMode(GL_PROJECTION);	//set the active matrix to the projection matrix
	glLoadIdentity();	//LOAD THE MATRIX, IF THIS STEP IS SKIPPED IT WILL NOT CHANGE THE MATRIX

	//set our perspective to a flat, orthographic view.
	//set up the ortho view first
	gluOrtho2D(0,w,h,0);	//this will change how objects are drawn to the screen using the size of our window
	gluPerspective(
		0.0,				//the perspective will be completely flat
		(float)w/(float)h,	//the aspect ratio is still in place, this will be adjusted with the recalc function
		0.0,				//the closest we see our 2D objects is at 0, which is where our camera is located
		1024.0				//the furthest point we should see our objects would be at 1, but this doesn't need to change TODO
	);
	//because our engine is mostly 2D, these values may not change

	//once all of this has been done, we can set the isrunning variable to true

	this->isrunning = true;
}

bool Engine::getRunning(){
	//not much to it, just get the isrunning variable and return it
	return this->isrunning;
}

void Engine::clearScreen(){
	//this function must do four things:
	//1) get the first tick of the loop
	//2) update the window's functions
	//3) recalculate the size of the renderer
	//4) refresh the screen
	//we just need to use the variable built into the engine called firsttick, which is a 32 bit integer
	//it just keeps track of how many ticks it takes to get from the clear to the draw
	//this is used for updating the frames
	this->firsttick = SDL_GetTicks();

	//to update the window we need to use an event variable
	SDL_Event event;	//this will control our actual window's events
	//now we need to poll each possible event
	while (SDL_PollEvent(&event)){
		if (event.type == SDL_QUIT){
			//if the X at the top right of the screen is clicked, the running variable will break the loop
			this->isrunning = false;
		}
	}
	//now that the window is being handled and we have the first tick, we must recalculate the renderer
	this->recalcRenderer();	//TODO implement the code for this later!!!

	//this will clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//the drawing will happen beneath this function but before the drawscreen function
}

void Engine::drawScreen(){
	//the drawscreen function is responsible for updating the screen with the graphics necessary
	//this function will only update at a specified interval
	//we need to know how long it would supposedly take to get to this point
	double frameDel = 1000.0 / this->framerate; //disclaimer: this is measured in mseconds so every 1000 mseconds is a second
	double frameTime = SDL_GetTicks() - this->firsttick; //this will retrieve how long it actually took to get to this point
	if (frameTime < frameDel){
		//if the time it is expected to take is greater than it actually took
		//we want to delay for that long in mseconds
		SDL_Delay(static_cast<Uint32>(frameDel - frameTime)); //must be cast to a Uint32 to avoid annoying warnings
		//This will guarantee that our engine updates NO FASTER than the FPS specified
	}
	//finally, swap the window (aka update the screen)
	SDL_GL_SwapWindow(this->window);
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
	//this will simply set the FPS of the engine through the framerate variable
	this->framerate = newFPS;
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


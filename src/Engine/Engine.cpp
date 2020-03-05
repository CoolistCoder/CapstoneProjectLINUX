

#include "Engine.h"

void Engine::recalcRenderer(){
	//TODO maybe improve this to scale better with the window?
	//this function needs to adjust the renderer's size according to the height of the window
	float ratio; //the ratio that will be calculated
	int scaleW, scaleH; //this is the adjusted scale of the renderer
	int currentW, currentH;	//this is the current size of the window

	SDL_GetWindowSize(this->window, &currentW, &currentH); //store the size of the window in the currentW/H variables
	ratio = (float)this->windowW / (float)this->windowH; //we need the ratio of the scene
	scaleH = currentH; //in order for the scene to look "correct" we need an axis to scale to.  We'll use the Y axis.
	scaleW = currentH * ratio; //as such, our width is adjusted according to the ratio

	//now we need to adjust the viewport accordingly
	//we want the viewport centered on the screen, and adjusted in scale to the scale variables
	glViewport((currentW/2)-(scaleW/2),(currentH/2) - (scaleH/2),scaleW,scaleH);
	//this will produce a window that scales fairly well with the window
}

void Engine::init(){
	//first, begin the process of initialization
	//because we want to initialize SDL as a whole for now,
	//we'll use the everything flag for initializing SDL2
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
		//we want to be a little more specific and attach an actual error to the error message now
		std::string errmsg = "UNABLE TO INIT SDL: ";	//we'll use the same error dialog
		errmsg.append(SDL_GetError());	//but we'll add the error message to the string

		//failure to init occurs if the value of SDL_Init is less than 0
		//we want to show a simple message box that will tell the user that something went wrong
		SDL_ShowSimpleMessageBox(
		SDL_MESSAGEBOX_ERROR,	//create a messagebox with an error icon
		"ERROR",				//the title of the error should just be "error" to describe what kind of box it is
		errmsg.c_str(),	//a simple description of the error
		nullptr					//our window is currently null, so we should just use nullptr
		);
		//we must break from the init
		return;
	}

	//if the first init phase works, then we can move onto step two
	//we must initialize the image module
	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)<1){
		//we want to be a little more specific and attach an actual error to the error message now
		std::string errmsg = "UNABLE TO INIT SDL: ";	//we'll use the same error dialog
		errmsg.append(SDL_GetError());	//but we'll add the error message to the string

		//IMG init fails if the value returned is 0
		//the error message is largely the same
		SDL_ShowSimpleMessageBox(
		SDL_MESSAGEBOX_ERROR,	//create a messagebox with an error icon
		"ERROR",				//the title of the error should just be "error" to describe what kind of box it is
		errmsg.c_str(),	//a simple description of the error
		nullptr					//our window is currently null, so we should just use nullptr
		);
		//break the function
		return;
	}

	//due to an error in the Ubuntu version of SDL2_mixer, OpenAudio must be called first apparently
	//this may not be necessary in the Windows version, be aware
	Mix_OpenAudio(
			44100, //The range of frequency that the sound is given
			MIX_DEFAULT_FORMAT,	//use default settings when using the sound
			2,		//we want two channels for audio
			1024);	//the amount of bytes per sample (the higher, the clearer)

	//the final step is similar to the first two steps
	//we must initialize the mixer module
	if (Mix_Init(MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG)<1){
		//we want to be a little more specific and attach an actual error to the error message now
		std::string errmsg = "UNABLE TO INIT SDL: ";	//we'll use the same error dialog
		errmsg.append(SDL_GetError());	//but we'll add the error message to the string

		//MIX init also fails if the value returned is 0
		//the error message is still mostly the same
		SDL_ShowSimpleMessageBox(
		SDL_MESSAGEBOX_ERROR,	//create a messagebox with an error icon
		"ERROR",				//the title of the error should just be "error" to describe what kind of box it is
		errmsg.c_str(),	//a simple description of the error
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
	//Close open audio channels
	Mix_CloseAudio();

	//clear out the context
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
	//finally, we may implement the quit functions
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
	//this function will close any resources that SDL uses
	//this will finish up the exit process, and the program will quit without any leaks
}

void Engine::makeWindow(unsigned int w, unsigned int h, std::string title){
	if (this->success && !this->window){ //we only want to create a window if we can successfully initialize the engine!
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
			//if we succeeded, we can give the window and renderer sizes our values
			this->windowW = w;	//at the start, the window's size is the same as what we specify above
			this->windowH = h;
			this->rendererW = this->windowW; //until we change the resolution, the renderer's size is equal to the window
			this->rendererH = this->windowH;

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
	SDL_GL_SetSwapInterval(0);	//disable VSync

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
	//5) update all of the joysticks
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

	//Now we need to redetect all of the joysticks
	if (!this->alljoysticks.empty()){
		//As long as there are joystick objects we can perform this step
		for (int i=0;i<Joystick::getTotalJoysticks();i++){
			//for each joystick found, we simply call the detect function
			this->alljoysticks.at(i)->detect();
			//this will force all of the joysticks to be detected
		}
	}
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

void Engine::setPosition(int x, int y){
	//SDL contains simple functions for modifying the window's properties
	SDL_SetWindowPosition(this->window, x, y);
	//these are extremely simple, and are based on the pixel position of a window's top left corner
}

void Engine::setSize(unsigned int w, unsigned int h){
	//like the previous position function, we can do the same with the size
	//we also need to save this new size for recalcRenderer
	this->windowW = w;
	this->windowH = h;
	SDL_SetWindowSize(this->window, w, h);
	//we also need to recenter the window
	this->setPosition(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	//an unsigned int cannot be negative, so inherently this would work
}

void Engine::setName(std::string newname){
	//make sure the newname variable is not empty before setting the window's title!!!
	if (!newname.empty()){
		//we can again, use a simple function to set the title of the window
		SDL_SetWindowTitle(this->window, newname.c_str());
	}
}

void Engine::setResolution(unsigned int w, unsigned int h){
	//this can be achieved with a simple call to gluortho
	//however, we want to make sure that we have the correct matrix mode set
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	//load the identity of the matrix mode
	gluOrtho2D(0,w,h,0);	//now call gluortho
	this->rendererW = w; //now adjust the renderer variables accordingly
	this->rendererH = h;
	//Being able to set the resolution within the window is intended behavior, even if it's much larger
}

void Engine::maximizeWindow(){
	//All this will do is maximize the game's window to the screen
	SDL_MaximizeWindow(this->window);
}

void Engine::restoreWindow(){
	//this will set the scale of the window back to normal
	SDL_RestoreWindow(this->window);
}

void Engine::fullscreenWindow(){
	//this will set the window to fullscreen
	SDL_SetWindowFullscreen(this->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	//keep in mind this is a maximized borderless window
}

void Engine::normalscreenWindow(){
	//this will return the window from fullscreen
	SDL_SetWindowFullscreen(this->window, 0);
}

void Engine::stop(){
	//set isrunning to false
	this->isrunning = false;
	//this will kill any typical loop
}

void Engine::setFPS(unsigned int newFPS){
	//this will simply set the FPS of the engine through the framerate variable
	this->framerate = newFPS;
	//Because this is an unsigned int, it cannot be negative, so this will prevent any negative values by design
}

bool Engine::getKey(SDL_Scancode key){
	//we need to make sure that the input value is not invalid
	if (key >= 0 || key < 256){
		//in order to get key input, we need an array of all of the possible keys
		//A Uint8 is just big enough to be a candidate for this array
		const Uint8* whichkey = SDL_GetKeyboardState(NULL);
		//Now, whichkey is a simple array that contains all of the possible keyboard states
		//we can use this to get the precise key we're looking for
		if (whichkey[key]){
			//If the key at the specified scancode is active, then we return true
			return true;
		}
	}
	//in all other circumstances, we return false for this function
	return false;
	//this allows us to take multiple key inputs
}

void Engine::addJoystick(Joystick* newjoystick){
	//as long as the new joypad is not null we can add it to the joystick vector
	if (newjoystick){
		this->alljoysticks.push_back(newjoystick);
	}
}

Joystick* Engine::getJoystick(unsigned int index){
	if (!this->alljoysticks.empty()){ //make sure we have a joystick
		if (index < this->alljoysticks.size()){ //if we have more than one joystick return the correct index
			return this->alljoysticks.at(index);
		}
		return this->alljoysticks.at(0); //if the index is invalid, return player 1
	}
	return nullptr; //return nullptr if we have no joysticks
}

Engine::Engine() {
	//begin by setting the defaults of everything
	this->context = 0; //don't need the context yet
	this->window = nullptr;		//no window has been created
	this->isrunning = false;	//the window is not running, therefore this is false for now
	this->success = false;	//the engine has not been initialized, therefore it is not successfully initialized
	this->framerate = 60;	//by default, the engine runs at 60 hrz
	this->windowW = 640;	//we want to use a simple frame size as a default so we don't accidentally cause and error
	this->windowH = 480;	//same on the window's height
	//the renderer's size can match the window's when we start
	this->rendererW = this->windowW;
	this->rendererH = this->windowH;

	this->init();	//perform the init after the engine's default values have been set

}

Engine::~Engine() {
	//clear out the engine once it has been deleted
	this->end();
}



#include "Player.h"

void Player::control(Entity* p){
	//make the player a fleshy color
	static_cast<Player*>(p)->modifyColor(255, 203, 209);

	//set the player's frame to 0
	static_cast<Player*>(p)->setFrame(0);

	//make sure the fire key isn't being pressed
	if (!Engine::getKey(SDL_SCANCODE_LCTRL)){
		//make the player move around
		if (Engine::getKey(SDL_SCANCODE_DOWN)){
			static_cast<Player*>(p)->moveDown();
		}
		if (Engine::getKey(SDL_SCANCODE_UP)){
			static_cast<Player*>(p)->moveUp();
		}
		if (Engine::getKey(SDL_SCANCODE_LEFT)){
			static_cast<Player*>(p)->moveLeft();
		}
		if (Engine::getKey(SDL_SCANCODE_RIGHT)){
			static_cast<Player*>(p)->moveRight();
		}
	}
	else{
		//TODO perform the fire
		static_cast<Player*>(p)->setFrame(3);
	}

	//we need to check against all walls.  If the player knows it has walls, we need to die when we collide with them
	if (static_cast<Player*>(p)->walls){
		//if the player knows about the walls
		for (unsigned int i=0; i<static_cast<Player*>(p)->walls->tileQuantity(); i++){
			//check each tile to see if a collision has occured
			if (static_cast<Player*>(p)->walls->getTile(i)->collideAgainst(static_cast<Player*>(p)) &&
					static_cast<Player*>(p)->walls->getTile(i)->isFrame(1)){
				//this determines whether or not the player is colliding with a tile that happens to be a wall
				static_cast<Player*>(p)->setBehavior(Player::die); //make it die
			}
		}
	}

	//now draw the player
	static_cast<Player*>(p)->draw();
}

void Player::die(Entity* p){
	static_cast<Player*>(p)->modifyColor(255,255,0);

	static int waitstatic = 0;
	waitstatic++;
	if (waitstatic > 2){
		//we need to make the player electrocute and restart
		if (static_cast<Player*>(p)->frame != 0 && static_cast<Player*>(p)->frame != 4){
			//if the frame of the sprite is neither 1 or 5
			//we want to set it to 0
			static_cast<Player*>(p)->frame = 0;
		}
		else{
			//if the frame is 1 or 5 we want to alternate between them
			if (static_cast<Player*>(p)->frame == 0){
				static_cast<Player*>(p)->frame = 4;
			}
			else{
				static_cast<Player*>(p)->frame = 0;
			}
		}
		waitstatic = 0;
	}


	static_cast<Player*>(p)->draw();

	//increment waittime until it reaches the point it needs to be at
	static_cast<Player*>(p)->waittime++;
	if (static_cast<Player*>(p)->waittime > static_cast<Player*>(p)->deathwait){
		static_cast<Player*>(p)->waittime = 0; //the waittime is reset
		static_cast<Player*>(p)->setBehavior(Player::setup); //reset the object
	}

}

void Player::setup(Entity* p){
	//this function sets up the default values for the player
	//give the player its appropriate sprite
	static_cast<Player*>(p)->loadImage("guy.png");
	//set up the properties for the sprite
	static_cast<Player*>(p)->setFrameCount(5,1); //5 tiles across, 1 down
	static_cast<Player*>(p)->setSize(12,16); //make the sprite about as big as its frame
	static_cast<Player*>(p)->setPosition(1920/8, 1080/8);

	//at the end of setup, switch to control mode
	static_cast<Player*>(p)->setBehavior(Player::control);

}

void Player::moveDown(){
	//set the frame appropriately
	if (walkDelayTimer < walkDelayMax){
		walkDelayTimer++; //increment the walkdelaytimer as long as it is lower than the max
	}
	else{
		//reset the timer and toggle the frame
		this->walkFrame++;
		if (this->walkFrame > 2){
			this->walkFrame = 1;
		}
		walkDelayTimer = 0;
	}
	this->setFrame(walkFrame); //set this to the walkframe

	//just move and update the position
	this->y++;
	this->setPosition(this->x, this->y);
}

void Player::moveUp(){
	//set the frame appropriately
	if (walkDelayTimer < walkDelayMax){
		walkDelayTimer++; //increment the walkdelaytimer as long as it is lower than the max
	}
	else{
		//reset the timer and toggle the frame
		this->walkFrame++;
		if (this->walkFrame > 2){
			this->walkFrame = 1;
		}
		walkDelayTimer = 0;
	}
	this->setFrame(walkFrame); //set this to the walkframe
	//just move and update the position
	this->y--;
	this->setPosition(this->x, this->y);

}

void Player::moveLeft(){
	//set the frame appropriately
	if (walkDelayTimer < walkDelayMax){
		walkDelayTimer++; //increment the walkdelaytimer as long as it is lower than the max
	}
	else{
		//reset the timer and toggle the frame
		this->walkFrame++;
		if (this->walkFrame > 2){
			this->walkFrame = 1;
		}
		walkDelayTimer = 0;
	}
	this->setFrame(walkFrame); //set this to the walkframe

	//make sure to mirror properly
	this->activateHorizontalFlip();

	//just move and update the position
	this->x--;
	this->setPosition(this->x, this->y);

}

void Player::moveRight(){
	//set the frame appropriately
	if (walkDelayTimer < walkDelayMax){
		walkDelayTimer++; //increment the walkdelaytimer as long as it is lower than the max
	}
	else{
		//reset the timer and toggle the frame
		this->walkFrame++;
		if (this->walkFrame > 2){
			this->walkFrame = 1;
		}
		walkDelayTimer = 0;
	}
	this->setFrame(walkFrame); //set this to the walkframe

	//make sure to mirror properly
	this->deactivateHorizontalFlip();

	//just move and update the position
	this->x++;
	this->setPosition(this->x, this->y);
}

void Player::wallIs(Tilemap* w){
	if (w){
		this->walls = w; //give the player the wall data if it is valid
	}
}

void Player::execute(){
	//execute the stored behavior
	this->storedBehavior(this);
}

Player::Player() {
	// TODO Auto-generated constructor stub
	//run the setup function
	this->setBehavior(Player::setup);

	this->walkDelayTimer = 0;
	this->walkFrame = 1;

	//starting off, we have no data
	this->walls = nullptr;
	this->laser = nullptr;

	//we haven't died yet so waittime is 0
	this->waittime = 0;

}

Player::~Player() {
	// TODO Auto-generated destructor stub
}


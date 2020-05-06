
#include "Player.h"

void Player::control(Entity* p){
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

	//now draw the player
	static_cast<Player*>(p)->draw();
}

void Player::die(Entity* p){

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

}

Player::~Player() {
	// TODO Auto-generated destructor stub
}


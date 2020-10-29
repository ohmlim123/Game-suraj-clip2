#include "Player.h"

//Initializer Function
void Player::initVariables()
{

}

void Player::initComponents()
{
	this->createMovementComponent(300.f,15.f,5.f);
}


//Contructor / Destructor
Player::Player(float x , float y , sf::Texture& texture)
{
	this->initVariables();
	this->initComponents();

	this->setTexture(texture);
	this->setPosition(x, y);
}

Player::~Player()
{

}

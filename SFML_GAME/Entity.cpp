#include"Entity.h"
void Entity::iniVarialbe()
{
	
	
	
	this->movementcomponent = NULL;
}
Entity::Entity()
{
	this->iniVarialbe();
}

Entity::~Entity()
{
	delete this->movementcomponent;
	delete this->animationComponent;
}

//Component Function
void Entity::setTexture(sf::Texture& texture)
{
	
	this->sprite.setTexture(texture);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
	this->movementcomponent = new MovementComponent(this->sprite, maxVelocity,acceleration,deceleration);
}

void Entity::createAnimationComponent( sf::Texture& texture_sheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}



// Functions

void Entity::setPosition(const float x, const float y)
{
		this->sprite.setPosition(x,y);
}

void Entity::move(const float dir_x, const float dir_y, const float& dt )
{
	if (this->movementcomponent)
	{
		this->movementcomponent->move(dir_x, dir_y,dt); // Set Velocity
	}
	
}

void Entity::update(const float& dt)
{
	
}

void Entity::render(sf::RenderTarget * target)
{
	
	
		target->draw(this->sprite);

	

}



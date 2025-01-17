#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H




enum movement_states
{
	IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN,
	WAIT_LEFT, WAIT_RIGHT, WAIT_DOWN,JUMP

};

class MovementComponent
{
private:

	sf::Sprite& sprite;

	float maxVelocity;
	float acceleration;
	float deceleration;
	float gravity;
	


	sf::Vector2f velocity;
	
	//Initializer functions


public:
	MovementComponent(sf::Sprite& sprite, 
		float maxVelocity, float acceleration, float deceleration);
	virtual ~MovementComponent();

	//Accessors
	const float& getMaxVelocity() const;
	const sf::Vector2f& getVelocity() const;

	//Function
	
	const bool getState(const short unsigned state) const;
	void stopVelocity();
	void stopVelocityX();
	void speedup();
	void speeddown();
	void stopVelocityY();
	void updategravity();
	void jump(float jump_height);
	void bounce(const float dir_x, const float dir_y, const float x_force, const float y_force, const float& dt);
	const float get_gravity();
	void set_gravity(float gravitate);
	
	
	
	void move(const float x, const float y,const float& dt);
	void update(const float& dt);
};
#endif


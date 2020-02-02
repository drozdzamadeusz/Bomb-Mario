/** @file */
#pragma once
#include "Animation.hpp"

// Player class
/**
 * Defines player animations and behavior
 */
class Player {
public:
	/**
	 * Basic class constructor
	 * @param sprite sheet of player texuture
	 * @param number of horizontal and vertical images
	 * @param time after which the player picture change
	 * @param player maximum speed
	 * @param player maximum jump height
	*/
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight);

	/**
	 * Class destructor
	 */
	~Player();

	/**
	 * Update the logic of the player - movement and animation
	 */
	void update(float deltaTime);

	/**
	 * Draw player sprint on the screen
	 */
	void draw(sf::RenderWindow& window);

	/**
	 * Set position of the player
	 *
	 * @param horizontal positon
	 * @param vertical position
	 */
	void setPosition(int x, int y);

	/**
	 * Return position of the player
	 */
	sf::Vector2f getPosition();

	/**
	 * Get body of the player - rectangular box
	 */
	sf::RectangleShape getBody();
	
private:
	sf::RectangleShape _body; ///< body of the player 
	Animation _animation; ///< player animation
	unsigned int _row; ///< current displayed row in animation
	float _speed; ///< player maximum speed
	float _jumpHeight; ///< player maximum jump height
	float _speedMultiply; ///< player multiply factor
	bool _faceRight;///< option if player image should be flipped X
	
	sf::Vector2f _velocity; ///< player current velocity
	bool _canJump; ///< option if player can jump
	bool _isJumping; ///< state if player is currently jumping
};

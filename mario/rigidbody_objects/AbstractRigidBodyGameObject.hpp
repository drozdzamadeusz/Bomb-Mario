#pragma once

#include "../GameObject.hpp"

//! AbstractRigidbodyGameObject class
/**
 * Moving game object in game
 * Inherits GameObject class - every moving object also has a static object properties 
*/
class AbstractRigidbodyGameObject : public GameObject {
public:
	/**
	 * Basic class constructor without any parameters - empty object
	*/
	AbstractRigidbodyGameObject() :GameObject(), _disposeObject(false), _colldedWithPlayer(false) {};

	/**
	 * Class constructor with adjustable width and height of an moving object
	 *
	 * @param object width
	 * @param object height
	*/
	AbstractRigidbodyGameObject(int width, int height) :GameObject(width, height), _disposeObject(false), _colldedWithPlayer(false) {};

	/**
	 * Update the logic of an moving object
	 * Because every moving object behaves differently this is pure virtual method so it must be overwritten in inheriting classes
	 */
	virtual void update(float deltaTime) = 0;


	/**
	 * Return whether given object is rigidbody
	 */
	virtual bool isRigidbody()
	{
		return _isRigidbody;
	};

	/**
	 * Draw object on the screen
	 * This is pure virtual method so it must be overwritten in inheriting classes
	 */
	virtual void draw(sf::RenderWindow& window) = 0;


	/**
	 * Set position of object
	 *
	 * @param horizontal positon
	 * @param vertical position
	 */
	virtual void setPosition(int x, int y){
		this->_body.setPosition(x, y);
	}

	/**
	 * Return position of object
	 */
	virtual sf::Vector2f getPosition(){
		return this->_body.getPosition();
	}

	/**
	 * Get body of the player - rectangular box
	 */
	virtual sf::RectangleShape getBody()
	{
		return _body;
	}

	/**
	 * Returns if moving object collided with player
	 */
	virtual bool hasColldedWithPlayer() { return _colldedWithPlayer;  };

	/**
	 * Set object status to already collided with player
	 */
	virtual void setColldedWithPlayer(bool colldedWithPlayer) { _colldedWithPlayer = colldedWithPlayer; };

	/**
	 * Set object status to be removed form the memory
	 */
	virtual bool disposeObject() { return _disposeObject; };
protected:
	bool _isRigidbody; ///< whether object is rigidbody
	bool _disposeObject; ///< object has to be removed form the memory
	bool _colldedWithPlayer; ///< object collided with player
	sf::RectangleShape _body;///< object rectangular body
};

#include "Bomb.hpp"
#include <iostream>

Bomb::Bomb() : AbstractRigidbodyGameObject(), _animation(nullptr, sf::Vector2u(0, 0), 1) {

}

Bomb::Bomb(sf::Texture* texture, sf::Vector2u dimensions, sf::Vector2u imageCount, sf::Vector2f bombSpeed, float bombAcceleration, float rotation) :
	AbstractRigidbodyGameObject(dimensions.x, dimensions.y),
	_animation(texture, imageCount, 0.1f),
	_animationImageCount(imageCount),
	_bombSpeed(bombSpeed),
	_row(0),
	_explodingTimer(0.45f)
{
	this->_body.setSize(sf::Vector2f(dimensions.x, dimensions.y));
	this->_body.setTexture(texture);
	this->_body.setOrigin(dimensions.x / 2.0f, dimensions.y / 2.0f);
	this->_body.rotate(rotation);
}


Bomb::~Bomb(){
}

void Bomb::update(float deltaTime) {

	if(_colldedWithPlayer)
	{
		_explodingTimer -= deltaTime;
		if(_explodingTimer <= 0)
		{
			_disposeObject = true;
		}
	}
	
	this->_velocity = _bombSpeed;
	
	this->_animation.update(this->_row, deltaTime, false, false, false);
	this->_body.setTextureRect(this->_animation.uvrect);
	
	if(!_colldedWithPlayer) this->_body.move(this->_velocity * deltaTime);
}

void Bomb::draw(sf::RenderWindow& window) {
	window.draw(this->_body);
}

sf::RectangleShape Bomb::getBody()
{
	return _body;
}

void Bomb::setTexture(sf::Texture* texture)
{
	_animation  = Animation(texture, _animationImageCount, 0.15f);
	this->_body.setTexture(texture);
}



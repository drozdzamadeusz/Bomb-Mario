#include "Apple.hpp"

Apple::Apple() : AbstractRigidbodyGameObject(), _animation(nullptr, sf::Vector2u(0, 0), 1) {

}

Apple::Apple(sf::Texture* texture, sf::Vector2u dimensions, sf::Vector2u imageCount, sf::Vector2f bombSpeed, float bombAcceleration, float rotation) :
	AbstractRigidbodyGameObject(dimensions.x, dimensions.y),
	_animation(texture, imageCount, 0.1f),
	_bombSpeed(bombSpeed),
	_row(0)
{
	this->_body.setSize(sf::Vector2f(dimensions.x, dimensions.y));
	this->_body.setTexture(texture);
	this->_body.setOrigin(dimensions.x / 2.0f, dimensions.y / 2.0f);
	this->_body.rotate(rotation);
}


Apple::~Apple() {
}

void Apple::update(float deltaTime) {
	this->_velocity = _bombSpeed;

	this->_animation.update(this->_row, deltaTime, false, false, false);
	this->_body.setTextureRect(this->_animation.uvrect);
	this->_body.move(this->_velocity * deltaTime);
}

void Apple::draw(sf::RenderWindow& window) {
	window.draw(this->_body);
}

sf::RectangleShape Apple::getBody()
{
	return _body;
}


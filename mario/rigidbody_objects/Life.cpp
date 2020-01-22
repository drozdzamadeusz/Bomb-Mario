#include "Life.hpp"


Life::Life() : AbstractRigidbodyGameObject(), _animation(nullptr, sf::Vector2u(0, 0), 1) {

}

Life::Life(sf::Texture* texture, sf::Vector2u dimensions, sf::Vector2u imageCount, sf::Vector2f bombSpeed, float bombAcceleration, float rotation) :
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


Life::~Life() {
}

void Life::update(float deltaTime) {
	this->_velocity = _bombSpeed;

	this->_animation.update(this->_row, deltaTime, false, false, false);
	this->_body.setTextureRect(this->_animation.uvrect);
	this->_body.move(this->_velocity * deltaTime);
}

void Life::draw(sf::RenderWindow& window) {
	window.draw(this->_body);
}

sf::RectangleShape Life::getBody()
{
	return _body;
}
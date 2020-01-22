#include "Cloud.hpp"



Cloud::Cloud() : AbstractRigidbodyGameObject(), _animation(nullptr, sf::Vector2u(0, 0), 1) {

}

Cloud::Cloud(sf::Texture* texture, sf::Vector2u dimensions, sf::Vector2u imageCount, sf::Vector2f cloudSpeed, float shakeSpeed, float switchTime, float currentImage):
	AbstractRigidbodyGameObject(dimensions.x, dimensions.y),
	_animation(texture, imageCount, switchTime, currentImage),
	_shakeSwitchTime(shakeSpeed),
	_shakeTimer(0),
	_cloudSpeed(cloudSpeed),
	_row(0)
{
	_moveUp = (Utils::randomInt(0, 1) == 1);
	this->_body.setSize(sf::Vector2f(dimensions.x, dimensions.y));
	this->_body.setTexture(texture);
	this->_body.setOrigin(dimensions.x / 2.0f, dimensions.y / 2.0f);
}


Cloud::~Cloud() {
}

void Cloud::update(float deltaTime){

	this->_velocity = _cloudSpeed;
	this->_velocity.y = (_moveUp) ? -this->_velocity.y : this->_velocity.y;
	_shakeTimer += deltaTime;
	
	if(_shakeTimer >= _shakeSwitchTime)
	{
		_moveUp = !_moveUp;
		_shakeTimer = 0;
	}
	this->_animation.update(this->_row, deltaTime, false, false, false);
	this->_body.setTextureRect(this->_animation.uvrect);
	this->_body.move(this->_velocity * deltaTime);
}

void Cloud::draw(sf::RenderWindow& window) {
	window.draw(this->_body);
}

sf::RectangleShape Cloud::getBody()
{
	return _body;
}


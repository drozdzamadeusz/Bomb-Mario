/** @file */
#pragma once
#include "AbstractRigidbodyGameObject.hpp"
#include "../Animation.hpp"
#include "../Utils.hpp"

class Cloud : public AbstractRigidbodyGameObject
{
public:
	Cloud();
	Cloud(sf::Texture* texture, sf::Vector2u dimensions, sf::Vector2u imageCount, sf::Vector2f cloudSpeed, float shakeSpeed, float switchTime, float currentImage);
	~Cloud();

	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;

	sf::RectangleShape getBody() override;
private:
	Animation _animation;
	unsigned int _row;

	sf::Vector2f _cloudSpeed;
	float _shakeSwitchTime;
	sf::Vector2f _velocity;

	float _shakeTimer;
	float _moveUp;
};

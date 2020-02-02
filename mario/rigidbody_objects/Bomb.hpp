/** @file */
#pragma once

#include "AbstractRigidbodyGameObject.hpp"
#include "../GameObject.hpp"
#include "../Animation.hpp"


class Bomb : public AbstractRigidbodyGameObject {
public:
	Bomb();
	Bomb(sf::Texture* texture, sf::Vector2u dimensions, sf::Vector2u imageCount, sf::Vector2f bombSpeed, float bombAcceleration, float rotation);
	~Bomb();

	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;

	sf::RectangleShape getBody() override;
	void setTexture(sf::Texture* texture);
private:
	Animation _animation;
	sf::Vector2u _animationImageCount;
	unsigned int _row;
	
	sf::Vector2f _bombSpeed;
	float _speedMultiply;
	sf::Vector2f _velocity;
	
	float _explodingTimer;
};

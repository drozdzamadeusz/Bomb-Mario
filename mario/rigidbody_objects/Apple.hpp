/** @file */
#pragma once
#include "AbstractRigidbodyGameObject.hpp"
#include "../Animation.hpp"

class Apple : public AbstractRigidbodyGameObject {
public:
	Apple();
	Apple(sf::Texture* texture, sf::Vector2u dimensions, sf::Vector2u imageCount, sf::Vector2f bombSpeed, float bombAcceleration, float rotation);
	~Apple();

	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;

	sf::RectangleShape getBody() override;

private:
	Animation _animation;
	unsigned int _row;

	sf::Vector2f _bombSpeed;
	float _speedMultiply;
	sf::Vector2f _velocity;
};

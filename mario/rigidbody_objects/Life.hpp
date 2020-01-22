#pragma once
#include "AbstractRigidbodyGameObject.hpp"
#include "../Animation.hpp"

class Life : public AbstractRigidbodyGameObject {
public:
	Life();
	Life(sf::Texture* texture, sf::Vector2u dimensions, sf::Vector2u imageCount, sf::Vector2f speed, float acceleration, float rotation);
	~Life();

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

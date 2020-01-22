#include "Utils.hpp"


float Utils::randomFloat(float min, float max)
{
	float num = (float) rand() / RAND_MAX;
	return min + num * (max - min);
}

int Utils::randomInt(int min, int max)
{
	int range = max - min + 1;
	return rand() % range + min;
}

float Utils::calculateAngleOfRotationForVelocity(sf::Vector2f objectVelocity)
{
	return (((double)atan((-objectVelocity.x / objectVelocity.y)) * 180) / PI);
}

std::string Utils::resourcePath(void)
{
	return "assets/";
}

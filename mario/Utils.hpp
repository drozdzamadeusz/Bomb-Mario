/** @file */
#pragma once
#include <cmath>
#include <cstdlib>
#include <SFML/System/Vector2.hpp>
#include <string>

constexpr auto PI = 3.14159265;

//! Utils
/**
 * Useful tool used in many classes
 */
class Utils{
	public:
		/**
		 * Generate random float number
		 */
		static float randomFloat(float min, float max);

		/**
		 * Generate random integer number
		 */
		static int randomInt(int min, int max);

		/**
		 * Calculate angle of rotation for velocity to tilt the object in the direction of falling
		 * -objectVelocity.x / objectVelocity.y)) * 180) / PI = tan(x)
		 * where x is searched number
		 */
		static float calculateAngleOfRotationForVelocity(sf::Vector2f objectVelocity);

		/**
		 * Returns default assets folder
		 */
		static std::string resourcePath(void);
};

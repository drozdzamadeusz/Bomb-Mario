/** @file */
#pragma once
#include <SFML/Graphics.hpp>

//! Animation class
/**
 * Animates a game object
*/
class Animation {
public:
	/**
	 * Basic class constructor
	 * @param sprite sheet texuture
	 * @param number of horizontal and vertical images
	 * @param time after which the picture change
	*/
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);

	/**
	 * Class constructor with the option of choosing the first texture
	 *
	 * @param sprite sheet texuture
	 * @param number of horizontal and vertical images
	 * @param time after which the picture change
	 * @param first displayed image
	*/
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float currentImage);

	/**
	 * Box with current texture
	*/
	sf::IntRect uvrect;

	/**
	 * Update sprie - change texture
	 *
	 * @param default row
	 * @param time difference between previous frame 
	 * @param flip horizontal texture
	 * @param default vertical image
	 */
	void update(int row, float deltaTime, bool flipX, bool secondRow, bool defaultV);
	
private:

	/**
	 * Number of horizontal and vertical images
	 */
	sf::Vector2u _imageCount;

	/**
	 * Current displayed image
	 */
	sf::Vector2u _currentImage;


	/**
	 * Sprite total show time
	 */
	float _totalTime;

	/**
	 * Time of displaying of one texture
	 */
	float _switchTime;
};

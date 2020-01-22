// Platform class
// Mario can run or jump on it
#pragma once

#include <SFML/Graphics.hpp>

//! GameObject class
/**
 * Simple static object in game
*/
class GameObject {
public:

    /**
	 * Basic class constructor without any parameters
    */
    GameObject();

    /**
     * Class constructor with adjustable width and height of an object
     *
     * @param object width
     * @param object height
    */
    GameObject(int width, int height);

    /**
	 * Class destructor
	*/
    ~GameObject();

    /**
     * Adjusts the width and height of the object
    */
    void setPosition(float x, float y);

	/**
	 * Return the size of object
	*/
    sf::Vector2f getPosition();

    /**
     * Draw the object on selected window
    */
    void draw(sf::RenderWindow& window);

    /**
     * Set the texture of object
    */
    void setTexture(std::string texturePath);

    /**
     * Get texture of object
	*/
    sf::Texture getTexture();

    /**
     * Set whatever the object's texture should be tiled
     */
    bool setTextureRepeat(bool repeat);

    /**
	 * Get rectangle of object
	*/
	sf::IntRect getRectangle() const;
protected:
    sf::IntRect _rect; ///< Rectangle of object
    sf::Texture _texture; ///< Texture of object
    sf::Sprite _sprite; ///< Sprite of object
    bool _textureRepeat; ///< Texture repeat option
};

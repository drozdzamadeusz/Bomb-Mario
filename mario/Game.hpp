#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.hpp";
#include "GameObjectManager.hpp"

#include "Player.hpp"
#include "Utils.hpp"

#include "rigidbody_objects/AbstractRigidBodyGameObject.hpp"

#include "rigidbody_objects/Bomb.hpp"
#include "rigidbody_objects/Apple.hpp"
#include "rigidbody_objects/Cloud.hpp"
#include "rigidbody_objects/Life.hpp"


//! Game class
/**
 * Controls all game objects, events and rendering
*/
class Game {
public:
	Game();
	~Game();

	/**
	 * Initiation of a new game
	 * This method will re-initialize all dynamic content in the game
	*/
	void initGame();


	/**
	 * Initiation of a new round
	 * This method will initialize all variables in the game
	*/
	void initRound();

	/**
	 * Displayed window size
	*/
	float width, height;

	/**
	 * Displayed window size
	*/
	std::string title;


	/**
	 * All information about levels in the game
	 * Such as frequency of bombs falling, bomb falling speed, frequency of new life falling etc.
	*/
	struct Level
	{
		int levelDuration; ///< level duration
		std::string levelSlug; ///< level short name
		std::string levelDescription; ///< level description
		sf::Color levelColor; ///< color of level
		sf::Vector2f _bombDropFreqTimeRage; ///< frequency of bombs dropping
		sf::Vector2f _bombDropSpeedYRage; ///< speed of bomb dropping
		sf::Vector2f _appleDropFreqTimeRage; ///< frequency of apple dropping
		sf::Vector2f _cloudGenFreqTimeRage; ///< frequency of new clouds appearing
		sf::Vector2f _heartDropFreqTimeRage; ///< frequency of heart dropping
	};
	
	/**
	 * All possible game states
	*/
	enum GameState {
		RUNNING,
		EXITING,
		UNINITIALIZED,
		PAUSE
	};
	
	/**
	 * Method that is called to run the new game after the initialization of all variables
	*/
	void run(void);
private:
	/**
	 * Current state of the game
	*/
	GameState _gameState;

	/**
	 * Window that can serve as a target for 2D drawing
	*/
	sf::RenderWindow _window;

	/**
	 * Variable that defines the behavior of individual levels
	*/
	std::vector<Level> _levels = {
		{
			30,
			"I",
			"BEGINNER",
			sf::Color(13, 255, 0),
			sf::Vector2f(0.6f, 1.4f),
			sf::Vector2f(150, 360),
			sf::Vector2f(6, 15),
			sf::Vector2f(1.0f, 6),
			sf::Vector2f(8, 17)
		},
		{
			45,
			"II",
			"NORMAL",
			sf::Color(0, 225, 255),
			sf::Vector2f(0.3f, 0.9f),
			sf::Vector2f(180, 500),
			sf::Vector2f(6, 12),
			sf::Vector2f(1.0f, 6),
			sf::Vector2f(8, 17)
		},
		{
			60,
			"III",
			"ADVANCED",
			sf::Color(255, 255, 0),
			sf::Vector2f(0.2f, 0.65f),
			sf::Vector2f(200, 560),
			sf::Vector2f(5, 10),
			sf::Vector2f(1.0f, 6),
			sf::Vector2f(10, 17)
		},
		{
			90,
			"IV",
			"EXPERT",
			sf::Color(255, 17, 0),
			sf::Vector2f(0.2f, 0.45f),
			sf::Vector2f(220, 630),
			sf::Vector2f(5, 9),
			sf::Vector2f(1.0f, 6),
			sf::Vector2f(8, 17)
		},
		{
			0,
			"V",
			"LEGENDARY",
			sf::Color(0, 0, 0),
			sf::Vector2f(0.15f, 0.35f),
			sf::Vector2f(220, 650),
			sf::Vector2f(7, 10),
			sf::Vector2f(1.0f, 6),
			sf::Vector2f(8, 17)
		}
	};

	/**
	 * Static list of objects in game - background game objects such as ground or background
	*/
	GameObjectManager<GameObject> _gameStaticObjectsManager;


	/**
	 * Static list of objects in game - gui game objects such as gui backgorund or icons for number of lives
	*/
	GameObjectManager<GameObject> _gameStaticMenuObjects;

	/**
	 * Dynamic list of objects in game - moving (rigidbody) objects in game which are deleted and added to the memory during the game, such as bombs or points
	*/
	GameObjectManager<AbstractRigidbodyGameObject>* _gameRigidObjectsManager = nullptr;

	/**
	 * Method that creates a new dynamic objects - Bombs
	*/
	void dropNewBombs(float deltaTime);

	/**
	 * Method that creates a new dynamic objects - Apples (Points)
	*/
	void dropApple(float deltaTime);

	/**
	 * Method that creates a new dynamic objects - Hearts (new lifes)
	*/
	void dropHeartLifes(float deltaTime);

	/**
	 * Method that creates a new dynamic objects - Moving clouds
	*/
	void generateClouds(float deltaTime);

	/**
	 * Check whether the player has reached a new level, if so, increase the difficulty
	*/
	void handleNextLevels(Game::Level level, float deltaTime);

	/**
	 * Main game loop which is run each frame
	*/
	void _loop(Player& player);

	/**
	 * Main gui method which handle user interface in general
	*/
	void renderGui(float deltaTime);

	/**
	 * Draw gui - collected points
	*/
	void renderSocre(float deltaTime);

	/**
	 * Draw gui - current level
	*/
	void renderLevel(float deltaTime);

	/**
	 * Draw gui - available lives
	*/
	void renderLifes(float deltaTime);

	/**
	 * Draw gui - time counter
	*/
	void renderTimer(float deltaTime);

	/**
	 * Draw gui - if the player lost show the new reset screen
	*/
	void gameOverScreen();

	/**
	 * Increase the number of points scored by the player
	*/
	void appleCollected();
	
	/**
	 * Detect collisions in game
	 * player <-> all moving objets
	*/
	void detectCollisions(Player* player, GameObjectManager<AbstractRigidbodyGameObject>::Node* node);
	
	/**
	 * Check if the game state is not EXITING
	*/
	bool _isRunning(void);
	
	/**
	 * Variable that measures the elapsed time
	*/
	sf::Clock _timer;

	/**
	 * The time in seconds since the last frame
	*/
	float _deltaTime;

	/**
	 * Time since last bomb dropped
	*/
	float _lastBombDropTime;

	/**
	 * Time that must pass to a new bomb to be dropped
	*/
	float _bombDropFreqTime;

	/**
	 * Bomb animation texuture
	*/
	sf::Texture _bombTexture;

	/**
	 * Bomb explode animation texuture
	*/
	sf::Texture _bombExplodeTexture;

	/**
	 * Time since last apple dropped
	*/
	float _lastAppleDropTime;

	/**
	 * Time that must pass to a new apple to be dropped
	*/
	float _appleDropFreqTime;

	/**
	 * Apple texture holder
	*/
	sf::Texture _appleTexture;


	/**
	 * Time since last heart dropped
	*/
	float _lastHeartDropTime;

	/**
	 * Time that must pass to a new heart to be dropped
	*/
	float _heartDropFreqTime;

	/**
	 * Heart texture holder
	*/
	sf::Texture _heartTexture;
	

	/**
	 * Time since last cloud appeared
	*/
	float _lastGenCloudTime;

	/**
	 * Time that must pass to a new heart to be appear
	*/
	float _cloudGenFreqTime;

	/*
	 * Cloud texture holder
	*/
	sf::Texture _cloudTexture;

	/**
	 * Typeface used in game
	*/
	sf::Text _text;

	/**
	 * Font used in game
	*/
	sf::Font _font;

	/**
	 * Number of points corrected by player in one game
	*/
	int _score;


	/**
	 * Current number of lifes
	*/
	int _lifes;
	
	/**
	 * One game play time
	*/
	float _playTime;

	/**
	 * Time that must pass to start a new game
	*/
	float _gameOverResetTime;

	/**
	 * Current level
	*/
	short int _currentLevel;

	/**
	 * One level play time
	*/
	float _levelTrackTime;

	/**
	 * Method deletes all objects created during the game form the memory
	*/
	void disposeDynamicObjects();

	/**
	 * Remove form the memory all moving objects that have fallen out of the camera
	*/
	void disposeOffScreenObjects(GameObjectManager<AbstractRigidbodyGameObject>::Node* node);

	/**
	 * Draw all the objects on the screen
	*/
	void drawGameObjects(Player& player);

	/**
	 * Update logic of all moving objects
	*/
	void updateRigidBodyGameObjects(Player& player);

};

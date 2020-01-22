#include "Game.hpp"

Game::Game() :
	_gameState(UNINITIALIZED)
{
	srand(time(NULL));
	
	sf::RenderWindow _window;
    sf::Clock _timer;
    float _deltaTime;
	
	_bombTexture.loadFromFile(Utils::resourcePath() + "bomb.png");
	_appleTexture.loadFromFile(Utils::resourcePath() + "apple.png");
	_cloudTexture.loadFromFile(Utils::resourcePath() + "cloud.png");
	_heartTexture.loadFromFile(Utils::resourcePath() + "heart_anim.png");
	_bombExplodeTexture.loadFromFile(Utils::resourcePath() + "explode.png");
	
	if(!_font.loadFromFile(Utils::resourcePath() + "emulogic.ttf"))
	{
		std::exit(0);
	}
	
	_text.setFont(_font);
	_text.setCharacterSize(15);

	initGame();
}

void Game::initGame()
{
	disposeDynamicObjects();
	initRound();	
}

void Game::initRound()
{
	_bombDropFreqTime = (2.0f);
	_lastBombDropTime = (0.0f);
	
	_appleDropFreqTime = (5.0f);
	_lastAppleDropTime = (1.0f);
	

	_heartDropFreqTime = (4.0f);
	_lastHeartDropTime = (1.0f);
	
	_lastGenCloudTime = (2);
	_cloudGenFreqTime = (2);
	
	_score = (0);
	_lifes = (3);
	_gameOverResetTime = (5);
	_currentLevel = 1;
	_levelTrackTime = 0;
	_playTime = 0;
	
	delete _gameRigidObjectsManager;
	_gameRigidObjectsManager = new GameObjectManager<AbstractRigidbodyGameObject>();
}

void Game::run()
{
    if (_gameState != UNINITIALIZED){
        return;
    }

    _window.create(sf::VideoMode(width, height), title);

	_window.setVerticalSyncEnabled(true);
	
    _gameState = RUNNING;
 
    _deltaTime = 0.0f;

    sf::Texture playerTexture;
    playerTexture.loadFromFile(Utils::resourcePath() + "supermario.png");
	
    Player player(&playerTexture, sf::Vector2u(3, 2), 0.1f, 130.0f, 75);
    player.setPosition(0, height - 45);
    
    // set background for game
    GameObject background (Game::width, Game::height);
    background.setTexture(Utils::resourcePath() + "background.png");

    // ground
    GameObject p1(Game::width, 16);
    p1.setTextureRepeat(true);
    p1.setPosition(0, Game::height - 16);
    p1.setTexture(Utils::resourcePath() + "stage.png");

	_gameStaticObjectsManager.addItem(&background, "background");
    _gameStaticObjectsManager.addItem(&p1, "ground");

	// gui background
	GameObject guiBackground(Game::width, 66);
	guiBackground.setTexture(Utils::resourcePath() + "menu_background.png");
	guiBackground.setPosition(0, 0);
	guiBackground.setTextureRepeat(false);

	// heart empty
	GameObject heartEmpty(20, 16);
	heartEmpty.setTexture(Utils::resourcePath() + "heart_empty.png");
	heartEmpty.setTextureRepeat(false);

	// heart full
	GameObject heartFull(20, 16);
	heartFull.setTexture(Utils::resourcePath() + "heart_full.png");
	heartFull.setTextureRepeat(false);

	// gameover gui backgorund
	GameObject gameOverBackground(230, 98);
	gameOverBackground.setTexture(Utils::resourcePath() + "game_over_background.png");
	gameOverBackground.setTextureRepeat(false);
	gameOverBackground.setPosition(width / 2.0f - gameOverBackground.getRectangle().width / 2.0f, height / 2.0f - gameOverBackground.getRectangle().height / 2.0f);
	
	_gameStaticMenuObjects.addItem(&guiBackground, "guiBackground");
	_gameStaticMenuObjects.addItem(&heartEmpty, "heartEmpty");
	_gameStaticMenuObjects.addItem(&heartFull, "heartFull");
	_gameStaticMenuObjects.addItem(&gameOverBackground, "gameOverBackground");
	
    while (_isRunning()){
        _loop(player);
    }
	
    _window.close();
}


void Game::disposeOffScreenObjects(GameObjectManager<AbstractRigidbodyGameObject>::Node* node)
{
	if (node == nullptr) return;
	if ((node->gameObject->getPosition().y > width + node->gameObject->getRectangle().height + 300) ||
		(node->gameObject->getPosition().x < -300 || node->gameObject->getPosition().x > width + 300) ||
		(node->gameObject->disposeObject()))
	{
		_gameRigidObjectsManager->deleteItem(node);
	}
}


void Game::drawGameObjects(Player& player)
{
	//draw static objects
	GameObjectManager<GameObject>::Node* s = _gameStaticObjectsManager.getNodeHead();
	while (s != nullptr) {
		s->gameObject->draw(_window);
		s = s->next;
	}

	//draw moving objects
	GameObjectManager<AbstractRigidbodyGameObject>::Node* m = _gameRigidObjectsManager->getNodeHead();
	while (m != nullptr) {
		m->gameObject->draw(_window);
		m = m->next;
	}
}

void Game::updateRigidBodyGameObjects(Player& player)
{
	//refreshing moving objects
	GameObjectManager<AbstractRigidbodyGameObject>::Node* m = _gameRigidObjectsManager->getNodeHead();
	int i = 0;
	while (m != nullptr) {
		i++;
		m->gameObject->update(_deltaTime);
		detectCollisions(&player, m);
		disposeOffScreenObjects(m);
		m = m->next;
	}
}

void Game::dropNewBombs(float deltaTime)
{
	_lastBombDropTime += deltaTime;
	if(_lastBombDropTime >= _bombDropFreqTime){
		
		Level level = _levels.at(_currentLevel - 1);
		
		float posX = Utils::randomFloat(30, width - 30);
		float posY = 50;

		float speedX = Utils::randomFloat(20, 200);
		float speedY = Utils::randomFloat(level._bombDropSpeedYRage.x, level._bombDropSpeedYRage.y);

		
		if (Utils::randomInt(0, 1) == 1)
			speedX = -speedX;
		
		float rotate = Utils::calculateAngleOfRotationForVelocity(sf::Vector2f(speedX, speedY));

		
		Bomb* bomb = new Bomb(&_bombTexture, sf::Vector2u(18, 25), sf::Vector2u(3, 1), sf::Vector2f(speedX, speedY), 10, rotate);
		bomb->setPosition(posX, posY);
		_gameRigidObjectsManager->addItem(bomb, "bomb");

		_bombDropFreqTime = Utils::randomFloat(level._bombDropFreqTimeRage.x, level._bombDropFreqTimeRage.y);
		_lastBombDropTime = 0;
	}
}


void Game::dropApple(float deltaTime)
{
	_lastAppleDropTime += deltaTime;
	if (_lastAppleDropTime >= _appleDropFreqTime) {

		Level level = _levels.at(_currentLevel - 1);
		
		float posX = Utils::randomFloat(100, width - 100);
		float posY = 50;

		float speedX = Utils::randomFloat(5, 35);
		float speedY = Utils::randomFloat(100, 200);

		if (Utils::randomInt(0, 1) == 1) {
			speedX = -speedX;
		}

		float rotate = Utils::calculateAngleOfRotationForVelocity(sf::Vector2f(speedX, speedY));

		Apple* apple = new Apple(&_appleTexture, sf::Vector2u(16, 20), sf::Vector2u(3, 1), sf::Vector2f(speedX, speedY), 10, rotate);
		apple->setPosition(posX, posY);
		_gameRigidObjectsManager->addItem(apple, "apple");

		_appleDropFreqTime = Utils::randomFloat(level._appleDropFreqTimeRage.x, level._appleDropFreqTimeRage.y);
		_lastAppleDropTime = 0;
	}
}

void Game::dropHeartLifes(float deltaTime)
{
	_lastHeartDropTime += deltaTime;
	if (_lastHeartDropTime >= _heartDropFreqTime) {

		Level level = _levels.at(_currentLevel - 1);

		float posX = Utils::randomFloat(100, width - 100);
		float posY = 50;

		float speedX = Utils::randomFloat(0, 10);
		float speedY = Utils::randomFloat(100, 200);

		if (Utils::randomInt(0, 1) == 1) {
			speedX = -speedX;
		}

		float rotate = Utils::calculateAngleOfRotationForVelocity(sf::Vector2f(speedX, speedY));

		Life* life = new Life(&_heartTexture, sf::Vector2u(20, 16), sf::Vector2u(2, 1), sf::Vector2f(speedX, speedY), 10, rotate);
		life->setPosition(posX, posY);
		_gameRigidObjectsManager->addItem(life, "life");

		_heartDropFreqTime = Utils::randomFloat(level._heartDropFreqTimeRage.x, level._heartDropFreqTimeRage.y);
		_lastHeartDropTime = 0;
	}
}

void Game::generateClouds(float deltaTime)
{
	_lastGenCloudTime += deltaTime;
	if (_lastGenCloudTime >= _cloudGenFreqTime) {

		Level level = _levels.at(_currentLevel - 1);
		
		bool formLeft = (Utils::randomInt(0, 1) == 1);

		float posX = (formLeft) ? -40 : width + 40;
		float posY = Utils::randomFloat(80, 300);

		float speedX = Utils::randomFloat(30, 50);
		float speedY = Utils::randomFloat(10, 20);

		float shakeSpeed = Utils::randomFloat(0.5, 1.5f);
		float switchTime = Utils::randomFloat(7, 30);

		float currentImage = 0;
		if (Utils::randomInt(0, 100) < 10)
			currentImage = Utils::randomInt(1, 2);
		 

		speedX = (formLeft) ? speedX : -speedX;
		
		Cloud* cloud = new Cloud(&_cloudTexture, sf::Vector2u(32, 16), sf::Vector2u(3, 1), sf::Vector2f(speedX, speedY), shakeSpeed, switchTime, currentImage);
		cloud->setPosition(posX, posY);
		
		_gameRigidObjectsManager->addItem(cloud, "cloud");

		_cloudGenFreqTime = Utils::randomFloat(level._cloudGenFreqTimeRage.x, level._cloudGenFreqTimeRage.y);
		_lastGenCloudTime = 0;
	}
}

void Game::handleNextLevels(Game::Level level, float deltaTime)
{
	_levelTrackTime += deltaTime;
	if(level.levelDuration != 0 && _levelTrackTime >= level.levelDuration)
	{
		_currentLevel++;
		_levelTrackTime = 0;
		_lastBombDropTime = _levels.at(_currentLevel - 1)._bombDropFreqTimeRage.y + 1;
	}
}

void Game::_loop(Player& player)
{
    _deltaTime = _timer.restart().asSeconds();
    
	Level level = _levels.at(_currentLevel - 1);
	
	// waiting for user action
    sf::Event e;
    while (_window.pollEvent(e)) {
        if (e.type == sf::Event::EventType::Closed) {
            _gameState = EXITING;
        }
    }
    
    _window.clear();


	if (_lifes > 0) {
		updateRigidBodyGameObjects(player);
		player.update(_deltaTime);
	}
	
	dropApple(_deltaTime);
	dropHeartLifes(_deltaTime);
	dropNewBombs(_deltaTime);

	generateClouds(_deltaTime);


	drawGameObjects(player);
	player.draw(_window);

	renderGui(_deltaTime);

	if (!_lifes > 0) {
		_gameOverResetTime -= _deltaTime;
		gameOverScreen();

		if(_gameOverResetTime <= 0.0f)
		{
			initRound();
		}
	}
	
	handleNextLevels(level, _deltaTime);
    _window.display();
}



void Game::renderGui(float deltaTime)
{
	// set background for game
	GameObject guiBackground = *_gameStaticMenuObjects.findByObjectName("guiBackground")->gameObject;
	guiBackground.draw(_window);
	
	renderSocre(deltaTime);
	renderLevel(deltaTime);
	renderLifes(deltaTime);
	renderTimer(deltaTime);
}

void Game::renderSocre(float deltaTime)
{
	
	_text.setString("POINTS:"+std::to_string(_score));
	_text.setPosition(15, 10);
	_window.draw(_text);
}

void Game::renderLevel(float deltaTime)
{
	Level level= _levels.at(_currentLevel - 1);

	_text.setString("LEVEL:");
	_text.setPosition(15, 35);
	_window.draw(_text);
	
	_text.setString( level.levelSlug+ " "+level.levelDescription);
	_text.setFillColor(level.levelColor);
	_text.setPosition(104, 35);
	_window.draw(_text);
	_text.setFillColor(sf::Color::White);
}

void Game::renderLifes(float deltaTime)
{
	GameObject heartEmpty = *_gameStaticMenuObjects.findByObjectName("heartEmpty")->gameObject;
	GameObject heartFull = *_gameStaticMenuObjects.findByObjectName("heartFull")->gameObject;

	GameObject heart;
	
	heart = (_lifes >= 3) ? heartFull : heartEmpty;
	heart.setPosition(width/2 + 38  - 36 + 5, 9);
	heart.draw(_window);

	heart = (_lifes >= 2) ? heartFull : heartEmpty;
	heart.setPosition(width / 2 + 38 - 64 + 5, 9);
	heart.draw(_window);
	
	heart = (_lifes >= 1) ? heartFull : heartEmpty;
	heart.setPosition(width / 2 + 38 - 92 + 5, 9);
	heart.draw(_window);
}


void Game::renderTimer(float deltaTime)
{
	if(_lifes > 0) _playTime += deltaTime;

	_text.setString("TIME:" + std::to_string((int)_playTime));
	_text.setPosition(width - 150, 10);
	_window.draw(_text);
}


void Game::gameOverScreen()
{
	GameObject guiGameOverBackground = *_gameStaticMenuObjects.findByObjectName("gameOverBackground")->gameObject;
	guiGameOverBackground.draw(_window);

	_text.setFillColor(sf::Color(255, 11, 0));
	_text.setString("GAMEOVER");
	_text.setPosition(width / 2.0f - guiGameOverBackground.getRectangle().width / 2.0f + 54, height / 2.0f - guiGameOverBackground.getRectangle().height / 2.0f + 15 * 1);
	_window.draw(_text);
	_text.setFillColor(sf::Color::White);

	_text.setString("POINTS:" + std::to_string(_score));
	_text.setPosition(width / 2.0f - guiGameOverBackground.getRectangle().width / 2.0f + 15, height / 2.0f - guiGameOverBackground.getRectangle().height / 2.0f + (15 * 2) + 10 * 1);
	_window.draw(_text);


	_text.setString("NEW GAME IN:" + std::to_string((int)_gameOverResetTime + 1));
	_text.setPosition(width / 2.0f - guiGameOverBackground.getRectangle().width / 2.0f + 15, height / 2.0f - guiGameOverBackground.getRectangle().height / 2.0f + (15 * 3) + 10 * 2);
	_window.draw(_text);
}

void Game::appleCollected()
{
	_score += 100;
}


void Game::detectCollisions(Player* player, GameObjectManager<AbstractRigidbodyGameObject>::Node* node)
{
	sf::IntRect rect1(player->getBody().getPosition().x, player->getBody().getPosition().y, player->getBody().getSize().x, player->getBody().getSize().y);
	sf::IntRect rect2 (node->gameObject->getPosition().x, node->gameObject->getPosition().y, node->gameObject->getRectangle().width, node->gameObject->getRectangle().height);
	
	if (rect1.left <= rect2.left + rect2.width &&
		rect1.left + rect1.width >= rect2.left &&
		rect1.top <= rect2.top + rect2.height &&
		rect1.top + rect1.height >= rect2.top) {


		if (node->objectName == "bomb"){
			Bomb* bomb = ((Bomb*)node->gameObject);
			if (!bomb->hasColldedWithPlayer()) {
				bomb->setTexture(&_bombExplodeTexture);
				--_lifes;
			}
		}
		else if (node->objectName == "apple")
		{
			appleCollected();

		}else if(node -> objectName == "life")
		{
			if (_lifes < 3) _lifes++;

		}
		node->gameObject->setColldedWithPlayer(true);
		
		if (node->objectName != "bomb") _gameRigidObjectsManager->deleteItem(node);
	}
}


bool Game::_isRunning() {
    if (_gameState != EXITING) {
        return true;
    }
    
    return false;
}

void Game::disposeDynamicObjects()
{
	delete _gameRigidObjectsManager;
}


Game::~Game()
{
	disposeDynamicObjects();
}

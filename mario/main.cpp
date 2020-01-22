#include "Game.hpp"
#include "GameObjectManager.hpp"
#include "GameObject.hpp";

/** The main function of the program
* @param Number of console line arguments
* @param Console line arguments
*/
int main(int, char const**)
{	
    // settings for Game
    Game* game = new Game();

    game->width = 640;
    game->height = 480;
    game->title = "SFML - Bobo Mario";
  
    // run game
    game->run();

	//free all reserved memory
	delete game;
	
    return 0;
}

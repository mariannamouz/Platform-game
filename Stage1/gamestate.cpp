#include "gamestate.h"
#include "level.h"
#include "player.h"
#include "enemy.h"
#include <thread>
#include <chrono>

GameState::GameState()
{

}

GameState::~GameState()
{
	if (m_current_level)
		delete m_current_level;
	if (m_player)
		delete m_player;
}

GameState* GameState::getInstance()
{
	//if GameState doesn't exist,it creates one
	if (!m_unique_instance){
		m_unique_instance = new GameState();
	}
	//returns GameState
	return m_unique_instance;
}

void GameState::init()
{
	// we start at the start menu
	m_current_level = new Level("assets/startmenu.txt", "assets/background_6.png");
	m_current_level->init();
	currentLevel = 0;

	//player
	m_player = new Player("Player" , "assets/asterix.png");
	m_player->init();
	std::cout << "    player was created";

	//pre-load all assets
	graphics::preloadBitmaps(getAssetDir());  // getAssetDir = get assets directory
	
	//set text font
	//called before drawText
	//text is always designed last
	graphics::setFont(m_asset_path + "OpenSans-Regular.ttf");

}

void GameState::draw()
{	
	//if current level doesn't exist
	if (!m_current_level)
		return;

	//if current level exists , draw it
	m_current_level->draw();
}

void GameState::update(float dt)
{
	// Skip an update if a long delay is detected 
	// to avoid messing up the collision simulation
	
	// barrier for too slow changes
	if (dt > 500) // ms
		return;

	// Avoid too quick updates
	// barrier for too fast changes
	float sleep_time = std::max(17.0f - dt, 0.0f);
	if (sleep_time > 0.0f)
	{
		std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(sleep_time));
	}

	//if current level doesn't exist
	if (!m_current_level)
		return;

	//if current level exists , update it
	if (m_current_level)
		m_current_level->update(dt);

	m_debugging = graphics::getKeyState(graphics::SCANCODE_0);

}

// getters :
std::string GameState::getFullAssetPath(const std::string& asset)
{
	return m_asset_path + asset;
}

std::string GameState::getAssetDir()
{
	return m_asset_path;
}

//  static GameState* m_unique_instance; (gamestate.h) must be initialized
GameState* GameState::m_unique_instance = nullptr;

void GameState::loadNextLevel()
{
	// Check if the requested level is within the valid range
	std::cout << "  current level :";
	std::cout <<currentLevel;
	std::cout << "  is level loading :";
	std::cout <<m_loading_next_level;

	// check if the next level is already loading
	if (m_loading_next_level)
		return;

	if (currentLevel >= 0 && currentLevel <= 4 )	{

		// Load the corresponding level
		switch (currentLevel++)	{
			// if we are on the start menu , we want to load the 1st level
			case 1:
				createLevel("assets/level1.txt" , "assets/background_6.png");
				std::cout << "   level 1";
				break;

			// if the next level is the 2nd
			case 2:
				createLevel("assets/level2.txt", "assets/background_6.png");
				std::cout << "   level 2";
				break;

			case 3: // if the next level is the 3rd
				createLevel("assets/level3.txt", "assets/background_6.png");
				std::cout << "    level 3";
				break;

			case 4: // if we just finished the 3rd level , the currentlevel = 4 , we need to load the ending page
				createLevel("assets/endpage.txt", "assets/background_6.png");
				std::cout << "    end page";
				break;

			default:
				std::cout << "    default";
				break;
			
			// Set the flag to prevent multiple loading attempts
			m_loading_next_level = true;

			// increase the currentLevel variable 
			currentLevel++;

		}

	} else {	// if we reached the 3rd level , the game is over and we have won
		// Handle invalid level number
	}
}

// load different page when player losses game
// it goes from the page the player was when he lost -to the game lost page
void GameState::loadGameLost()
{
	createLevel("assets/gamelost.txt", "assets/background_6.png");

}

void GameState::createLevel(const std::string& texture , const std::string& background)
{
	Level* level = new Level(texture , background);

	// reset player's position so that he always starts at the center
	getPlayer()->resetPlayerPosition();
	level->init(); 

	m_current_level = level;
}



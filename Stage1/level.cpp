#include "level.h"
#include <sgg/graphics.h>
#include "util.h"
#include <string>
#include <thread>  // we include the <thread> header for sleep


std::chrono::steady_clock::time_point nextLevelDisplayTime; // used to draw "next level"

// contructor
Level::Level(const std::string& file , const std::string& background)
	: GameObject(file), filename(file), m_exit(nullptr)
{
	m_brush_background.outline_opacity = 0.0f;
	m_brush_background.texture = background;

	// next level brush
	m_brush_nextLevel.outline_opacity = 0.0f;
	SETCOLOR(m_brush_nextLevel.fill_color, 0.0f, 0.0f, 1.0f); //blue

	// health brush
	m_brush_health.outline_opacity = 0.0f;
	SETCOLOR(m_brush_health.fill_color, 1.0f, 0.5f,0.0f); // orange

	// game over brush
	m_brush_gameOver.outline_opacity = 0.0f;
	SETCOLOR(m_brush_gameOver.fill_color, 1.0f, 0.0f, 0.0f); //red

	// game won brush
	m_brush_game.outline_opacity = 0.0f;
	SETCOLOR(m_brush_game.fill_color, 0.0f, 0.0f, 0.0f); //black


	//start menu brush
	m_brush_startmenu.outline_opacity = 0.0f;
	m_brush_startmenu.texture = m_state->getFullAssetPath("papyrus.png");

}

// distractor
Level::~Level()
{
	for (auto b : m_blocks)
		delete b;
	for (auto e : m_enemies)
		delete e;
	for (auto g : m_gems)
		delete g;

	// Delete the Exit object if it exists
	if (m_exit)
		delete m_exit;
}

void Level::loadLevel(std::string& filename)
{
	// Open the file
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Error: Could not open file " << filename << std::endl;
		return;
	}

	// Store the level data in a vector of strings
	std::vector<std::string> levelData;
	std::string line;
	while (std::getline(file, line)) {
		levelData.push_back(line);
	}
	// Now, levelData contains each line of the file as a separate element

	file.close();

	// Now, you can process the level data and create game objects accordingly
	createGameObjects(levelData);
}

void Level::createGameObjects(std::vector<std::string>& levelData)
{
	const float startX = 0.0f;      // Set the starting X position

	// Loop through each row of the level data
	for (int i = 0; i < levelData.size(); ++i) {
		const std::string& row = levelData[i];
		for (int j = 0; j < row.size(); ++j) {
			char symbol = row[j];

			float x = startX + j * Block::getBlockSize();
			float y = i * Block::getBlockSize();

			// Create game objects based on the symbol
			switch (symbol) {
			case 'E':
				// Create an enemy
				createEnemy(x, y, Enemy::getEnemySize(), Enemy::getEnemySize(), "roman.png");
				break;

			case 'B':
				// Create a block with grass
				createBlock(x, y, Block::getBlockSize(), Block::getBlockSize(), "grass_block.png");
				break;

			case 'N':
				// Create a block
				createBlock(x, y, Block::getBlockSize(), Block::getBlockSize(), "block.png");
				break;

			case 'V':
				// Create an exit with gate.png
				m_exit = createExit(x, y, Exit::getExitSize(), Exit::getExitSize(), "gate.png");
				break;

			case 'W':
				// Create an exit with getafix.png
				m_exit = createExit(x, y, Exit::getExitSize(), Exit::getExitSize(), "getafix.png");
				break;

			case '1':
				// Create a blue potion
				createGem(x, y, Gem::getGemSize(), Gem::getGemSize(), "potion_1.png");
				break;

			case '2':
				// Create a red potion
				createGem(x, y, Gem::getGemSize(), Gem::getGemSize(), "potion_2.png");
				break;

			case '3':
				// Create a green potion
				createGem(x, y, Gem::getGemSize(), Gem::getGemSize(), "potion_3.png");
				break;

			case '4':
				// Create a yellow potion
				createGem(x, y, Gem::getGemSize(), Gem::getGemSize(), "potion_4.png");
				break;

			// END PAGE - GAME LOST
			case 'O':
				// draw game over text
				writeText(x, y, m_brush_gameOver , "Game Over!   You Lost!");
				break;

			// START MENU
			case 'M':
				showPapyrus(x,y, m_brush_startmenu);
				break;

			// END PAGE - GAME WON
			case 'T':
				// draw game won text
				writeText(x, y, m_brush_game, "Game Over!   You WON!");
				break;
			}
		}
	}
}

// writes text
void Level::writeText(float x, float y, graphics::Brush brush, std::string s)
{
	std::cout << "    text drawn";
	graphics::drawText(
		x,
		y,
		0.5f,
		s,
		brush
	);
}

// creates an enemy
void Level::showPapyrus(float x, float y, graphics::Brush brush)
{
	std::cout << "    papyrus drawn";
	std::cout << x;
	std::cout <<y;
	graphics::drawRect(
		x,
		y,
		1.8f,
		1.8f,
		brush
	);
}

// creates an enemy
void Level::createEnemy(float x, float y, float w, float h, const std::string& texture)
{
	Enemy* enemy = new Enemy(x, y, w, h, texture);
	m_enemies.push_back(enemy);
}

// creates a block
void Level::createBlock(float x, float y, float w, float h, const std::string& texture)
{
	Block* block = new Block(x, y, w, h, texture);
	m_blocks.push_back(block);
}

// creates a gem
void Level::createGem(float x, float y, float w, float h, const std::string& texture)
{
	Gem* gem = new Gem(x, y, w, h, texture);
	m_gems.push_back(gem);
}

// creates an exit , and stores it in m_exit (m_exit : level.h)
Exit* Level::createExit(float x, float y, float w, float h, const std::string& texture)
{
	Exit* exit = new Exit(x, y, w, h, texture);
	return exit;
}


void Level::update(float dt)
{
	// if player is active , update player
	//std::cout << "    update player";
	if (m_state->getPlayer()->isActive())
		m_state->getPlayer()->update(dt);

	// for each enemy: if enemy is active , update enemie
	for (auto e : m_enemies)
		if(e->isActive())
			e->update(dt);

	// for each gem: if gem is active , update gem
	for (auto g : m_gems)
		if (g->isActive())
			g->update(dt);

	// update exit
	if (m_exit)
		m_exit->update(dt);

	checkCollisions();
	checkHealth();

	GameObject::update(dt);

	// Check if it's time to reset the "Next Level" text display
	auto currentTime = std::chrono::steady_clock::now();
	auto displayDuration = std::chrono::seconds(2); // Same duration as in the draw function

	if (currentTime - nextLevelDisplayTime >= displayDuration)
	{
		// Reset the display time when the duration is over
		nextLevelDisplayTime = std::chrono::steady_clock::time_point();
	}
}

void Level::draw()
{
	float w = m_state->getCanvasWidth();
	float h = m_state->getCanvasHeight();

	//deixnei thn ygeia toy player
	std::string healthString = std::to_string(m_state->getPlayer()->getHealth());
	graphics::drawText(
		0.3f, 
		5.6f, 
		0.3f, 
		"health = " + healthString, 
		m_brush_health
	);
	
	//Moving Player (stationary Background)
		graphics::drawRect(
			w,
			h,
			2.0f * w,
			4.0f * h,
			m_brush_background
		);


	if (m_state->getPlayer()->isActive())
		m_state->getPlayer()->draw();

	// draw enemies
	// for each enemy: if enemy is active , draw enemie
	for (auto e : m_enemies)
		if (e->isActive())
			e->draw();

	// for each gem: if gem is active , draw gem
	for (auto g : m_gems)
		if (g->isActive())
			g->draw();

	// draw blocks 
	for (auto& b : m_blocks)
		b->draw();

	// draw exit
	if (m_exit)
		m_exit->draw();

	// Draw "Next Level" text if within the display duration
	auto currentTime = std::chrono::steady_clock::now();
	auto displayDuration = std::chrono::seconds(2); // Adjust the duration as needed

	if (currentTime - nextLevelDisplayTime < displayDuration)
	{
		std::string nextLevel = "Next Level";
		graphics::drawText(
			3.5f,
			2.6f,
			1.0f,
			nextLevel,
			m_brush_nextLevel
		);
	}

}

void Level::init()
{
	loadLevel(filename);

	for (auto e : m_enemies)
		e->init();
	for (auto g : m_gems)
		g->init();

	if (m_exit)
		m_exit->init();

}

// loads game lost page , if the player has lost
void Level::checkHealth() {
	if (m_state->getPlayer()->getHealth() == 0) {
		m_state->loadGameLost();
	}
}

//--------------------------- collisions --------------------------------------------------------------------

void Level::checkCollisions()
{
	//collision with upper surface of the block
	for (auto& block : m_blocks)
	{
		float offset = 0.0f; //  offset

		if (offset = m_state->getPlayer()->intersectDown(*block))
		{
			m_state->getPlayer()->m_pos_y += offset;

			// add sound event
			if (m_state->getPlayer()->m_vy > 1.0f)
				graphics::playSound(m_state->getFullAssetPath("snow-step-1-81064"), 1.5f);

			m_state->getPlayer()->m_vy = 0.0f;
			break;
		}
	}

	// collisions on left and right
	for (auto& block : m_blocks)
	{
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersectSideways(*block))
		{
			// add sound event
			if (m_state->getPlayer()->m_vx > 1.0f || m_state->getPlayer()->m_vx < -1.0f)
				graphics::playSound(m_state->getFullAssetPath("snow-step-1-81064"), 1.5f);
			m_state->getPlayer()->m_pos_x += offset;

			m_state->getPlayer()->m_vx = 0.0f;
			break;
		}
	}

	//collisions with the lower part of the block
	for (auto& block : m_blocks)
	{
		float offset = 0.0f; //  offset

		if (offset = m_state->getPlayer()->intersectUp(*block))
		{
			m_state->getPlayer()->m_pos_y += offset;

			// add sound event
			if (m_state->getPlayer()->m_vy < -1.0f)
				graphics::playSound(m_state->getFullAssetPath("snow-step-1-81064"), 1.5f);

			m_state->getPlayer()->m_vy = 0.0f;
			break;
		}
	}

	//---------------------------collision with the enemy--------------------------------------------------------------------
		//collisions with the lower part of the enemy
	float offset = 0.0f; //  offset

	for (auto enemy : m_enemies)
	{
		float offset = 0.0f; //  offset

		if (offset = m_state->getPlayer()->intersectUp(*enemy))
		{
			//when there is a collision between the player and the enemy, players health is decreased
			m_state->getPlayer()->decreaseHealth(1);

			m_state->getPlayer()->m_pos_y += offset;


			m_state->getPlayer()->m_vy = 0.0f;
			// add sound event

			graphics::playSound(m_state->getFullAssetPath("baseball_hit.wav"), 0.5f);


			break;
		}
	}

	// collisions on left and right of the enemy
	for (auto& enemy : m_enemies)
	{
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersectSideways(*enemy))
		{
			enemy->changeDirection();
			//when there is a collision between the player and the enemy, players health is decreased
			m_state->getPlayer()->decreaseHealth(1);

			m_state->getPlayer()->m_pos_x += offset;

			m_state->getPlayer()->m_vx = 0.0f;
			// add sound event		
			graphics::playSound(m_state->getFullAssetPath("baseball_hit.wav"), 0.5f);
			break;
		}
	}

	//collision with upper surface of the enemy
	for (auto& enemy : m_enemies)
	{
		float offset = 0.0f; //  offset

		if (offset = m_state->getPlayer()->intersectDown(*enemy))
		{
			//when there is a collision between the player and the enemy, players health is decreased
			m_state->getPlayer()->decreaseHealth(1);

			m_state->getPlayer()->m_pos_y += offset;

			// add sound event

			graphics::playSound(m_state->getFullAssetPath("baseball_hit.wav"), 0.5f);


			m_state->getPlayer()->m_vy = 0.0f;
			break;
		}
	}

	//--------------------------- collision with the gem --------------------------------------------------------------------
	//upper part of gem
	for (auto& gem : m_gems)
	{
		float offset = 0.0f; //  offset

		if (offset = m_state->getPlayer()->intersectDown(*gem))
		{
			m_state->getPlayer()->m_pos_y += offset;

			gem->handlePlayerCollision();
			m_gems.erase(std::remove(m_gems.begin(), m_gems.end(), gem), m_gems.end());
			gem->visabilityOfRemainingGems();// the gems remaining after the collision stay visible


			// add sound event

			graphics::playSound(m_state->getFullAssetPath("mixkit-fairy-glitter-867.wav"), 0.5f);


			m_state->getPlayer()->m_vy = 0.0f;
			break;
		}
	}

	// collisions on left and right of the gem
	for (auto& gem : m_gems)
	{
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersectSideways(*gem))
		{
			m_state->getPlayer()->m_pos_x += offset;
			m_state->getPlayer()->m_vx = 0.0f;

			gem->handlePlayerCollision();
			m_gems.erase(std::remove(m_gems.begin(), m_gems.end(), gem), m_gems.end());
			gem->visabilityOfRemainingGems();// the gems remaining after the collision stay visible

			// add sound event

			graphics::playSound(m_state->getFullAssetPath("mixkit-fairy-glitter-867.wav"), 0.5f);


			break;
		}
	}

	//collisions with the lower part of the gem
	for (auto& gem : m_gems)
	{
		float offset = 0.0f; //  offset

		if (offset = m_state->getPlayer()->intersectUp(*gem))
		{
			m_state->getPlayer()->m_pos_y += offset;
			m_state->getPlayer()->m_vy = 0.0f;

			gem->handlePlayerCollision();

			m_gems.erase(std::remove(m_gems.begin(), m_gems.end(), gem), m_gems.end());
			gem->visabilityOfRemainingGems();// the gems remaining after the collision stay visible

			// add sound event

			graphics::playSound(m_state->getFullAssetPath("mixkit-fairy-glitter-867.wav"), 0.5f);

			break;
		}
	}

	//--------------------------- collision with the exit door --------------------------------------------------------------------
	// Check if player intersects with the exit
	if (m_exit && m_state->getPlayer()->intersect(*m_exit) && m_gems.empty())
	{
		// if the next level is not loading
		if (!m_state->isLoadingNextLevel())
		{
			// now is the time to draw "next level" text
			if (m_state->getCurrentLevel() == 1 || m_state->getCurrentLevel() == 2) {
				nextLevelDisplayTime = std::chrono::steady_clock::now();
			}

			// sleep for 1 second (1000 milliseconds)
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));


			// and move to the next level
			m_state->loadNextLevel();

		}
	}
	else
	{
		// Reset the flag when player is not in contact with the exit
		m_state->resetLoadingNextLevelFlag();
	}
}


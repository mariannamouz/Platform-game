#include "startpage.h"
#include <sgg/graphics.h>
#include "util.h"
#include "block.h"
#include "player.h"
#include <string>

// contructor
StartPage::StartPage(const std::string& file)
	: GameObject(file), filename(file)
{
	m_brush_background.outline_opacity = 0.0f;
	m_brush_background.texture = m_state->getFullAssetPath("background.png");

	m_brush_startButton.outline_opacity = 0.0f;
	m_brush_startButton.texture = m_state->getFullAssetPath("startButton.png");
}

// distractor
StartPage::~StartPage()
{
	// reset png (if it is changed when the button gets pressed)
	m_brush_startButton.texture = m_state->getFullAssetPath("startButton.png");
}

void StartPage::loadLevel(std::string& filename)
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

void StartPage::createGameObjects(std::vector<std::string>& levelData)
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
			case 'T': 
				// show game tittle
				//createEnemy(x, y, Enemy::getEnemySize(), Enemy::getEnemySize(), "roman.png");
				break;

			case 'C':
				// choose player text
				//createBlock(x, y, Block::getBlockSize(), Block::getBlockSize(), "block8.png");
				//m_block_names.push_back("block8.png");
				break;

			case 'P':
				// choose player
				//createBlock(x, y, Block::getBlockSize(), Block::getBlockSize(), "block8.png");
				//m_block_names.push_back("block8.png");
				break;
			case 'S':
				// start game
				// you can start the game after you choose a player
				createStartButton(x,y, getStartButtonSize(), getStartButtonSize());
				std::cout << "    start button was created";
				break;
			}
		}
	}
}

// creates startButton
void StartPage::createStartButton(float x, float y, float w, float h)
{
	//create button
	graphics::drawRect(
		x,
		y,
		w,
		h,
		m_brush_startButton
	);
}

void StartPage::update(float dt)
{
	// if player is active , update player
	//std::cout << "    update player";
	if (m_state->getPlayer()->isActive())
		m_state->getPlayer()->update(dt);

	//load level 1 if startButton is pressed (for now if space is pressed)
	if (graphics::getKeyState(graphics::SCANCODE_SPACE))
		m_state->loadNextLevel();
	std::cout << "    space was pressed";

	// καλώ καλού-κακού και την update του GameObject
	GameObject::update(dt);

}

void StartPage::draw()
{
	float w = m_state->getCanvasWidth();
	float h = m_state->getCanvasHeight();

	graphics::drawRect(
		w,
		h,
		2.0f * w,
		4.0f * h,
		m_brush_background
	);
}

void StartPage::init()
{
	loadLevel(filename);

}
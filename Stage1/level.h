#pragma once
#include <vector>
#include <list>
#include <string>
#include <sgg/graphics.h>
#include "gameobject.h"
#include "player.h"
#include "enemy.h"
#include "block.h"
#include "exit.h"
#include "gem.h"
#include <fstream>
#include <iostream>

class Level : public GameObject
{

	graphics::Brush m_brush_background;
	graphics::Brush m_brush_nextLevel;
	graphics::Brush m_brush_gameOver;
	graphics::Brush m_brush_game;
	graphics::Brush m_brush_health;

	graphics::Brush m_brush_startmenu;


	// game won paragraph 
	std::string game_won_paragraph =
		"Congratulations  ,you won !";

	// BLOCKS
	std::vector<Block*> m_blocks; 
 
	// ENEMIES
	std::vector<Enemy*> m_enemies;  

	// GEMS
	std::vector<Gem*> m_gems; 

	// it is not a box so we have to declare them
	float m_center_x = 5.0f;
	float m_center_y = 5.0f;

	// detect collisions
	void checkCollisions();

	//check if player's health is 0=player has lost
	void checkHealth();

public:
	void update(float dt) override;
	void draw() override; 
	void init() override;

	void loadLevel(std::string& filename); // creates vector that contains each line of the file as a separate element
	
	void createEnemy(float x, float y, float w, float h, const std::string& texture); // creates an enemy
	void createBlock(float x, float y, float w, float h, const std::string& texture); // creates a block
	void createGem(float x, float y, float w, float h, const std::string& texture); // creates a gem
	Exit* createExit(float x, float y, float w, float h, const std::string& texture); // creates exit

	void writeText(float x,float y, graphics::Brush brush , std::string); // writes text
	void showPapyrus(float x, float y, graphics::Brush brush);

	//contructor
	Level(const std::string& filename , const std::string& background); // parse file with 'level map' and background as argument
		
	//distractor
	~Level() override; 

private:
	void createGameObjects(std::vector<std::string>& levelData);

private:
	std::string filename; // declare filename as a member variable
	Exit* m_exit = 0; // level exit

};

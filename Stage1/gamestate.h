#pragma once
#include <string>
#include <sgg/graphics.h>


class GameState {
private:
	static GameState* m_unique_instance;
	const std::string m_asset_path = "assets\\"; // path to our assets
	
	// canvas size - used in graphics::setCanvasSize
	const float m_canvas_width = 11.0f;
	const float m_canvas_height = 6.0f;

	class Level* m_current_level = 0; // level
	class Player* m_player = 0; // player 

	bool levelLost = false;

	GameState(); //private constructor

	int currentLevel; // Current level number ( 1, 2, 3)

	bool m_loading_next_level = false; // true : when the loadNextLevel() has been called

public:
	bool m_debugging = false;

public:
	~GameState();
	
	// if a  GameState exists it returns it , otherwise it creates one and returns it
	static GameState* getInstance();

	void init();
	void draw();
	void update(float dt);

	//  getters for private variables
	// get : const std::string m_asset_path = "assets\\";
	std::string getFullAssetPath(const std::string& asset);
	std::string getAssetDir();

	float getCanvasWidth() {
		return m_canvas_width;
	}

	float getCanvasHeight() {
		return m_canvas_height;
	}

	class Player* getPlayer() {
		return m_player;
	}

	int getCurrentLevel() {
		return currentLevel;
	}

	bool getLevelLost() {
		return levelLost;
	}

	void setLevelLost(bool x) {
		levelLost = x;
	}

	// Function to load the next level
	void loadNextLevel();

	// load different page when player losses game
	// it goes from the page the player was when he lost -to the game lost page
	void loadGameLost();

	void createLevel(const std::string& texture , const std::string& background);

	// getter for m_loading_next_level
	bool isLoadingNextLevel() const { 
		return m_loading_next_level; 
	}

	// reset the m_loading_next_level to false
	void resetLoadingNextLevelFlag() { 
		m_loading_next_level = false; 
	}

};

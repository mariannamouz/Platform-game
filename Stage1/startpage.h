#pragma once
#include <vector>
#include <list>
#include <string>
#include <sgg/graphics.h>
#include "gameobject.h"
#include <fstream>
#include <iostream>

class StartPage : public GameObject
{

	graphics::Brush m_brush_background;
	graphics::Brush m_brush_startButton;

	//startButton

	// δεν είναι Βox oπότε πρέπει να τα ορίσουμε
	float m_center_x = 5.0f;
	float m_center_y = 5.0f;


public:
	void update(float dt) override; //ενημερώνει το state level και καλεί update δυναμικών αντικειμένων
	void draw() override; //σχεδιάζει τα πάντα, ότι περιέχεται 
	void init() override; //φορτώνει το περιβάλλον της πίστας

	void loadLevel(std::string& filename); // creates vector that contains each line of the file as a separate element

	//contructor
	StartPage(const std::string& filename); // parse file with 'level map' as argument

	//distractor
	~StartPage() override;

	void createStartButton(float x, float y, float w, float h); // creates startButton
	
	float getStartButtonSize() {
		return startButton_size;
	}

private:
	void createGameObjects(std::vector<std::string>& levelData);

private:
	std::string filename; // declare filename as a member variable
	float startButton_size = 2.0f;
};
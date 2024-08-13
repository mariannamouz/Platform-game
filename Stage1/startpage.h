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

	// ��� ����� �ox o���� ������ �� �� ��������
	float m_center_x = 5.0f;
	float m_center_y = 5.0f;


public:
	void update(float dt) override; //���������� �� state level ��� ����� update ��������� ������������
	void draw() override; //��������� �� �����, ��� ���������� 
	void init() override; //�������� �� ���������� ��� ������

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
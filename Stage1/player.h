#pragma once
#include "gameobject.h"
#include <sgg/graphics.h>
#include "box.h"

// player is GameObject & Box
class Player : public Box, public GameObject
{
	//player brush
	graphics::Brush m_brush_player;
	
	//player size
	float player_size = 0.8f;

	// what will happen to the vertical (y) axis when he jumps
	// to model a jump we must have instantaneous acceleration
	const float m_accel_vertical = 250.0f;
	// how fast the player will be brought back down when jumping
	const float m_gravity = 10.0f;

	// what happens to horizontal axis (x) when player jumps
	const float m_accel_horizontal = 20.0f;

	const float m_max_velocity = 2.8f;
	
	int health = 100;

public:
	// player velocity
	// initially 0 , until player moves
	float m_vx = 0.0f;
	float m_vy = 0.0f;


public:
	void update(float dt) override;
	void draw() override;
	void init() override;
	int getHealth(); //returns players health
	void decreaseHealth(int x); //effect of a collision to health

	//constructor
	Player(std::string name, const std::string& texture);

	void resetPlayerPosition();

protected:
	void debugDraw();

	// controls how player moves
	void movePlayer(float dt);

};
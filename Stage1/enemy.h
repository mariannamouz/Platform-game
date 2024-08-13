#pragma once
#include <vector>
#include <string>
#include <sgg/graphics.h>
#include "box.h"
#include "gameobject.h"

class Enemy : public Box, public GameObject {

	//enemie brush
	graphics::Brush m_brush_enemy;
	static float enemy_size;

public:
	float enemy_velocity = 2.0f; // Speed of enemy movement

public:
	Enemy(float x, float y, float w, float h, const std::string& texture);

	void update(float dt) override;
	void draw() override;
	void init() override;

	// getter for enemy_size
	static float getEnemySize() {
		return enemy_size;
	}

	// getter for enemy velocity
	float getVelocity() {
		return enemy_velocity;
	}

	void changeDirection(); //useful for collisions

protected:
	void debugDraw();

};



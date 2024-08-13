#include "enemy.h"
#include "util.h"

//enemy's size 
float Enemy::enemy_size = 0.6f;

Enemy::Enemy(float x, float y, float w, float h, const std::string& texture) : Box(x, y, w, h), GameObject("Enemy") {
	m_brush_enemy.texture = m_state->getFullAssetPath(texture);
	m_brush_enemy.fill_opacity = 1.0f;
	m_brush_enemy.outline_opacity = 0.0f;
}

void Enemy::update(float dt) {
	// Move from left to right
	m_pos_x += enemy_velocity * dt / 1000.0f;

	// Check if the enemy has reached the left or right border
	if (m_pos_x < 0.0f) {
		// If it reached the left border, set position to 0
		m_pos_x = 0.0f;
		// Change direction to move to the right
		enemy_velocity = fabs(enemy_velocity);
	}
	else if (m_pos_x + m_width > GameState::getInstance()->getCanvasWidth()) {
		// If it reached the right border, set position to the rightmost position
		m_pos_x = GameState::getInstance()->getCanvasWidth() - m_width;
		// Change direction to move to the left
		enemy_velocity = -fabs(enemy_velocity);

		// Change the direction the enemy is facing 
		graphics::setScale(-1.0f, 1.0f);
		graphics::resetPose();
	}

	GameObject::update(dt);
}

void Enemy::draw() {

	float x = m_pos_x;
	float y = m_pos_y;

	graphics::drawRect(
		x,
		y,
		m_width,
		m_height,
		m_brush_enemy
	);

	if (GameObject::m_state->m_debugging) {
		debugDraw();
	}

}

void Enemy::init() {
	
}

void Enemy::debugDraw() {
	// Debug drawing, if needed
	graphics::Brush debug_brush;
	SETCOLOR(debug_brush.fill_color, 1, 0.3f, 0);
	SETCOLOR(debug_brush.outline_color, 1, 0.1f, 0);
	debug_brush.fill_opacity = 0.1f;
	debug_brush.outline_opacity = 1.0f;
	graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, debug_brush);
}

void Enemy::changeDirection() {
	enemy_velocity = -fabs(enemy_velocity);
}



#include "player.h"
#include "enemy.h"
#include "util.h"
#include <cmath>
#include <iostream>


Player:: Player(std::string name, const std::string& texture) : GameObject(name) {
	m_brush_player.fill_opacity = 1.0f;
	m_brush_player.outline_opacity = 0.0f;
	m_brush_player.texture = texture;
}

void Player::update(float dt)
{
	float delta_time = dt / 1000.0f; // in sec (msec-sec because of /1000.0f)
	
	movePlayer(dt);

	GameObject::update(dt);
}

// controls how player moves
void Player::movePlayer(float dt)
{
	float delta_time = dt / 1000.0f;

	float move = 0.0f;

	if (graphics::getKeyState(graphics::SCANCODE_A)) // left
		move -= 1.0f;

	if (graphics::getKeyState(graphics::SCANCODE_D)) // right
		move += 1.0f;

	// Χ
		// horizontal - speed (right - left)
		// delimit the horizon - speed
		m_vx = std::min<float>(m_max_velocity, m_vx + delta_time * move * m_accel_horizontal); // don't exceed the maximum speed
		m_vx = std::max<float>(-m_max_velocity, m_vx); // be greater than the minimum speed

		// "frenaroume" ton player otan kineitai
		m_vx -= 0.2f * m_vx / (0.1f + fabs(m_vx));

		// we don't want to slow down all the time, we set a limit when our speed reaches a low point
		if (fabs(m_vx) < 0.01f)
			m_vx = 0.0f;

		// adjust horizontal position
		// horizontal position = speed * time
		m_pos_x += m_vx * delta_time; 


	// Υ
		// we don't want the player to be able to jump while in the air
		if (m_vy == 0.0f )
			m_vy -= (graphics::getKeyState(graphics::SCANCODE_W) ? m_accel_vertical : 0.0f) * 0.02f;// not delta_time!! Burst 

		// vertical - speed (up - down)
		m_vy += delta_time * m_gravity;

		// adjust vertical position
		// vertical position = speed * time
		m_pos_y += m_vy * delta_time;

}

void Player::draw()
{
	// Moving Player (stationary background)
	graphics::drawRect(
		m_pos_x,
		m_pos_y,
		player_size,
		player_size,
		m_brush_player);

	//std::cout << "    player drawn";

	if (m_state->m_debugging)
		debugDraw();
}

void Player::init()
{
	// setting player's starting position
	m_pos_x = 5.0f;
	m_pos_y = 5.0f;
	m_width /= 2.0f; // shrink the player box (uses collision management)
	//m_height = 0.8f;

	// Adjust width for finer collision detection
	m_width = 0.5f;

}

void Player::resetPlayerPosition() {
	m_pos_x = 5.0f;
	m_pos_y = 5.0f;
}

// when 0 is pressed i am in debug mode
void Player::debugDraw()
{
	graphics::Brush debug_brush;
	SETCOLOR(debug_brush.fill_color, 1, 0.3f, 0);
	SETCOLOR(debug_brush.outline_color, 1, 0.1f, 0);
	debug_brush.fill_opacity = 0.1f;
	debug_brush.outline_opacity = 1.0f;
	graphics::drawRect(
		m_pos_x,
		m_pos_y,
		player_size,
		player_size,
		debug_brush
	);

	char s[20];
	sprintf_s(s, "(%5.2f, %5.2f)", m_pos_x, m_pos_y);
	SETCOLOR(debug_brush.fill_color, 1, 0, 0);
	debug_brush.fill_opacity = 1.0f;
	graphics::drawText(
		m_pos_x,
		m_pos_y,
		0.15f, 
		s, 
		debug_brush
	);
}

// getter for player's health
int Player::getHealth() {
	return health;
}

// decrease player's health 
void Player::decreaseHealth(int x) {
	health -= x;
}
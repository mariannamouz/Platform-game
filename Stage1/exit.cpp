#include "exit.h"
#include "util.h"
#include <sgg/graphics.h>

float Exit::m_exit_size = 0.5f;

Exit::Exit(float x, float y, float w, float h, const std::string& texture)
	: Box(x, y, w, h), GameObject("Exit")
{
	// Set up any additional initialization logic for Block
	m_exit_brush.texture = m_state->getFullAssetPath(texture);

	// m_exit_brush_debug : brush for debug mode
	m_exit_brush.outline_opacity = 0.0f; 
	m_exit_brush_debug.fill_opacity = 0.1f; 
	SETCOLOR(m_exit_brush_debug.fill_color, 0.1f, 1.0f, 0.1f);
	SETCOLOR(m_exit_brush_debug.outline_color, 0.3f, 1.0f, 0.2f); 

}

void Exit::init()
{
	m_pos_y = m_pos_y - 0.20f;

}

void Exit::update(float dt)
{
	// Add any update logic for the Block
}

void Exit::draw()
{
	// position in which my exit will be drawn 

	float x = m_pos_x;
	float y = m_pos_y;

	graphics::drawRect(
		x,
		y,
		1.8f * m_width, // 1.8 * , ωστε να ειναι πο μεγαλα απο το block τα png , να φαινονται κολλητα μεταξυ τους (θελει δοκιμες για να βρουμε το 1.8)
		1.8f * m_height,
		m_exit_brush
	);

	// when in debug mode (0)
	if (m_state->m_debugging)
		graphics::drawRect(
			x,
			y,
			m_exit_size,
			m_exit_size,
			m_exit_brush_debug
		);
}

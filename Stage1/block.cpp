#include "block.h"
#include "util.h"
#include <sgg/graphics.h>

float Block::m_block_size = 0.5f;

Block::Block(float x, float y, float w, float h, const std::string& texture)
    : Box(x, y, w, h), GameObject("Block")
{
    // set up any additional initialization logic for Block
	m_block_brush.texture = m_state->getFullAssetPath(texture);

	// m_block_brush_debug : debug mode brush
	m_block_brush.outline_opacity = 0.0f; // without border

	m_block_brush_debug.fill_opacity = 0.1f; // with a little border
	SETCOLOR(m_block_brush_debug.fill_color, 0.1f, 1.0f, 0.1f);
	SETCOLOR(m_block_brush_debug.outline_color, 0.3f, 1.0f, 0.2f); // without border 

}

void Block::init()
{

}

void Block::update(float dt)
{
    
}

void Block::draw()
{
	float x = m_pos_x;
	float y = m_pos_y;

	graphics::drawRect(
		x,
		y,
		1.8f * m_width, // 1.8 * , so that png is bigger than block , to appear close to each other
		1.8f * m_height,
		m_block_brush
	);

	// when in debug mode (0)
	if (m_state->m_debugging)
		graphics::drawRect(
			x,
			y,
			m_block_size,
			m_block_size,
			m_block_brush_debug
		);
}
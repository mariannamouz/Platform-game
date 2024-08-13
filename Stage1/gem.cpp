#include "gem.h"
#include "util.h"
#include <sgg/graphics.h>

float Gem::m_gem_size = 0.5f;

Gem::Gem(float x, float y, float w, float h, const std::string& texture)
    : Box(x, y, w, h), GameObject("Gem"), m_drawGem(true)
{
    // Set up any additional initialization logic for Gem
    m_gem_brush.texture = m_state->getFullAssetPath(texture);


    m_gem_brush.outline_opacity = 0.0f;
    m_gem_brush_debug.fill_opacity = 0.1f;
    SETCOLOR(m_gem_brush_debug.fill_color, 0.1f, 1.0f, 0.1f);
    SETCOLOR(m_gem_brush_debug.outline_color, 0.3f, 1.0f, 0.2f);

}

void Gem::handlePlayerCollision()
{
    // Handle collision with the player
    // Set m_drawGem to false to make the gem disappear
    m_drawGem = false;
}

void Gem::visabilityOfRemainingGems()
{
    // Handle collision with the player
    // Set m_drawGem to false to make the gem disappear
    m_drawGem = true;
}

void Gem::init()
{

}


void Gem::update(float dt)
{

}

void Gem::draw()
{
    if (m_drawGem)
    {
        float x = m_pos_x;
        float y = m_pos_y;

        graphics::drawRect(
            x,
            y,
            1.8f * m_width,
            1.8f * m_height,
            m_gem_brush
        );

        // Debug mode
        if (m_state->m_debugging)
        {
            graphics::drawRect(
                x,
                y,
                m_gem_size,
                m_gem_size,
                m_gem_brush_debug
            );
        }
    }
}


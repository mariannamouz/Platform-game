#pragma once
#include <string>
#include <sgg/graphics.h>
#include "box.h"
#include "gameobject.h"

class Block : public Box, public GameObject
{
    graphics::Brush m_block_brush; //brush to draw block
    graphics::Brush m_block_brush_debug; //brush to draw block on debugging mode

    static float m_block_size;

    // the block size is set in the level.h
    //const float blockWidth = 1.0f;  // Set the width of your blocks
    //const float blockHeight = 1.0f; // Set the height of your blocks

public:
    Block(float x, float y, float w, float h, const std::string& texture);
    void draw();
    void init() override;
    void update(float dt) override;

    // Getter for block_size
    static float getBlockSize() {
        return m_block_size;
    }
};

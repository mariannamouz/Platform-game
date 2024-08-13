#pragma once
#include <string>
#include <sgg/graphics.h>
#include "box.h"
#include "gameobject.h"

class Exit : public Box, public GameObject
{
    graphics::Brush m_exit_brush; //brush to draw exit
    graphics::Brush m_exit_brush_debug;

    static float m_exit_size;

public:
    Exit(float x, float y, float w, float h, const std::string& texture);
    void draw();
    void init() override;
    void update(float dt) override;

    // Getter for block_size
    static float getExitSize() {
        return m_exit_size;
    }
};
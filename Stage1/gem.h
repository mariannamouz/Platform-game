#pragma once
#include <string>
#include <sgg/graphics.h>
#include "box.h"
#include "gameobject.h"

class Gem : public Box, public GameObject
{
    graphics::Brush m_gem_brush; //brush to draw gem
    graphics::Brush m_gem_brush_debug;

    static float m_gem_size;



    bool m_drawGem;// flag to determine whether to draw the gem

public:
    Gem(float x, float y, float w, float h, const std::string& texture);
    void draw();
    void init() override;
    void update(float dt) override;
    void handlePlayerCollision();
    void visabilityOfRemainingGems();

    // Getter for gem_size
    static float getGemSize() {
        return m_gem_size;
    }

};
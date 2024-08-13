#include <sgg/graphics.h> 
#include "util.h"
#include <string>
#include <stdio.h>
#include "gamestate.h"

void draw()
{
    GameState::getInstance()->draw();

}

void update(float dt)
{
    GameState::getInstance()->update(dt);
}

void init()
{  
    GameState::getInstance()->init();
}

int main(int argc, char** argv)
{
    //creates 1500 x 800 window named ASTERIX - Potion Hunt
    graphics::createWindow(1500, 800, "ASTERIX - Potion Hunt");

    init();

    // every time the library wants to draw or update , it will call the functions draw or update accordingly
    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    // dimensions of the canvas we are drawing
    graphics::setCanvasSize(GameState::getInstance()->getCanvasWidth(), 
                            GameState::getInstance()->getCanvasHeight());

    // how the window changes scale
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    //so that the window doesn't clode immediately
    graphics::startMessageLoop();
    return 0;
}




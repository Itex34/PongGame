#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"
#include "Game.hpp"
#include "Paddle.hpp"
#include <iostream>
Game game;
int main(int argc, char* argv[]) {

    const float targetFPS = 60.0f;
    const float maxFrameTime = 1.0f / targetFPS;
    Uint32 prevTicks = SDL_GetTicks();
    const float dt = 1000.0f / targetFPS;
    int windowWidth = 1300;
    int windowHeight = 700;

    game.init("GameWindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, false);

    Paddle paddle;

    if (!paddle.loadTexture(game.getRenderer(), "paddle.png")) {
        std::cerr << "Failed to load paddle texture" << std::endl;
        return -1;
    }

    while (game.running() == true) {
        Uint32 currentTicks = SDL_GetTicks();
        float deltaTime = (currentTicks - prevTicks) / 1000.0f;
        prevTicks = currentTicks;
        
        game.handleEvents();
        game.update();

        paddle.update();

        SDL_RenderPresent(game.getRenderer());

        game.render(windowHeight, windowWidth);
        paddle.render(game.getRenderer(), 20, windowHeight / 2);

        Uint32 frameTicks = SDL_GetTicks() - currentTicks;
        if (frameTicks < maxFrameTime * 1000.0f) {
            SDL_Delay((Uint32)((maxFrameTime * 1000.0f) - frameTicks));
        }
    }
    game.clean();
    return 0;
}


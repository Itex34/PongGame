#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"
#include "Game.hpp"
#include "Paddle.hpp"
#include "NPCPaddle.hpp"
#include "Ball.hpp"
#include <iostream>
#include <random>
Game game;

Paddle paddle;
NPCPaddle npcPaddle;
Ball ball;

int main(int argc, char* argv[]) {

    const float targetFPS = 60.0f;
    const float maxFrameTime = 1.0f / targetFPS;
    Uint32 prevTicks = SDL_GetTicks();
    const float dt = 1000.0f / targetFPS;
    int windowWidth = 1300;
    int windowHeight = 700;

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> ballY(50, 600);

    game.init("GameWindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, false);



    if (!paddle.loadTexture(game.getRenderer(), "paddle.png")) {
        std::cerr << "Failed to load paddle texture" << std::endl;
        return -1;
    }
    if (!npcPaddle.loadTexture(game.getRenderer(), "paddle.png")) {
        std::cerr << "Failed to load paddle texture" << std::endl;
        return -1;
    }
    if (!ball.loadTexture(game.getRenderer(), "ball.png")) {
        std::cerr << "Failed to load ball texture" << std::endl;
        return -1;
    }

    while (game.running() == true) {
        Uint32 currentTicks = SDL_GetTicks();
        float deltaTime = (currentTicks - prevTicks) / 1000.0f;
        prevTicks = currentTicks;
        
        game.handleEvents();
        game.update();

        paddle.update();
        npcPaddle.update();
        ball.update(game.getRenderer(), windowWidth, windowHeight, ballY(gen));

        game.render(windowHeight, windowWidth);

        paddle.render(game.getRenderer(), windowWidth, windowHeight / 2);
        npcPaddle.render(game.getRenderer(), windowWidth, windowHeight / 2);
        ball.render(game.getRenderer(), windowWidth, windowHeight / 2);

        SDL_RenderPresent(game.getRenderer());

        Uint32 frameTicks = SDL_GetTicks() - currentTicks;
        if (frameTicks < maxFrameTime * 1000.0f) {
            SDL_Delay((Uint32)((maxFrameTime * 1000.0f) - frameTicks));
        }
    }
    game.clean();
    return 0;
}


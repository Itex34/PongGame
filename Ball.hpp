#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Paddle.hpp"
#include "NPCPaddle.hpp"
#include <string>
#include <iostream>
#include <random>

extern Paddle paddle;
extern NPCPaddle npcPaddle;


class Ball {
public:
    Ball();
    ~Ball();

    void update(SDL_Renderer* renderer, int windowWidth, int windowHeight, int Y);
    void render(SDL_Renderer* renderer, int windowWidth, int windowHeight);
    bool checkCollision(const SDL_Rect& paddleRect);
    bool checkNPCCollision(SDL_Renderer* renderer, const SDL_Rect& paddleRect);
    bool loadTexture(SDL_Renderer* renderer, const std::string& filePath);

    float offset = radius;
    int ballX = 650, ballY = 350;
    int npcScore = 0;
    int playerScore = 0;
private:
    SDL_Texture* texture = nullptr;
    float radius = 30;
    float velocityY = 12;
    float velocityX = 12;
};

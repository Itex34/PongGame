#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>
#include <iostream>

class Paddle {
public:
    Paddle();
    ~Paddle();

    void update();
    void render(SDL_Renderer* renderer, int windowWidth, int windowHeight);

    bool loadTexture(SDL_Renderer* renderer, const std::string& filePath);

private:
    SDL_Texture* texture;
    int width = 100, height = 20;

    float playerPaddleY = 700/2;
    float playerPaddleAngle = 90;

    float computerPaddleY = 700 / 2;
    float computerPaddleAngle = 90;
};


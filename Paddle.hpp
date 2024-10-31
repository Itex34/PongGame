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

    SDL_Rect getRect() const;
    bool loadTexture(SDL_Renderer* renderer, const std::string& filePath);

    int playerPaddleY = 700 / 2 + (height / 2);
    float playerPaddleAngle = 0;
    
    SDL_Rect dstRect = { (0 - width / 2) + 100, playerPaddleY, width, height };
private:
    SDL_Texture* texture = nullptr;
    int width = 15, height = 150;
};


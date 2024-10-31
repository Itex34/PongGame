#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>
#include <iostream>

class NPCPaddle {
public:
    NPCPaddle();
    ~NPCPaddle();

    void update();
    void render(SDL_Renderer* renderer, int windowWdith, int y);
    SDL_Rect getRect() const;

    bool loadTexture(SDL_Renderer* renderer, const std::string& filePath);

    int NPCPaddleY = 700 / 2 + (height / 2);
    float NPCPaddleAngle = 0;

    SDL_Rect dstRect = { (0 - width / 2) + 1200, NPCPaddleY, width, height };
private:
    SDL_Texture* texture = nullptr;
    int width = 15, height = 150;
};

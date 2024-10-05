#include "Paddle.hpp"

Paddle::Paddle() {}
Paddle::~Paddle() {}


void Paddle::update() {
    const Uint8* state = SDL_GetKeyboardState(nullptr);
    if (state[SDL_SCANCODE_LEFT]) {
        playerPaddleAngle -= 2;
    }
    if (state[SDL_SCANCODE_RIGHT]) {
        playerPaddleAngle += 2;
    }

    if (playerPaddleY <= 650) {
        if (state[SDL_SCANCODE_DOWN]) {
            playerPaddleY += 4;
        }
    }

    if (playerPaddleY >= 50) {
        if (state[SDL_SCANCODE_UP]) {
            playerPaddleY -= 4;
        }
    }
}

void Paddle::render(SDL_Renderer* renderer, int windowWidth, int windowHeight) {
    if (texture != nullptr) {
        SDL_Rect dstRect = { 20, playerPaddleY, width, height };
        SDL_Point center = { width / 2, height / 2 };

        SDL_RenderCopyEx(renderer, texture, nullptr, &dstRect, playerPaddleAngle, &center, SDL_FLIP_NONE);
    }
}

bool Paddle::loadTexture(SDL_Renderer* renderer, const std::string& filePath) {
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
        return false;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return false;
    }

    width = surface->w;
    height = surface->h;

    SDL_FreeSurface(surface);
    return true;
}

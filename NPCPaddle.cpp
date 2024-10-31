#include "NPCPaddle.hpp"

NPCPaddle::NPCPaddle() {}
NPCPaddle::~NPCPaddle() {}


void NPCPaddle::update() {
    const Uint8* state = SDL_GetKeyboardState(nullptr);
    if (state[SDL_SCANCODE_LEFT]) {
        NPCPaddleAngle -= 2;
    }
    if (state[SDL_SCANCODE_RIGHT]) {
        NPCPaddleAngle += 2;
    }

    if (NPCPaddleY <= 550) {
        if (state[SDL_SCANCODE_DOWN]) {
            NPCPaddleY += 16;
        }
    }

    if (NPCPaddleY >= 0) {
        if (state[SDL_SCANCODE_UP]) {
            NPCPaddleY -= 16;
        }
    }
}

void NPCPaddle::render(SDL_Renderer* renderer, int windowWidth, int y) {
    if (texture != nullptr) {
        dstRect = { (0 - width / 2) + 1200, NPCPaddleY, width, height };
        SDL_Point center = { width / 2, height / 2 };

        SDL_RenderCopyEx(renderer, texture, nullptr, &dstRect, NPCPaddleAngle, &center, SDL_FLIP_NONE);
    }
}

bool NPCPaddle::loadTexture(SDL_Renderer* renderer, const std::string& filePath) {
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

    //width = surface->w;
    //height = surface->h;

    SDL_FreeSurface(surface);
    return true;
}

SDL_Rect NPCPaddle::getRect() const {
    return dstRect;
}

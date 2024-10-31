#include "Ball.hpp"
#include "Paddle.hpp"
#include "NPCPaddle.hpp"

Ball::Ball() {}
Ball::~Ball() {}


void Ball::update(SDL_Renderer* renderer, int windowWidth, int windowHeight, int Y) {

    ballX -= velocityX;
    ballY -= velocityY;

    if (ballY <= 0 || ballY + radius >= windowHeight) {
        velocityY = -velocityY;
    }

    if (checkCollision(paddle.getRect()) || checkNPCCollision(renderer, npcPaddle.getRect())) {
        velocityX = -velocityX; 
    }

    if (ballX >= windowWidth) {
        npcScore += 1;
        ballX = windowWidth / 2;
        ballY = Y;
    }

    if (ballX <= 0) {
        playerScore += 1;
        ballX = windowWidth / 2;
        ballY = Y;
    }

    if (npcScore <= 10 || playerScore <= 10)
    {
        std::cout << "Player score : " << playerScore << '\n';
        std::cout << "NPC score : " << npcScore << '\n';
    }

    if (npcScore >= 10) {
        SDL_Quit();
        std::cout << "Left player won!" << '\n';
    }

    if (playerScore >= 10) {
        SDL_Quit();
        std::cout << "Right player won!" << '\n';
    }
}

void Ball::render(SDL_Renderer* renderer, int windowWidth, int windowHeight) {
    if (texture != nullptr) {
        SDL_Rect dstRect = { ballX - offset, ballY - offset, radius, radius };

        SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
    }
}

bool Ball::loadTexture(SDL_Renderer* renderer, const std::string& filePath) {
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

    //radius = surface->w;
    //radius = surface->h;

    SDL_FreeSurface(surface);
    return true;
}

bool Ball::checkCollision(const SDL_Rect& tempPaddleRect) {
    SDL_Rect ballRect = { ballX, ballY, radius, radius };


    return SDL_HasIntersection(&ballRect, &tempPaddleRect);
}

bool Ball::checkNPCCollision(SDL_Renderer* renderer, const SDL_Rect& tempPaddleRect) {

    SDL_Rect ballRect = { ballX, ballY, radius, radius };

    return SDL_HasIntersection(&ballRect, &tempPaddleRect);
}

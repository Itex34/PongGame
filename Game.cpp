#include "Game.hpp"

Game::Game()
{}

Game::~Game()
{}
extern Ball ball;
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;


	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0 && TTF_Init() == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}

}

void Game::handleEvents()
{
	SDL_Event event;

	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}

}

void Game::update()
{
	cnt++;
}

void Game::render(int windowHeight, int windowWidth)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_Rect netLine;
	float netWidth = windowWidth / 100;
	float netHeight = windowHeight;
	netLine.x = windowWidth / 2 - netWidth / 2;
	netLine.y = 0;
	netLine.w = netWidth;
	netLine.h = netHeight;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &netLine);

	TTF_Font* Sans = TTF_OpenFont("sans.ttf", 150);
	if (Sans == nullptr)
	{
		std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
		return;
	}

	SDL_Color White = { 255, 255, 255 };

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "Player 1 score : ", White);
	if (surfaceMessage == nullptr)
	{
		std::cerr << "Failed to render text surface: " << TTF_GetError() << std::endl;
		TTF_CloseFont(Sans);
		return;
	}

	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	if (Message == nullptr)
	{
		std::cerr << "Failed to create text texture: " << SDL_GetError() << std::endl;
		SDL_FreeSurface(surfaceMessage);
		TTF_CloseFont(Sans);
		return;
	}

	SDL_Rect Message_rect;
	Message_rect.x = 200;
	Message_rect.y = 20;
	Message_rect.w = 200;
	Message_rect.h = 70;

	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
	TTF_CloseFont(Sans);

}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
	SDL_Quit();
}
SDL_Renderer* Game::getRenderer() const {
	return renderer;
}

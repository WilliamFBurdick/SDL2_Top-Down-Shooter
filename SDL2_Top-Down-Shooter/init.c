#include "common.h"

#include "init.h"
#include "structs.h"
#include "stage.h"

#include "bullets.h"
#include "text.h"
#include "items.h"
#include "enemies.h"
#include "effects.h"
#include "player.h"
#include "sound.h"
#include "highscores.h"

extern App app;
extern Stage stage;

void initSDL(void) {
	int rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	int windowFlags = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Failed to initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	app.window = SDL_CreateWindow("Shooter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

	if (!app.window) {
		printf("Failed to create %d x %d window: %s", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
		exit(1);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);

	if (!app.renderer) {
		printf("Failed to create renderer: %s", SDL_GetError());
		exit(1);
	}

	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	SDL_ShowCursor(0);

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		printf("Couldn't initialize SDL Mixer\n");
		exit(1);
	}
	Mix_AllocateChannels(MAX_SND_CHANNELS);
}

void cleanup(void) {
	Mix_Quit();
	IMG_Quit();
	SDL_DestroyRenderer(app.renderer);
	SDL_DestroyWindow(app.window);
	SDL_Quit();
}

void initGame(void) {
	initFonts();
	initPlayer();
	initEnemies();
	initBullets();
	initItems();
	initEffects();
	initSounds();
	initHighscoreTable();
	memset(&stage, 0, sizeof(Stage));
	loadMusic("../music/fight_looped.ogg");
	playMusic(1);
}
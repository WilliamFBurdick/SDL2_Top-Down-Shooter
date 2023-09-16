#pragma once

typedef struct Texture Texture;
typedef struct Entity Entity;
typedef struct Effect Effect;

typedef struct {
	void (*logic)(void);
	void (*draw)(void);
} Delegate;

struct Texture {
	char name[MAX_NAME_LENGTH];
	SDL_Texture* texture;
	Texture* next;
};

typedef struct {
	int x, y;
	int button[MAX_MOUSE_BUTTONS];
	int wheel;
} Mouse;

struct Effect {
	float x, y;
	float dx, dy;
	int life;
	SDL_Color color;
	SDL_Texture* texture;
	Effect* next;
};

struct Entity {
	int side;
	float x, y;
	int w, h;
	int radius;
	float dx, dy;
	int health;
	int reload;
	int angle;
	int weaponType;
	SDL_Texture* texture;
	SDL_Color color;

	void (*tick)(void);
	void (*touch)(Entity* other);
	void (*die)(void);
	Entity* next;
};

typedef struct {
	SDL_Renderer* renderer;
	SDL_Window* window;
	Delegate delegate;
	int keyboard[MAX_KEYBOARD_KEYS];
	Mouse mouse;
	Texture textureHead, * textureTail;
	char inputText[MAX_LINE_LENGTH];
} App;

typedef struct {
	int score;
	Entity entityHead, *entityTail;
	Entity bulletHead, * bulletTail;
	Effect effectHead, * effectTail;
	int ammo[WPN_MAX];
	SDL_Point camera;
} Stage;

typedef struct {
	char name[MAX_SCORE_NAME_LENGTH];
	int recent, score;
} Highscore;

typedef struct {
	Highscore highscore[NUM_HIGHSCORES];
} Highscores;
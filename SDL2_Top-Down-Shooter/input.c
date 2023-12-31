#include "common.h"
#include "input.h"

extern App app;

static void handleKeydown(SDL_KeyboardEvent* event) {
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS){
		app.keyboard[event->keysym.scancode] = 1;
	}
}

static void handleKeyup(SDL_KeyboardEvent* event) {
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS) {
		app.keyboard[event->keysym.scancode] = 0;
	}
}

static void doMouseButtonUp(SDL_MouseButtonEvent* event) {
	app.mouse.button[event->button] = 0;
}

static void doMouseButtonDown(SDL_MouseButtonEvent* event) {
	app.mouse.button[event->button] = 1;
}

void handleInput(void) {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			exit(0);
			break;
		case SDL_KEYDOWN:
			handleKeydown(&event.key);
			break;
		case SDL_KEYUP:
			handleKeyup(&event.key);
			break;
		case SDL_MOUSEBUTTONDOWN:
			doMouseButtonDown(&event.button);
			break;
		case SDL_MOUSEBUTTONUP:
			doMouseButtonUp(&event.button);
			break;
		case SDL_MOUSEWHEEL:
			app.mouse.wheel = event.wheel.y;
			break;
		default:
			break;
		}
	}

	SDL_GetMouseState(&app.mouse.x, &app.mouse.y);
}
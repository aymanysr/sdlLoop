#include <stdio.h>
#include <SDL2/SDL.h>
#include "./constants.h"

int game_is_running = FALSE;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

struct ball {
  float x;
  float y;
  float width;
  float height;
} ball;

int initialize_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        return FALSE;
    }
    // SDL_Window * SDL_CreateWindow(const char *title,
    //                           int x, int y, int w,
    //                           int h, Uint32 flags);
    window = SDL_CreateWindow(
        "SDL2 \\o/",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0
    );
    if (!window) {
        fprintf(stderr, "Error creating SDL Window\n");
        return FALSE;
    }
    // SDL_Renderer * SDL_CreateRenderer(SDL_Window * window,
    //                    int index, Uint32 flags);
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
    {
        fprintf(stderr, "Error creating SDL Renderer\n");
        return FALSE;
    }

    return TRUE;
}

void process_input() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            game_is_running = FALSE;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                game_is_running = FALSE;
            break;
    }
}

void setup() {
  ball.x = 20;
  ball.y = 20;
  ball.width = 15;
  ball.height = 15;
}

void update() {
  ball.x += 1;
  ball.y += 1;
}

void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // here is where we can start drawing our game objects

    // first i'll draw a rectangle
    SDL_Rect ball_rect = {
      (int)ball.x,
      (int)ball.y,
      (int)ball.width,
      (int)ball.height
    };

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &ball_rect);

    SDL_RenderPresent(renderer);
}

void destroy_window() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


int main() {
    game_is_running = initialize_window();

    setup();

    // the holy trinity of the game loop
    while (game_is_running) {
        // responsible for exiting the game
        process_input();
        update();
        render();
    }

    destroy_window();

    return FALSE;
}

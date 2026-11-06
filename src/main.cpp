#include <SDL3/SDL.h>
#include <vector>

const int WIDTH = 800;
const int HEIGHT = 600;
const int BYTES = 4;

int main() {

    std::vector<unsigned char> framebuffer;
    framebuffer.resize(WIDTH * HEIGHT * BYTES);


    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Nostos",
        WIDTH,
        HEIGHT,
        SDL_WINDOW_RESIZABLE
    );

    if (!window) {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
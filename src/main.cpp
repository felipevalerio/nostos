#include <SDL3/SDL.h>
#include <vector>

const int WIDTH = 320;
const int HEIGHT = 200;

std::vector<unsigned char> framebuffer(WIDTH * HEIGHT);

int main() {

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    
    window = SDL_CreateWindow(
        "Nostos",
        WIDTH,
        HEIGHT,
        SDL_WINDOW_RESIZABLE
    );

    renderer = SDL_CreateRenderer(window, NULL);
    texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_XRGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        WIDTH, HEIGHT
    );

    framebuffer[0] = 0x00FF00;

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

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
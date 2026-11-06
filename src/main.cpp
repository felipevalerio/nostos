#include <SDL3/SDL.h>
#include <vector>
#include <cstdint>

const int WIDTH = 320;
const int HEIGHT = 200;

std::vector<uint32_t> framebuffer(WIDTH * HEIGHT);

int main() {

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);

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


    bool running = true;

    while (running) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        framebuffer[0] = 0x0000FF00;

        // copia o conteúdo do framebuffer para o texture
        SDL_UpdateTexture(
            texture,
            NULL,
            framebuffer.data(),
            WIDTH * sizeof(uint32_t) // WIDTH * 4 bytes
        );

        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
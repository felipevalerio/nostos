#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include <cstdint>

const int WIDTH = 320;
const int HEIGHT = 200;

std::vector<uint32_t> framebuffer(WIDTH * HEIGHT);


void putPixel(uint32_t x, uint32_t y, uint32_t color) {

    if (x < WIDTH && y < HEIGHT) {

        uint32_t index = y * WIDTH + x;
        framebuffer[index] = color;
    } else {
        std::cout << "Out of bounds!" << std::endl;
    }
    
}

void dda() {
    
}


int main() {

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
        "Nostos",
        WIDTH * 4,
        HEIGHT * 4,
        SDL_WINDOW_RESIZABLE
    );

    renderer = SDL_CreateRenderer(window, NULL);
    texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_XRGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        WIDTH, HEIGHT
    );

    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

    bool running = true;

    while (running) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        for (size_t y = 0; y < 10; y++) {
            for (size_t x = 0; x < 10; x++) {
                uint32_t index = y * WIDTH + x;
                framebuffer[index] = 0x0000FF00;
            }
        }
        

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
#include <iostream>
#include <SDL2/SDL.h>

#include "mesh.h"
#include "screen.h"

int SCREEN_WIDTH = 320;
int SCREEN_HEIGHT = 240;

int main(int argc, char *args[]) {
    if (argc < 2) {
        printf("Error need a filename arg.");
        return 1;
    }
    if (argc < 3) {
        printf("Need a matrix arg.");
        return 2;
    }

    point<float> light(-20, 0, -20);
    light = light / light.mag();
    screen screen(SCREEN_WIDTH, SCREEN_HEIGHT, 255);
    std::ifstream infile(args[1]);
    mesh<float> teapot(infile);

    std::ifstream inmatrix(args[2]);

    // Rotate and scale the input mesh in order to fit into the screen for debugging.
    matrix transform(inmatrix);
    transform.scale(1);
    teapot.transform(transform);

    std::ifstream inrotation("rotation.txt");
    matrix rotation(inrotation);

    //The window we'll be rendering to
    SDL_Window *window = NULL;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    //Create window
    window = SDL_CreateWindow("Burn Walton", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen.width * 6,
                              screen.height * 6, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    //Get window surface
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture *texture = SDL_CreateTexture(renderer,
                                             SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH,
                                             SCREEN_HEIGHT);
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    while(true) {
        for (triangle &t : teapot.triangles) {
            t.normal();
            t.throw_shade(light);
            point<int> screen_cords1 = screen.projection(*t.v1);
            point<int> screen_cords2 = screen.projection(*t.v2);
            point<int> screen_cords3 = screen.projection(*t.v3);

            color faded_color = t.fade_color();
            uint32_t colour = faded_color.pack();

            screen.draw_line(screen_cords1, screen_cords2, colour);
            screen.draw_line(screen_cords1, screen_cords3, colour);
            screen.draw_line(screen_cords2, screen_cords3, colour);
           // screen.draw_triangle(screen_cords1, screen_cords2, screen_cords3, colour);
        }

        SDL_UpdateTexture(texture, NULL, screen.pixels.data(), SCREEN_WIDTH * sizeof(Uint32));

        SDL_RenderClear(renderer);
        SDL_RenderCopyEx(renderer, texture, NULL, NULL, 0, NULL, SDL_FLIP_VERTICAL);
        SDL_RenderPresent(renderer);

        SDL_Delay(60);
        teapot.transform(rotation);
        screen.clear();
    }

    //Destroy window
    SDL_DestroyWindow(window);

    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}



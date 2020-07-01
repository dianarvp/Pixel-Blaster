#include <iostream>
#include <SDL2/SDL.h>

#include "mesh.h"
#include "screen.h"

int main(int argc, char *args[]) {
    if (argc < 2) {
        printf("Error need a filename arg.");
        return 1;
    }
    if (argc < 3) {
        printf("Need a matrix arg.");
        return 2;
    }

    point<float> light(1, 1, 1);
    light = light / light.mag();
    screen screen(640, 480, 255);
    std::ifstream infile(args[1]);
    mesh<float> teapot(infile);

    std::ifstream inmatrix(args[2]);

    // Rotate and scale the input mesh in order to fit into the screen for debugging.
    matrix transform(inmatrix);
    transform.scale(0.01);
    teapot.transform(transform);

    //The window we'll be rendering to
    SDL_Window *window = NULL;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    } else {
        //Create window
        window = SDL_CreateWindow("Burn Walton", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen.width,
                                  screen.height, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        } else {
            //Get window surface
            SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
            SDL_Texture *texture = SDL_CreateTexture(renderer,
                                                     SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 640, 480);

            for (triangle &t : teapot.triangles) {
                t.normal();
                t.color(light);
                point<int> screen_cords1 = screen.projection(*t.v1);
                point<int> screen_cords2 = screen.projection(*t.v2);
                point<int> screen_cords3 = screen.projection(*t.v3);

                screen.draw_line(screen_cords1, screen_cords2, t.shade * 255);
                screen.draw_line(screen_cords1, screen_cords3, t.shade * 255);
                screen.draw_line(screen_cords2, screen_cords3, t.shade * 255);
                screen.draw_triangle(screen_cords1, screen_cords2, screen_cords3, t.shade * 255);
            }

            SDL_UpdateTexture(texture, NULL, screen.pixels.data(), 640 * sizeof(Uint32));

            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);

            //Wait two seconds
            SDL_Delay(3000);
        }
    }

    //Destroy window
    SDL_DestroyWindow(window);

    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}



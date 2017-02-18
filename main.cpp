#include <iostream>
#include <SDL.h>
#include <vector>

#include "object.h"
#include "matrix.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_DEPTH = 255;

const Uint32 color = 255;
Uint32 get_pixel32( SDL_Surface *surface, int x, int y )
{
    //Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;

    //Get the requested pixel
    return pixels[ ( y * surface->w ) + x ];
}

void put_pixel32( SDL_Surface *surface, int x, int y, Uint32 pixel )
{
    //Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;

    //Set the pixel
    pixels[ ( y * surface->w ) + x ] = pixel;
}

int main(int argc, char *args[]) {
    if(argc<2) {
        printf("Error need a filename arg.");
        return 1;
    }
    if(argc<3) {
        printf("Need a matrix arg.");
        return 2;
    }
    std::ifstream infile(args[1]);
    object<float> teapot(infile);

    std::ifstream inmatrix(args[2]);

    matrix transform(inmatrix);
    std::cout << transform <<"\n";
    teapot.transform(transform);

    for(const triangle &t : teapot.triangles) {
        std::cout << "point1: " << *t.v1 << " point 2: " << *t.v2 << " point 3: " << *t.v3 << std::endl;
        point<float> norm = t.normal();
        std::cout << "norm: " << norm << " mag: " << norm.mag() << std::endl;
        std::cout << "perp1: " << norm.dot(*t.v1-*t.v2) << " perp2: " << norm.dot(*t.v1-*t.v3) << " perp3: " << norm.dot(*t.v2-*t.v3) <<std::endl;
        std:: cout << "\n";
    }

    //The window we'll be rendering to
    SDL_Window *window = NULL;

    //The surface contained by the window
    SDL_Surface *screenSurface = NULL;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    } else {
        //Create window
        window = SDL_CreateWindow("Burn Walton", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        } else {
            //Get window surface
            SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
            SDL_Texture * texture = SDL_CreateTexture(renderer,
                                                      SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 640, 480);
            std::vector<Uint32> pixels(640 * 480,23562462);

            for(point<float>& p:teapot.points) {
                point<int> screen_coords = p.screen_coords(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_DEPTH);
                if(screen_coords.inbounds(SCREEN_WIDTH, SCREEN_HEIGHT)) {
                    pixels[screen_coords[1] * SCREEN_WIDTH + screen_coords[0]] = 0;
                }
            }

            SDL_UpdateTexture(texture, NULL, pixels.data(), 640 * sizeof(Uint32));

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



#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "display.h"


bool is_running = false;


//setup function
void setup(void)
{
    //allocating required memory to hold color buffer
    color_buffer = (uint32_t*)malloc(sizeof(uint32_t) * window_width * window_height);
// creating a SDL texture that is used to display color buffer
    color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, window_width, window_height);
}
//process input function
void process_input(void)
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch(event.type)
    {
        case SDL_QUIT:
            is_running = false;
        break;
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_ESCAPE)
                is_running = false;
        break;
    }
}
//update function
void update(void)
{

}


//render function
void render(void)
{
    // clear_color_buffer(0xFF36FF00);
    // clear_color_buffer(0xFFFFFF00); // color format is |alphaalpha|RR|GG|BB|
    
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);

    // draw_grid();
    //draw_grid();

    render_color_buffer();
    //clear_color_buffer(0xFF36FF00); //paints the whole screen
    clear_color_buffer(0xFF000000); //so disabled to draw grid or paint it all black
    
    //drawing rectangle
    draw_rect(300,200,100,150,0xFFFF00FF);
    

    SDL_RenderPresent(renderer);
}

int main(void)
{
    is_running = initialize_window();

    setup();

    while (is_running)
    {
        process_input();
        update();
        render();
    }
    

    destroy_window();

    
    return 0;
}
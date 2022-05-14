#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "display.h"
#include "vector.h"

//////////////////////////////////////////////////////
// DECLARE An array of vectors/points
/////////////////////////////////////////////////////
//const int N_POINTS = 9 * 9 * 9; // points to descrive the object to be deawn
#define N_POINTS 9*9*9
vec3_t cube_points[N_POINTS];     // 9 x 9 x 9
vec2_t projected_points[N_POINTS];

float fov_factor = 128;

bool is_running = false;


//setup function
void setup(void)
{
    //allocating required memory to hold color buffer
    color_buffer = (uint32_t*)malloc(sizeof(uint32_t) * window_width * window_height);
// creating a SDL texture that is used to display color buffer
    color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, window_width, window_height);


    // start loading my array of vectors
    // fom -1 to 1 (in 9 x 9 x 9 cube)
    int point_count = 0;

    for(float x = -1; x <= 1; x+= 0.25)
    {
        for(float y = -1; y <= 1; y += 0.25)
        {
            for (float z = -1; z <= 1; z+=0.25)
            {
                vec3_t new_point = {.x = x, .y = y, .z = z};
                cube_points[point_count++] = new_point;
                

            }

        }
    }
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

////////////////////////////////////////////////////////////////////////////////
// function that takes 3d vector and return 2d projection of it
////////////////////////////////////////////////////////////////////////////////

vec2_t project(vec3_t point)
{
    vec2_t projected_point = 
    {
        .x = (fov_factor * point.x),
        .y = (fov_factor * point.y)
    };
    return projected_point;
}


//update function
void update(void)
{
    for(int i  = 0; i < N_POINTS; i++)
    {
        // project the current point
        vec3_t point = cube_points[i];

        //save the projected 2d vectors in array of projected points

        vec2_t projected_point = project(point);
        projected_points[i] = projected_point;
    }

}


//render function
void render(void)
{
    //draw_grid();

    // clear_color_buffer(0xFFFFFF00); // color format is |alphaalpha|RR|GG|BB|
    // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    // SDL_RenderClear(renderer);
    
    

    //loop all projected points
    for(int i  = 0; i < N_POINTS; i++)
    {
        vec2_t projected_point = projected_points[i];
        draw_rect(projected_point.x + (window_width/2),projected_point.y + (window_height/2),  8, 8,  0xFF00FF00);
    }

    render_color_buffer();
    //clear_color_buffer(0xFF36FF00); //paints the whole screen
    clear_color_buffer(0xFF000000); //so disabled to draw grid or paint it all black
    
    //drawing rectangle
    //draw_rect(1500,200,100,150,0xFFFF0000);

    //draw pixel
    //draw_pixel(300,200,0xFFFFFF00);



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
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>

//GLOBAL variable
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL ;
bool is_running = false;

uint32_t* color_buffer = NULL;// stores the address of an integer of 32 bits or array
int window_width = 800;
int window_height = 600;

bool initialize_window(void)
{
    //initializing hardware
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr,"Error initializing SDL.\n");
        return false;
    }
    //create a sdl window
    window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_BORDERLESS);
    if (!window)
    {
        fprintf(stderr, "Error creating SDL windoe.\n");
        return false;
    }

    // create SDl renderer
    renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer)
    {
        fprintf(stderr, "Error creating renderer\n");
        return false;
    }

    return true;
}

//setup function
void setup(void)
{
    color_buffer = (uint32_t)malloc(sizeof(uint32_t) * window_width * window_height);

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
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
}

//destroying windows
void destroy_window(void)
{
    free(color_buffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
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
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>


bool is_running = false;
//GLOBAL variable
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL ;


uint32_t* color_buffer = NULL;// stores the address of an integer of 32 bits or array
SDL_Texture* color_buffer_texture = NULL;
int window_width = 800;
int window_height = 600;
//-----------------------------------------------------------------------------
bool initialize_window(void)
{
    //initializing hardware
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr,"Error initializing SDL.\n");
        return false;
    }
    
    //USE SDL to query monitor screen size for FULL SCREEN SIZE
    
    SDL_DisplayMode display_mode;
    SDL_GetCurrentDisplayMode(0, &display_mode);
    window_width = display_mode.w;
    window_height = display_mode.h;
    
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
    //FOR FULL SCRENN VIDEO MODE
    //SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    return true;
}

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

void draw_grid(void) {
    for (int y = 0; y < window_height; y++)
    {
        for(int x = 0; x < window_width; x++)
        {
            if(x%10 == 0 || y %10 ==0 )
            {
                color_buffer[(window_width * y) + x ] = 0x000000FF;
            }
        }
    }
    // TODO:
}


//render color buffer
void render_color_buffer(void)
{
    SDL_UpdateTexture(
        color_buffer_texture, 
        NULL, 
        color_buffer, 
        (int)(window_width * sizeof(uint32_t)));

    SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}


//clearing the color buffer(memory) to draw every frame
void clear_color_buffer(uint32_t color)
{
    for (int y = 0; y  < window_height; y++)
    {
        for(int x = 0; x < window_width; x++)
        {
            // if((y%40)==0 || (x%40)==0)  /*made a GRID*/
            color_buffer[(window_width * y) + x] = color;
            

        }
    }
}
//render function
void render(void)
{
    // clear_color_buffer(0xFF36FF00);
    // clear_color_buffer(0xFFFFFF00);
    
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);

    // draw_grid();
    draw_grid();

    render_color_buffer();
    //clear_color_buffer(0xFF36FF00); //paints the whole screen
    clear_color_buffer(0xFF000000); //so disabled to draw grid
    
    

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
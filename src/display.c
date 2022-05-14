#include "display.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
uint32_t* color_buffer = NULL;
SDL_Texture* color_buffer_texture = NULL;
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


void draw_grid(void) {
    for (int y = 0; y < window_height; y++)
    {
        for(int x = 0; x < window_width; x++)
        {
            if(x%30 == 0 || y %30 ==0 )
            {
                color_buffer[(window_width * y) + x ] = 0x000000FF;
            }
        }
    }
    // TODO:
}


void draw_rect(int x, int y, int width, int height, uint32_t color)
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j <width; j++)
        {
            int current_x = x + i;
            int current_y = y + j;
            color_buffer[(window_width * current_y)+ current_x] = color;
        }
    }
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

//destroying windows
void destroy_window(void)
{
    free(color_buffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


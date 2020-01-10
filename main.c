#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <string.h>
#include "Struct.h"
#include "config.h"

int main(int argc, char** argv)
{
    Conf config;
    GetConfig("config\\general.conf",&config);
    int choose       = 0;
    int quit         = 0;
    int menu         = 0;
    int sound        = 1;
    int isFullscreen = 0;
    int actualWidth  = 0;
    int actualHeight = 0;
    int width        = 1280;
    int height       = 720;
    int res;
    switch(width){
    case 3840:
        res = 0;
        break;
    case 2560:
        res = 1;
        break;
    case 1920:
        res = 2;
        break;
    default:
        res = 3;
        break;
    }




    //  Initialization of SDL
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    //  Creation of the window
    SDL_Window * window = SDL_CreateWindow("RCP",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
        // Images loading
    //printf("hello\n");

    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

    char texture[50];
    SDL_Surface * surface;
    SDL_Texture * textures[14];
    FILE * texturefile = fopen(config.texturespath,"rb");


    for(int i = 0; i < 14 ;i++){

        fgets(texture,30,texturefile);
        texture[strlen(texture)-2]='\0';
        printf("Getting  : %s\n",texture);

        surface = IMG_Load(texture);
        printf("Loading  : %s\n",texture);

        if(!surface) {
            printf("IMG_Load : %s\n", IMG_GetError());
            return -1;
        }

        textures[i] = SDL_CreateTextureFromSurface(renderer, surface);
    }
        // creation of the textures
    Mix_Music * music_menu = Mix_LoadMUS("Sounds\\menu.mp3");
    Mix_PlayMusic(music_menu,-1);
    SDL_Event event;

    while (!quit)
    {
        SDL_WaitEvent(&event);

        switch (event.type)
        {
            case SDL_QUIT:
                quit = 1;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym){
                case SDLK_F11:
                    if(isFullscreen){
                        SDL_SetWindowFullscreen(window,0);
                        isFullscreen--;
                    }else{
                        SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN_DESKTOP);
                        isFullscreen++;
                    }
                    break;
                case SDLK_DOWN:
                    choose = ++choose%3;
                    break;
                case SDLK_UP:
                    if(--choose < 0)
                        choose += 3;
                    break;
                case SDLK_RETURN:
                    switch(menu){
                    case 0:
                        switch(choose){
                        case 0: // Play

                            break;
                        case 1: // Options
                            menu++;
                            choose = 0;
                            break;
                        case 2: // Quit
                            quit = 1;
                            choose = 0;
                            break;
                        }
                        break;
                    case 1:
                        switch(choose){
                        case 0: // Resolution
                            res = ++res%4;

                            switch(res){
                            case 0:
                                width  = 3840;
                                height = 2160;
                                break;
                            case 1:
                                width  = 2560;
                                height = 1440;
                                break;
                            case 2:
                                width  = 1920;
                                height = 1080;
                                break;
                            case 3:
                                width  = 1280;
                                height = 720;
                                break;
                            }
                            SDL_SetWindowSize(window,width,height);
                            break;
                        case 1: // Sounds
                            sound = ++sound%2;
                            if(sound == 0)
                                Mix_VolumeMusic(0);
                            else
                                Mix_VolumeMusic(MIX_MAX_VOLUME);
                            break;
                        case 2: // Return
                            menu--;
                            choose = 0;
                            break;
                        }
                        break;
                    }

                }
        }

        double menuWidth  = (double)actualWidth/1920*969;
        double menuHeight = (double)actualHeight/1080*135;
        double menuOffset = menuWidth*466/969;

        SDL_GetWindowSize(window,&actualWidth,&actualHeight);


        SDL_Rect dstrect_titre   = {actualWidth/2-menuOffset,  actualHeight/20*3 , menuWidth,    menuHeight};
        SDL_Rect dstrect_1       = {actualWidth/2-menuOffset,  actualHeight/20*10, menuWidth,    menuHeight};
        SDL_Rect dstrect_2       = {actualWidth/2-menuOffset,  actualHeight/20*13, menuWidth,    menuHeight};
        SDL_Rect dstrect_3       = {actualWidth/2-menuOffset,  actualHeight/20*16, menuWidth,    menuHeight};


        SDL_Rect dstrect_select  = {actualWidth/2-menuOffset,  actualHeight/20*(10+choose*3), menuWidth,    menuHeight};

        SDL_RenderCopy(renderer, textures[0], NULL, NULL);
        SDL_RenderCopy(renderer, textures[3], NULL, &dstrect_titre);



        SDL_RenderCopy(renderer, textures[2], NULL, &dstrect_select);

        if(menu == 0){

            SDL_RenderCopy(renderer, textures[4],    NULL, &dstrect_1);
            SDL_RenderCopy(renderer, textures[5],    NULL, &dstrect_2);
            SDL_RenderCopy(renderer, textures[6],    NULL, &dstrect_3);

        }
        else if(menu == 1){

            SDL_RenderCopy(renderer, textures[9+res],       NULL, &dstrect_1);
            SDL_RenderCopy(renderer, textures[7+sound],     NULL, &dstrect_2);
            SDL_RenderCopy(renderer, textures[13],          NULL, &dstrect_3);

        }


        SDL_RenderPresent(renderer);
    }
    SDL_Quit();
    return 0;
}

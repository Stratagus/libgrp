#include "main.hpp"

int main(int count,char *argv[])
{
    //Watches to see if a key is pressed
    SDL_Event keyPressedEvent;
    //Allow for repeated keys
    SDL_EnableKeyRepeat(50, 5);
    
    //Initialize basic SDL library
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER)==-1)
    {
        std::cout << "SDL was unable to initialize\n";
        return -1;
    }
    
    //Set the SDL surface window size
    //In this case 640x480 is sufficent
    SDL_Surface *colorPalettePreviewWindow = SDL_SetVideoMode(WINDOWWIDTH,WINDOWHEIGHT,8,SDL_SWSURFACE|SDL_HWPALETTE);
    
    //If the window was unable to allocate, fatal fail
    if(!colorPalettePreviewWindow)
    {
        std::cout << "Unable to create the SDL surface window\n";
        return -1;
    }
    
    //Get our palette loaded up into a SDL Colors
    ColorPalette myColorPalette;
    myColorPalette.LoadPalette(PALLETTEFILEPATH);
    myColorPalette.GenerateBasicColorTables();
    
    //Load the PaletteColors into SDL colors to be displayed.
    LoadSDLColors(colorPalettePreviewWindow, myColorPalette);
    
    //Allocate a simple background
    std::vector<int8_t> windowBackground(WINDOWWIDTH * WINDOWHEIGHT);
    
    for (int i=0;i<WINDOWHEIGHT;i++)
        for (int j=0;j<WINDOWWIDTH;j++)
            windowBackground[i*WINDOWWIDTH+j]=(int8_t)j;
    
    UpdateSurface(colorPalettePreviewWindow, windowBackground);
    //Wait for user interaction
    while (SDL_WaitEvent(&keyPressedEvent))
    {
        //Figure out what kind of input device caused the event
        switch (keyPressedEvent.type)
        {
            //Check what input device polled
            case SDL_KEYDOWN:
            {
                switch (*SDL_GetKeyName(keyPressedEvent.key.keysym.sym))
                {
                    case 'w':
                        std::cout << "Previous Table -\n";
                        UpdateSurface(colorPalettePreviewWindow, windowBackground);
                        break;
                    
                    case 'e':
                        std::cout << "Next Table +\n";
                        UpdateSurface(colorPalettePreviewWindow, windowBackground);
                        break;
                        
                    case 'q':
                        std::cout << "Exiting ShowPalette\n";
                        SDL_Quit();
                        //Shouldn't reach here
                        return 0;
                        break;
                    
                    //Any key press will update the display
                    default:
                        std::cout << "KeyPress: " << SDL_GetKeyName(keyPressedEvent.key.keysym.sym) << '\n'
                                  << "q - Quit, w - Previous Table, e - Next Table\n";
                        
                        break;
                }
                
                default:
                break;
            }

        }
    }
    return 0;
}

void LoadSDLColors(SDL_Surface *targetSurface, ColorPalette sourceColorPalette)
{
    SDL_Color sdlColors[sourceColorPalette.formattedPaletteData->size()];
    for(int currentColor = 0; currentColor < sourceColorPalette.formattedPaletteData->size(); currentColor++)
    {
        sdlColors[currentColor].r = sourceColorPalette.formattedPaletteData->at(currentColor).RedElement;
        sdlColors[currentColor].g = sourceColorPalette.formattedPaletteData->at(currentColor).GreenElement;
        sdlColors[currentColor].b = sourceColorPalette.formattedPaletteData->at(currentColor).BlueElement;
    }
    //Could save the SDL_SetPalette error, but for sample code it's not important
    SDL_SetPalette(targetSurface,SDL_LOGPAL|SDL_PHYSPAL,sdlColors,0,sourceColorPalette.formattedPaletteData->size());
}

void UpdateSurface(SDL_Surface *targetSurface, std::vector<int8_t> background)
{
    if (SDL_MUSTLOCK(targetSurface))
        SDL_LockSurface(targetSurface);
    //memmove(targetSurface->pixels, &background,WINDOWWIDTH*WINDOWHEIGHT);
    std::copy(background.begin(), background.end(), (char *)targetSurface->pixels);
    if (SDL_MUSTLOCK(targetSurface))
        SDL_UnlockSurface(targetSurface);
    //update screen
    SDL_UpdateRect(targetSurface, 0, 0, 0, 0);
}
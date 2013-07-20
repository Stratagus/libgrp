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
    
    //If you want to force the generation of derived color tables
    //at the start. Otherwise they are generated upon request.
    //myColorPalette.GenerateColorTables();
    
    //Load the PaletteColors into SDL colors to be displayed.
    LoadSDLColors(colorPalettePreviewWindow, myColorPalette);
    
    //Allocate a simple background
    std::vector<int8_t> windowBackground(WINDOWWIDTH * WINDOWHEIGHT);
    
    //Setup simple gradient
    for (int i=0;i<WINDOWHEIGHT;i++)
        for (int j=0;j<WINDOWWIDTH;j++)
            windowBackground[i*WINDOWWIDTH+j]=(int8_t)j;
    
    //Do an initial update on the screen
    UpdateSurface(colorPalettePreviewWindow, windowBackground);
    //Wait for user interaction
    while (SDL_WaitEvent(&keyPressedEvent))
    {
        //Figure out what kind of input device caused the event
        //Be it mouse, keyboard; we only care about the keyboard though
        switch (keyPressedEvent.type)
        {
            //Check what input device polled
            case SDL_KEYDOWN:
            {
                switch (*SDL_GetKeyName(keyPressedEvent.key.keysym.sym))
                {
                    //If the 'w' key is pressed load the previous color table
                    case 'w':
                        std::cout << "Previous Table -\n";
                        UpdateSurface(colorPalettePreviewWindow, windowBackground);
                        break;
                    
                    //If the 'e' key is pressed load the next color table
                    case 'e':
                        std::cout << "Next Table +\n";
                        UpdateSurface(colorPalettePreviewWindow, windowBackground);
                        break;
                        
                    //If the 'q' key is pressed quit the application
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
    colorValues currentProcessingColor;
    SDL_Color sdlColors[sourceColorPalette.GetNumberOfColors()];
    for(int currentColor = 0; currentColor < sourceColorPalette.GetNumberOfColors(); currentColor++)
    {
        currentProcessingColor = sourceColorPalette.GetColorFromPalette(currentColor);
        sdlColors[currentColor].r = currentProcessingColor.RedElement;
        sdlColors[currentColor].g = currentProcessingColor.GreenElement;
        sdlColors[currentColor].b = currentProcessingColor.BlueElement;
    }
    //Could save the SDL_SetPalette error, but for sample code it's not important
    SDL_SetPalette(targetSurface,SDL_LOGPAL|SDL_PHYSPAL,sdlColors,0,sourceColorPalette.GetNumberOfColors());
}

void UpdateSurface(SDL_Surface *targetSurface, std::vector<int8_t> background)
{
    if (SDL_MUSTLOCK(targetSurface))
        SDL_LockSurface(targetSurface);
    
    std::copy(background.begin(), background.end(), (char *)targetSurface->pixels);
    
    if (SDL_MUSTLOCK(targetSurface))
        SDL_UnlockSurface(targetSurface);
    
    //update screen
    SDL_UpdateRect(targetSurface, 0, 0, 0, 0);
}
#ifndef ShowPalette_H
#define ShowPalette_H

#include "../../Source/libgrp.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <SDL.h>

#define WINDOWWIDTH 640
#define WINDOWHEIGHT 480

#define SDL_LOGPAL 0x01
#define SDL_PHYSPAL 0x02

//This is used to allow the sample program to rotate between colorized palettes (Nothing libgrp related)
enum colorTableSelect {NONE, SHADOWTABLE, LIGHTTABLE, REDTABLE, BLUETABLE, GREENTABLE};

//Allow Windows to use 8/16/32 byte values
#if defined(_WIN32)
#include <stdint.h>
    typedef uint8_t u_int8_t;
    typedef uint16_t u_int16_t;
    typedef uint32_t u_int32_t;
#endif

void LoadSDLColors(SDL_Surface *targetSurface, ColorPalette sourceColorPalette);
void UpdateSurface(SDL_Surface *targetSurface, std::vector<int8_t> background);
void ApplyColorizedValues(ColorPalette applicationPalette, colorTableSelect selectedTable, colorValues targetColor);
void ApplyGRPImage(unsigned int xPosition, unsigned int yPosition, GRPImage targetGRPImage, unsigned int targetFrame);

#ifndef QUOTE
	#define Q(x) #x
	#define QUOTE(x) Q(x)
#endif

#ifndef PALLETTEFILEPATH
	#define PALLETTEFILEPATH QUOTE(SAMPLECONTENTDIR/SamplePalette.pal)
#endif

#ifndef GRPIMAGEFILEPATH
	#define GRPIMAGEFILEPATH QUOTE(SAMPLECONTENTDIR/SampleImage.grp)
#endif

#endif

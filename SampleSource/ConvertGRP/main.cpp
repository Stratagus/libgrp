#include "main.hpp"

#include <Magick++/Image.h>
#include <Magick++/Pixels.h>

int main()
{
    //Magick::InitializeMagick(NULL);
    //Magick::Image myImage("4x4", "white");
    
    //Magick::PixelPacket myPixel;
    //myPixel.red = 50;
    //myPixel.blue = 10;
    //myPixel.green = 1;
    //myImage.pixelColor(0, 0, myPixel);
    //myImage.write("test.png");
    
    
    GRPImage myGRPImage;
    ColorPalette myGRPPallete;
    myGRPPallete.LoadPalette(PALLETTEFILEPATH);
    myGRPImage.LoadImage(GRPIMAGEFILEPATH);
    myGRPImage.SetColorPalette(&myGRPPallete);
    
    myGRPImage.ConvertImage("test.png", 0, 1, false, false);
    return 0;
}
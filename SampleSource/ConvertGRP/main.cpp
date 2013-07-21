#include "main.hpp"


int main()
{
    
    GRPImage myGRPImage;
    ColorPalette myGRPPallete;
    myGRPPallete.LoadPalette(PALLETTEFILEPATH);
    myGRPImage.LoadImage(GRPIMAGEFILEPATH);
    myGRPImage.SetColorPalette(&myGRPPallete);
    
    myGRPImage.ConvertImage("test.png", 0, myGRPImage.getNumberOfFrames(), true, 17);
    return 0;
}
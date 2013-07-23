#include "main.hpp"


int main()
{
    ColorPalette myGRPPallete;
    myGRPPallete.LoadPalette(PALLETTEFILEPATH);
    GRPImage myGRPImage(GRPIMAGEFILEPATH, false);
    myGRPImage.SetColorPalette(&myGRPPallete);
    
    myGRPImage.SaveConvertedImage("outputWithDuplicates.png", 0, myGRPImage.getNumberOfFrames(), true, 17);
    
    myGRPImage.LoadImage(GRPIMAGEFILEPATH, true);
    myGRPImage.SaveConvertedImage("outputWithOUTDuplicates.png", 0, myGRPImage.getNumberOfFrames(), false, 17);
    
    
    
    return 0;
}
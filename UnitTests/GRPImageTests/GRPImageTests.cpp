#include "GRPImageTests.hpp"

BOOST_AUTO_TEST_SUITE(GRPImageTests)

BOOST_AUTO_TEST_CASE(LoadGRP)
{
    ColorPalette samplePalette;
    samplePalette.LoadPalette(PALETTEFILEPATH);
    samplePalette.GenerateBasicColorTables();
    
    GRPImage sampleImage;
    sampleImage.SetColorPalette(&samplePalette);
    sampleImage.LoadImage(GRPIMAGEFILEPATH);
    
}

BOOST_AUTO_TEST_SUITE_END()
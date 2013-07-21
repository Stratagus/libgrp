#include "GRPImageTests.hpp"

BOOST_AUTO_TEST_SUITE(GRPImageTests)

BOOST_AUTO_TEST_CASE(LoadGRP)
{
    ColorPalette *samplePalette = new ColorPalette;
    samplePalette->LoadPalette(PALETTEFILEPATH);
    samplePalette->GenerateColorTables();
    
    GRPImage sampleImage;
    sampleImage.SetColorPalette(samplePalette);
    sampleImage.LoadImage(GRPIMAGEFILEPATH);
    
    delete samplePalette;
    samplePalette = NULL;
}

BOOST_AUTO_TEST_SUITE_END()
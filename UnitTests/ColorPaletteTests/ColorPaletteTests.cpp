#include "ColorPaletteTests.hpp"

BOOST_AUTO_TEST_SUITE(ColorPaletteTests)

BOOST_AUTO_TEST_CASE(LoadPaletteFile)
{
    ColorPalette samplePalette;
    try
    {
        samplePalette.LoadPalette(PALLETTEFILEPATH);
        BOOST_ASSERT(true);
    }
    catch (...)
    {
        BOOST_ASSERT(false);
    }
}

BOOST_AUTO_TEST_CASE(LoadCurruptPaletteFile)
{
    ColorPalette curruptPalette;
    BOOST_REQUIRE_THROW(curruptPalette.LoadPalette(CURRUPTPALLETTEFILEPATH), CurruptColorPaletteException);
}

BOOST_AUTO_TEST_CASE(GenerateTransparentColorsTable)
{
    ColorPalette samplePalette;
    samplePalette.LoadPalette(PALLETTEFILEPATH);
    samplePalette.GenerateTransparentColorsTable();
}

BOOST_AUTO_TEST_CASE(GenerateGreyScaleTable)
{
    ColorPalette samplePalette;
    samplePalette.LoadPalette(PALLETTEFILEPATH);
    samplePalette.GenerateGreyscaleTable();
}

BOOST_AUTO_TEST_CASE(GenerateShadowTable)
{
    ColorPalette samplePalette;
    samplePalette.LoadPalette(PALLETTEFILEPATH);
    samplePalette.GenerateShadowtable();
}

BOOST_AUTO_TEST_CASE(GenerateLightTable)
{
    ColorPalette samplePalette;
    samplePalette.LoadPalette(PALLETTEFILEPATH);
    samplePalette.GenerateLighttable();
}
BOOST_AUTO_TEST_CASE(GenerateRedTable)
{
    ColorPalette samplePalette;
    samplePalette.LoadPalette(PALLETTEFILEPATH);
    samplePalette.GenerateRedtable();
}
BOOST_AUTO_TEST_CASE(GenerateGreenTable)
{
    ColorPalette samplePalette;
    samplePalette.LoadPalette(PALLETTEFILEPATH);
    samplePalette.GenerateGreentable();
}
BOOST_AUTO_TEST_CASE(GenerateBlueTable)
{
    ColorPalette samplePalette;
    samplePalette.LoadPalette(PALLETTEFILEPATH);
    samplePalette.GenerateBluetable();
}
#warning Write tests for set std::vectors of paletteData


BOOST_AUTO_TEST_SUITE_END()
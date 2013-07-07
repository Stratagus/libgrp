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

#warning Write tests for set std::vectors of paletteData


BOOST_AUTO_TEST_SUITE_END()
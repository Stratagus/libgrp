#include "ColorPaletteTests.hpp"

BOOST_AUTO_TEST_SUITE(ColorPaletteTests)

//Check if a palette can be loaded from a file
//at all
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

//Ensure that both the data coming in as a file
//or from a vector are the same.
BOOST_AUTO_TEST_CASE(LoadPaletteVector)
{
    std::vector<char> *imageData = new std::vector<char>;
    LoadFileToVector(PALLETTEFILEPATH, imageData);
    ColorPalette fromFile, fromMemory;
    colorValues fromFileColor, fromMemoryColor;    
    
    
    try
    {
        fromFile.LoadPalette(PALLETTEFILEPATH);
        fromFileColor = fromFile.GetColorFromPalette(5);
        
        fromMemory.LoadPalette(imageData);
        fromMemoryColor = fromMemory.GetColorFromPalette(5);
        
        bool colorValuesMatch = true;
        
        for (int currentColorPaletteCheck = 0; (currentColorPaletteCheck < fromFile.GetNumberOfColors()) && colorValuesMatch; currentColorPaletteCheck++)
        {
            fromFileColor = fromFile.GetColorFromPalette(currentColorPaletteCheck);
            fromMemoryColor = fromMemory.GetColorFromPalette(currentColorPaletteCheck);
            
            colorValuesMatch = (fromFileColor.RedElement == fromMemoryColor.RedElement) &&
                               (fromFileColor.GreenElement == fromMemoryColor.GreenElement) &&
                               (fromFileColor.BlueElement == fromMemoryColor.BlueElement);
        }
        
        if(colorValuesMatch)
        {
            delete imageData;
            imageData = nullptr;
            BOOST_ASSERT(true);
        }
        else
        {
            delete imageData;
            imageData = nullptr;
            BOOST_ASSERT(false);
        }
        
    }
    catch (...)
    {
        delete imageData;
        imageData = nullptr;
        BOOST_ASSERT(false);
    }
}

BOOST_AUTO_TEST_CASE(LoadPalettenullptr)
{
    ColorPalette nullptrPaletteData;
    BOOST_REQUIRE_THROW(nullptrPaletteData.LoadPalette(nullptr), CurruptColorPaletteException);
}

BOOST_AUTO_TEST_CASE(LoadCurruptPaletteFile)
{
    ColorPalette curruptPalette;
    BOOST_REQUIRE_THROW(curruptPalette.LoadPalette(CURRUPTPALLETTEFILEPATH), CurruptColorPaletteException);
}
BOOST_AUTO_TEST_CASE(LoadCurruptPaletteMemory)
{
    std::vector<char> *imageData = new std::vector<char>;
    LoadFileToVector(CURRUPTPALLETTEFILEPATH, imageData);
    ColorPalette curruptPalette;
    BOOST_REQUIRE_THROW(curruptPalette.LoadPalette(imageData), CurruptColorPaletteException);
    
    delete imageData;
    imageData = nullptr;
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


BOOST_AUTO_TEST_CASE(noPaletteDataGenerateTransparentTable)
{
    ColorPalette noDataPalette;
    BOOST_REQUIRE_THROW(noDataPalette.GenerateTransparentColorsTable(), NoPaletteLoadedException);
}

BOOST_AUTO_TEST_CASE(noPaletteDataGenerateGreyscaleTable)
{
    ColorPalette noDataPalette;
    BOOST_REQUIRE_THROW(noDataPalette.GenerateGreyscaleTable(), NoPaletteLoadedException);
}


BOOST_AUTO_TEST_CASE(noPaletteDataGenerateRedTable)
{
    ColorPalette noDataPalette;
    BOOST_REQUIRE_THROW(noDataPalette.GenerateRedtable(), NoPaletteLoadedException);
}

BOOST_AUTO_TEST_CASE(noPaletteDataGenerateGreenTable)
{
    ColorPalette noDataPalette;
    BOOST_REQUIRE_THROW(noDataPalette.GenerateGreentable(), NoPaletteLoadedException);
}

BOOST_AUTO_TEST_CASE(noPaletteDataGenerateBlueTable)
{
    ColorPalette noDataPalette;
    BOOST_REQUIRE_THROW(noDataPalette.GenerateBluetable(), NoPaletteLoadedException);
}

BOOST_AUTO_TEST_CASE(noPaletteDataGenerateConstraintsTable)
{
    ColorPalette noDataPalette;
    colorValues myColors;
    myColors.RedElement = 50;
    myColors.GreenElement = 20;
    myColors.BlueElement = 15;
    
    BOOST_REQUIRE_THROW(noDataPalette.GenerateTableWithConstraints(myColors, 25), NoPaletteLoadedException);
}

BOOST_AUTO_TEST_CASE(invalidGradationGenerateConstraintsTable)
{
    ColorPalette dataPalette;
    dataPalette.LoadPalette(PALLETTEFILEPATH);
    colorValues myColors;
    myColors.RedElement = 50;
    myColors.GreenElement = 20;
    myColors.BlueElement = 15;
    
    BOOST_REQUIRE_THROW(dataPalette.GenerateTableWithConstraints(myColors, -25), InvalidGradationValueException);
}

BOOST_AUTO_TEST_CASE(NegativeColorValuesGenerateConstraintsTable)
{
    ColorPalette dataPalette;
    dataPalette.LoadPalette(PALLETTEFILEPATH);
    colorValues myColors;
    myColors.RedElement = -50;
    myColors.GreenElement = -20;
    myColors.BlueElement = 15;
    
    try
    {
        dataPalette.GenerateTableWithConstraints(myColors, 25);
        BOOST_ASSERT(true);
    } catch (...)
    {
        BOOST_ASSERT(false);
    }
}

BOOST_AUTO_TEST_CASE(noPaletteDataGenerateColorizeTable)
{
    ColorPalette noDataPalette;
    
    colorValues myColors;
    myColors.RedElement = 50;
    myColors.GreenElement = 20;
    myColors.BlueElement = 15;
    
    colorValues myColors2;
    myColors2.RedElement = 50;
    myColors2.GreenElement = 20;
    myColors2.BlueElement = 15;
    
    BOOST_REQUIRE_THROW(noDataPalette.GenerateColorizedTable(25, myColors, myColors2),  NoPaletteLoadedException);
}

BOOST_AUTO_TEST_CASE(InvalidGenerateColorizeTable)
{
    ColorPalette goodDataPalette;
    goodDataPalette.LoadPalette(PALLETTEFILEPATH);
    
    colorValues myColors;
    myColors.RedElement = 50;
    myColors.GreenElement = 20;
    myColors.BlueElement = 15;
    
    colorValues myColors2;
    myColors2.RedElement = 50;
    myColors2.GreenElement = 20;
    myColors2.BlueElement = 15;
    
    BOOST_REQUIRE_THROW(goodDataPalette.GenerateColorizedTable(-25, myColors, myColors2), InvalidGradationValueException);
}

BOOST_AUTO_TEST_CASE(NegativeColorValuesGenerateColorizeTable)
{
    ColorPalette goodDataPalette;
    goodDataPalette.LoadPalette(PALLETTEFILEPATH);
    
    colorValues myColors;
    myColors.RedElement = 50;
    myColors.GreenElement = 20;
    myColors.BlueElement = 15;
    
    colorValues myColors2;
    myColors2.RedElement = 50;
    myColors2.GreenElement = 20;
    myColors2.BlueElement = 15;
    
    try
    {
        goodDataPalette.GenerateColorizedTable(25, myColors, myColors2);
        BOOST_ASSERT(true);
    } catch (...)
    {
        BOOST_ASSERT(false);
    }
}

BOOST_AUTO_TEST_CASE(NoPaletteDataApplyShadow)
{
    ColorPalette noData;
    colorValues myColor;
    
    myColor.RedElement = 10;
    myColor.GreenElement = 20;
    myColor.BlueElement = 30;
    
    BOOST_REQUIRE_THROW(noData.ApplyShadowValue(myColor, 0), NoPaletteLoadedException);
}

BOOST_AUTO_TEST_CASE(OutofBoundsApplyShadowLow)
{
    ColorPalette goodData;
    goodData.LoadPalette(PALLETTEFILEPATH);
    colorValues myColor;
    
    myColor.RedElement = 10;
    myColor.GreenElement = 20;
    myColor.BlueElement = 30;
    
    BOOST_REQUIRE_THROW(goodData.ApplyShadowValue(myColor, -1), OutofBoundsColorException);
}

BOOST_AUTO_TEST_CASE(OutofBoundsApplyShadowHigh)
{
    ColorPalette goodData;
    goodData.LoadPalette(PALLETTEFILEPATH);
    colorValues myColor;
    
    myColor.RedElement = 10;
    myColor.GreenElement = 20;
    myColor.BlueElement = 30;
    
    BOOST_REQUIRE_THROW(goodData.ApplyShadowValue(myColor, (goodData.GetNumberOfColors() * 1000)), OutofBoundsColorException);
}

BOOST_AUTO_TEST_CASE(NoPaletteDataApplyLight)
{
    ColorPalette noData;
    colorValues myColor;
    
    myColor.RedElement = 10;
    myColor.GreenElement = 20;
    myColor.BlueElement = 30;
    
    BOOST_REQUIRE_THROW(noData.ApplyLightValue(myColor, 0), NoPaletteLoadedException);
}

BOOST_AUTO_TEST_CASE(OutofBoundsApplyLightLow)
{
    ColorPalette goodData;
    goodData.LoadPalette(PALLETTEFILEPATH);
    colorValues myColor;
    
    myColor.RedElement = 10;
    myColor.GreenElement = 20;
    myColor.BlueElement = 30;
    
    BOOST_REQUIRE_THROW(goodData.ApplyLightValue(myColor, -1), OutofBoundsColorException);
}

BOOST_AUTO_TEST_CASE(OutofBoundsApplyLightHigh)
{
    ColorPalette goodData;
    goodData.LoadPalette(PALLETTEFILEPATH);
    colorValues myColor;
    
    myColor.RedElement = 10;
    myColor.GreenElement = 20;
    myColor.BlueElement = 30;
    
    BOOST_REQUIRE_THROW(goodData.ApplyLightValue(myColor, (goodData.GetNumberOfColors() * 1000)), OutofBoundsColorException);
}

BOOST_AUTO_TEST_CASE(NoPaletteDataApplyRed)
{
    ColorPalette noData;
    colorValues myColor;
    
    myColor.RedElement = 10;
    myColor.GreenElement = 20;
    myColor.BlueElement = 30;
    
    BOOST_REQUIRE_THROW(noData.ApplyRedValue(myColor, 0), NoPaletteLoadedException);
}

BOOST_AUTO_TEST_CASE(OutofBoundsApplyRedLow)
{
    ColorPalette goodData;
    goodData.LoadPalette(PALLETTEFILEPATH);
    colorValues myColor;
    
    myColor.RedElement = 10;
    myColor.GreenElement = 20;
    myColor.BlueElement = 30;
    
    BOOST_REQUIRE_THROW(goodData.ApplyRedValue(myColor, -1), OutofBoundsColorException);
}

BOOST_AUTO_TEST_CASE(OutofBoundsApplyRedHigh)
{
    ColorPalette goodData;
    goodData.LoadPalette(PALLETTEFILEPATH);
    colorValues myColor;
    
    myColor.RedElement = 10;
    myColor.GreenElement = 20;
    myColor.BlueElement = 30;
    
    BOOST_REQUIRE_THROW(goodData.ApplyRedValue(myColor, (goodData.GetNumberOfColors() * 1000)), OutofBoundsColorException);
}

BOOST_AUTO_TEST_CASE(NoPaletteDataApplyGreen)
{
    ColorPalette noData;
    colorValues myColor;
    
    myColor.RedElement = 10;
    myColor.GreenElement = 20;
    myColor.BlueElement = 30;
    
    BOOST_REQUIRE_THROW(noData.ApplyGreenValue(myColor, 0), NoPaletteLoadedException);
}

BOOST_AUTO_TEST_CASE(OutofBoundsApplyGreenLow)
{
    ColorPalette goodData;
    goodData.LoadPalette(PALLETTEFILEPATH);
    colorValues myColor;
    
    myColor.RedElement = 10;
    myColor.GreenElement = 20;
    myColor.BlueElement = 30;
    
    BOOST_REQUIRE_THROW(goodData.ApplyGreenValue(myColor, -1), OutofBoundsColorException);
}

BOOST_AUTO_TEST_CASE(OutofBoundsApplyGreenHigh)
{
    ColorPalette goodData;
    goodData.LoadPalette(PALLETTEFILEPATH);
    colorValues myColor;
    
    myColor.RedElement = 10;
    myColor.GreenElement = 20;
    myColor.BlueElement = 30;
    
    BOOST_REQUIRE_THROW(goodData.ApplyGreenValue(myColor, (goodData.GetNumberOfColors() * 1000)), OutofBoundsColorException);
}

BOOST_AUTO_TEST_CASE(NoPaletteDataApplyBlue)
{
    ColorPalette noData;
    colorValues myColor;
    
    myColor.RedElement = 10;
    myColor.GreenElement = 20;
    myColor.BlueElement = 30;
    
    BOOST_REQUIRE_THROW(noData.ApplyBlueValue(myColor, 0), NoPaletteLoadedException);
}

BOOST_AUTO_TEST_CASE(OutofBoundsApplyBlueLow)
{
    ColorPalette goodData;
    goodData.LoadPalette(PALLETTEFILEPATH);
    colorValues myColor;
    
    myColor.RedElement = 10;
    myColor.GreenElement = 20;
    myColor.BlueElement = 30;
    
    BOOST_REQUIRE_THROW(goodData.ApplyBlueValue(myColor, -1), OutofBoundsColorException);
}

BOOST_AUTO_TEST_CASE(OutofBoundsApplyBlueHigh)
{
    ColorPalette goodData;
    goodData.LoadPalette(PALLETTEFILEPATH);
    colorValues myColor;
    
    myColor.RedElement = 10;
    myColor.GreenElement = 20;
    myColor.BlueElement = 30;
    
    BOOST_REQUIRE_THROW(goodData.ApplyBlueValue(myColor, (goodData.GetNumberOfColors() * 1000)), OutofBoundsColorException);
}

//Ensure that things are deleted properly
BOOST_AUTO_TEST_CASE(LoadOverPalette)
{
    ColorPalette myPalette;
    try
    {
        myPalette.LoadPalette(PALLETTEFILEPATH);
        myPalette.GenerateColorTables();
        myPalette.LoadPalette(PALLETTEFILEPATH);
        myPalette.GenerateColorTables();
        BOOST_ASSERT(true);
    } catch (...)
    {
        BOOST_ASSERT(false);
    }

}

BOOST_AUTO_TEST_SUITE_END()
//Used to load files into vectors for testing
void LoadFileToVector(std::string filePath, std::vector<char> *destinationVector)
{
    std::fstream inputFile(filePath.c_str());
    
    inputFile.exceptions(
                         std::ifstream::badbit
                         | std::ifstream::failbit
                         | std::ifstream::eofbit);
    
    inputFile.seekg(0, std::ios::end);
    
    std::streampos length(inputFile.tellg());
    
    if (length)
    {
        inputFile.seekg(0, std::ios::beg);
        destinationVector->resize(static_cast<std::size_t>(length));
        inputFile.read((char *)&destinationVector->front(), static_cast<std::size_t>(length));
    }
}
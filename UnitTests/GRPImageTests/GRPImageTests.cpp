#include "GRPImageTests.hpp"

BOOST_AUTO_TEST_SUITE(GRPImageTests)

BOOST_AUTO_TEST_CASE(LoadGRPFILE)
{
    ColorPalette *samplePalette = new ColorPalette;
    samplePalette->LoadPalette(PALETTEFILEPATH);
    samplePalette->GenerateColorTables();
    
    GRPImage sampleImage(GRPIMAGEFILEPATH, false);
    sampleImage.SetColorPalette(samplePalette);
    
    delete samplePalette;
    samplePalette = NULL;
}

BOOST_AUTO_TEST_CASE(LoadGRPMEM)
{
    std::vector<char> *imageData = new std::vector<char>;
    LoadFileToVectorImageGRP(GRPIMAGEFILEPATH, imageData);
    try
    {
        GRPImage myImage(imageData);
    } catch (...)
    {
        BOOST_ASSERT(false);
    }
    
    
}

BOOST_AUTO_TEST_SUITE_END()

void LoadFileToVectorImageGRP(std::string filePath, std::vector<char> *destinationVector)
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
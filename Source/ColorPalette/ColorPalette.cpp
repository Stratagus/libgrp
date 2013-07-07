#include "ColorPalette.hpp"

ColorPalette::ColorPalette()
{

}

ColorPalette::~ColorPalette()
{

}

void ColorPalette::GenerateRedColorTable()
{

}

void ColorPalette::LoadPalette(std::vector<char> *inputPalette)
{
    if(paletteData != NULL)
    {
        delete paletteData;
    }
    paletteData = inputPalette;
}

void ColorPalette::LoadPalette(std::string filePath)
{
    if(paletteData == NULL)
    {
        paletteData = new std::vector<char>;
    }
    else
    {
        delete paletteData;
        paletteData = new std::vector<char>;
    }
    LoadFileToVector(filePath, paletteData);
    
#warning Throw a error if the pallete is not 1024 or 768 bit length
}

void ColorPalette::LoadFileToVector(std::string filePath, std::vector<char> *destinationVector)
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
        inputFile.read(&destinationVector->front(), static_cast<std::size_t>(length));
    }
}
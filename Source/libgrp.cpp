#include "libgrp.hpp"

GRPImage::GRPImage()
{
    imageData = NULL;
    paletteData = NULL;
}

GRPImage::~GRPImage()
{
    if(imageData != NULL)
    {
        delete imageData;
        imageData = NULL;
    }
    if(paletteData != NULL)
    {
        delete paletteData;
        paletteData = NULL;
    }
}

void GRPImage::LoadPalette(std::string filePath)
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
    
#warning Throw a error if the pallete is not 1024 or 768
}

void GRPImage::LoadImage(std::string filePath)
{
    if(imageData == NULL)
    {
        imageData = new std::vector<char>;
    }
    else
    {
        delete imageData;
        imageData = new std::vector<char>;
    }
    LoadFileToVector(filePath, imageData);
}

void GRPImage::ExtractMetaData()
{
    
    std::cout << "\n";
    if(imageData)
    {
        for (int i = 0; i < 6; i++)
        {
            std::cout << imageData->at(i);
        }
        std::cout << '\n' << "Image Size: " << imageData->size() << "\n";
    }
    if(paletteData)
    {
        for (int i = 0; i < 6; i++)
        {
            std::cout << paletteData->at(i);
        }
        std::cout << '\n' << "Pallet Size: " << paletteData->size() << "\n";
    }

}

void GRPImage::LoadFileToVector(std::string filePath, std::vector<char> *destinationVector)
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
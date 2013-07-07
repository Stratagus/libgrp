#include "libgrp.hpp"

GRPImage::GRPImage()
{
    imageData = NULL;
    paletteData = NULL;
    imageFrames = NULL;
    
    numberOfFrames = -1;
    maxWidth = -1;
    maxHeight = -1;
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
    if(imageFrames != NULL)
    {
        delete imageFrames;
        imageFrames = NULL;
    }
}

void GRPImage::LoadPalette(std::vector<char> *inputPalette)
{
    if(paletteData != NULL)
    {
        delete paletteData;
    }
    paletteData = inputPalette;
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
    
#warning Throw a error if the pallete is not 1024 or 768 bit length
}

void GRPImage::LoadImage(std::vector<char> *inputImage)
{
    if(imageData != NULL)
    {
        delete imageData;
    }
    imageData = inputImage;
    this->ExtractMetaData();
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
    
    //Load the numberOfFrames, maxWidth, maxHeigt
    this->ExtractMetaData();
}

uint16_t GRPImage::getNumberOfFrames() const
{
    return numberOfFrames;
}
uint16_t GRPImage::getMaxWidth() const
{
    return maxWidth;
}
uint16_t GRPImage::getMaxHeight() const
{
    return maxHeight;
}

void GRPImage::DecodeFrame(unsigned int frameNumber)
{
    if(frameNumber < 0)
    {
        throw "Bad frame number";
    }
    std::cout << "Decoding Frame: " << frameNumber << '\n';
    
    
}

void GRPImage::ExtractMetaData()
{
    //Copy raw chunks of the Frame Header and load them
    //into 16bit unsigned integers
    memcpy(&numberOfFrames, &imageData->at(0), 2);
    memcpy(&maxWidth, &imageData->at(2), 2);
    memcpy(&maxHeight, &imageData->at(4), 2);
    
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
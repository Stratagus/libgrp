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

void GRPImage::LoadPalette(std::vector<char> *inputPalette)
{
    
}
void GRPImage::LoadPalette(std::string filePath)
{
}
void GRPImage::LoadImage(std::vector<char> *inputImage)
{
    
}
void GRPImage::LoadImage(std::string filePath)
{
    
}
void GRPImage::ConvertImage()
{
    
}

std::vector<char> *GRPImage::SaveImage()
{
    return NULL;
}
void GRPImage::SaveImage(std::string filepath)
{
    
}

void GRPImage::LoadFileToVector(std::string filePath, std::vector<char> destinationVector)
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
        destinationVector.resize(static_cast<std::size_t>(length));
        inputFile.read(&destinationVector.front(), static_cast<std::size_t>(length));
    }
}
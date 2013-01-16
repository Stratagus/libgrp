#ifndef libgrp_H
#define libgrp_H

#include <vector>
#include <string>
#include <fstream>

#include "Exceptions/GRPException.hpp"


#warning Temporary Debug includes
#include <iostream>

class GRPImage
{
    
public:
    GRPImage();
    ~GRPImage();
    
    //Various ways of loading data
    void LoadPalette(std::vector<char> *inputPalette);
    void LoadPalette(std::string filePath);
    void LoadImage(std::vector<char> *inputImage);
    void LoadImage(std::string filePath);
    
    
    std::vector<char> *ExtractFrames(int frameNumberStart, int frameNumberEnd);
    void ExtractFrames(int frameNumberStart, int frameNumberEnd, std::string filePath);
    
    std::vector<char> *SaveImage();
    void SaveImage(std::string filepath);
    
#warning Should be in protected
    void ExtractMetaData();
    
protected:
    void LoadFileToVector(std::string sourceFilePath, std::vector<char> *destinationVector);
    void SaveVectorToFile(std::vector<char> *sourceVector, std::string destinationFilePath);
    
    
    
private:
    std::vector<char> *paletteData;
    std::vector<char> *imageData;
    
    //Frameheader Information
    uint8_t frameLeft;
    uint8_t frameTop;
    uint8_t frameWidth;
    uint8_t frameHeight;
    
    uint32_t frameOffset;
    
};

#endif
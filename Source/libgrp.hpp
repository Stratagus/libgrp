#ifndef libgrp_H
#define libgrp_H

#include <vector>
#include <string>
#include <fstream>

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
    
    void ConvertImage();
    
    std::vector<char> *SaveImage();
    void SaveImage(std::string filepath);
    
protected:
    void LoadFileToVector(std::string filePath, std::vector<char> destinationVector);
    
private:
    std::vector<char> *paletteData;
    std::vector<char> *imageData;
    
};

#endif
#include "GRPImage.hpp"

GRPImage::GRPImage()
{
    imageData = NULL;
    currentPalette = NULL;
    
    numberOfFrames = -1;
    maxImageWidth = -1;
    maxImageHeight = -1;
}

GRPImage::~GRPImage()
{
    if(imageData != NULL)
    {
        delete imageData;
        imageData = NULL;
    }
    if(currentPalette != NULL)
    {
        currentPalette = NULL;
    }
}
#warning Add error checking
void GRPImage::LoadImage(std::vector<char> *inputImage)
{
    
    if(imageData != NULL)
    {
        delete imageData;
    }
    //imageData = inputImage;
    this->ExtractMetaData();
}

void GRPImage::LoadImage(std::string filePath)
{
    if(imageData == NULL)
    {
        imageData = new std::vector<unsigned char>;
    }
    else
    {
        delete imageData;
        imageData = new std::vector<unsigned char>;
    }
    LoadFileToVector(filePath, imageData);
    
    std::ifstream inputFile(filePath.c_str(), std::ios::binary);
    inputFile.exceptions(std::ifstream::badbit | std::ifstream::failbit | std::ifstream::eofbit);
    
    
    //Read in some basic data about the grp.
    inputFile.read((char *) &numberOfFrames, 2);
    
    //Find the Maximum Image Width & Height
    inputFile.read((char *) &maxImageWidth, 2);
    inputFile.read((char *) &maxImageHeight, 2);
    
    //Load each GRP Header into a GRPFrame & Allocate the 
    for(int currentGRPFrame = 0; currentGRPFrame < numberOfFrames; currentGRPFrame++)
    {
        GRPFrame *currentImageFrame = new GRPFrame;
        
        inputFile.read((char *) &currentImageFrame->xPosition, 1);
        inputFile.read((char *) &currentImageFrame->yPosition, 1);
        inputFile.read((char *) &currentImageFrame->width, 1);
        inputFile.read((char *) &currentImageFrame->height, 1);
        inputFile.read((char *) &currentImageFrame->dataOffset, 4);
        
        //Decode Frame here
        DecodeGRPFrameData(inputFile, currentImageFrame);
        
        std::cout << "Current Frame: " << currentGRPFrame << " Width: " << (int) currentImageFrame->width << " Height: "
                                       << (int) currentImageFrame->height << "\nxPosition: " << (int) currentImageFrame->xPosition
                                       << " yPosition: " << (int) currentImageFrame->yPosition << " with offset " << (int)currentImageFrame->dataOffset << '\n';
        
        imageFrames.insert(imageFrames.end(), currentImageFrame);
    }
    std::cout << "Finished loading grpimages!\n";
    
    
    
}

void GRPImage::DecodeGRPFrameData(std::ifstream &inputFile, GRPFrame *targetFrame)
{
    if(targetFrame == NULL || currentPalette == NULL)
    {
        #warning throw here
        std::cout << "Problem";
    }
    //The current image pixel that we are working on
    uint8_t currentDataPacket;
    
    //Save the original file pointer position to continue loading GRPHeaders
    std::ifstream::pos_type currentHeaderFilePosition = inputFile.tellg();
    
    //Goto the GRPFrame data
    inputFile.seekg(targetFrame->dataOffset);

#warning Processing here
    
    //Finished put the file position back
    inputFile.seekg(currentHeaderFilePosition);
}

uint16_t GRPImage::getNumberOfFrames() const
{
    return numberOfFrames;
}
uint16_t GRPImage::getMaxImageWidth() const
{
    return maxImageWidth;
}
uint16_t GRPImage::getMaxImageHeight() const
{
    return maxImageHeight;
}

void GRPImage::ExtractMetaData()
{
    //Copy raw chunks of the Frame Header and load them
    //into 16bit unsigned integers
    memcpy(&numberOfFrames, &imageData->at(0), 2);
    memcpy(&maxImageWidth, &imageData->at(2), 2);
    memcpy(&maxImageHeight, &imageData->at(4), 2);
    
}

void GRPImage::LoadFileToVector(std::string filePath, std::vector<unsigned char> *destinationVector)
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

void GRPImage::SetColorPalette(ColorPalette *selectedColorPalette)
{
    if(selectedColorPalette != NULL)
    {
        currentPalette = selectedColorPalette;
    }
    else
    {
            throw "Invalid color palette";
    }
}

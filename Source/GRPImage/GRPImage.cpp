#include "GRPImage.hpp"

GRPImage::GRPImage()
{
    imageData = NULL;
    imageFrames = NULL;
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
    if(imageFrames != NULL)
    {
        delete imageFrames;
        imageFrames = NULL;
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

    //Expand the GRPFrames vector to allocate enough memory
    if(imageFrames == NULL)
    {
        imageFrames = new std::vector<GRPFrame>;
    }
    imageFrames->resize(numberOfFrames);
    
    //Load each GRP Header into a GRPFrame
    for(int currentGRPFrame = 0; currentGRPFrame < numberOfFrames; currentGRPFrame++)
    {
        GRPFrame *currentImageFrame;
        
        currentImageFrame = &imageFrames->at(currentGRPFrame);
        inputFile.read((char *) &currentImageFrame->xPosition, 1);
        inputFile.read((char *) &currentImageFrame->yPosition, 1);
        inputFile.read((char *) &currentImageFrame->width, 1);
        inputFile.read((char *) &currentImageFrame->height, 1);
        inputFile.read((char *) &currentImageFrame->dataOffset, 4);
    }
    std::cout << "Finished loading headers!\n";
    
    //std::cout << "Frame demensions " << (int) imageFrames->at(currentGRPFrame).imageWidth << "x" << (int) imageFrames->at(currentGRPFrame).imageHeight << "  SkipLeft: " << (int) imageFrames->at(currentGRPFrame).skipLeft << " SkipUp: " << (int)imageFrames->at(currentGRPFrame).skipUp << '\n' << "Offset " << (unsigned int) imageFrames->at(currentGRPFrame).offset << '\n';
    
    //Now that we have the metadata of the image lets start processing bytes :D
    //The current (X,Y) pixel we are processing, we will skip the blank areas of the GRP
    
    
    //std::cout << "Peek: " << inputFile.peek() << " at " << inputFile.tellg() << '\n';
    
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

void GRPImage::LoadImageToFrame(unsigned int FrameNumber)
{
#warning Error checking here
    unsigned int currentXPosition = 0, currentYPosition = 0;
    
    //Allocate the GRPFrame
    GRPFrame myFrame;
    myFrame.SetFrameSize(128, 128);
    //myFrame.frameData.begin()
   // std::vector<char>::iterator currentPosition = imageData->begin() + 5;
    //std::copy(currentPosition, myFrame.frameData.end(), myFrame.frameData.begin());
    
    
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

void GRPImage::ProcessGRPImage()
{
#warning For loop for all Frames
    if(imageFrames == NULL)
    {
        imageFrames = new std::vector<GRPFrame>;
    }
    std::cout << "Number of Frames: " << numberOfFrames << '\n';
    imageFrames->resize(numberOfFrames);
    LoadImageToFrame(0);
    //for(int currentProcessFrame = 0; currentProcessFrame < numberOfFrames; currentProcessFrame++)
    //{
    //    std::cout << "Unpacking Frame: " << currentProcessFrame << '\n';
    //}
}
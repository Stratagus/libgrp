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
#warning MUST IMPLEMENT
void GRPImage::LoadImage(std::vector<char> *inputImage)
{
}

void GRPImage::LoadImage(std::string filePath, bool removeDuplicates)
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
        
        //std::cout << "Current Frame: " << currentGRPFrame << " Width: " << (int) currentImageFrame->width << " Height: "
        //<< (int) currentImageFrame->height << "\nxPosition: " << (int) currentImageFrame->xPosition
        //<< " yPosition: " << (int) currentImageFrame->yPosition << " with offset " << (int)currentImageFrame->dataOffset << '\n';
        
        //Decode Frame here
        DecodeGRPFrameData(inputFile, currentImageFrame);
        

        
        imageFrames.insert(imageFrames.end(), currentImageFrame);
    }
    //std::cout << "Finished loading grpimages!\n";
    
    
    
}

void GRPImage::DecodeGRPFrameData(std::ifstream &inputFile, GRPFrame *targetFrame)
{
    if(targetFrame == NULL || currentPalette == NULL)
    {
        #warning throw here
        //std::cout << "Problem";
    }
    //The current image pixel that we are working on
    char rawPacket, convertedPacket;
    
    
    //Save the original file pointer position to continue loading GRPHeaders
    std::ifstream::pos_type currentHeaderFilePosition = inputFile.tellg();
    
    //Goto the GRPFrame data
    inputFile.seekg(targetFrame->dataOffset);
    int tmp;

    
#warning Select specific grp image type here
    //int currentProcessingRow = targetFrame->width; //The current X Position
    int currentProcessingColumn = targetFrame->height; //The current Y Position
    int currentProcessingRow = targetFrame->width;
    
    
    //std::cout << "Target offset " << targetFrame->dataOffset << '\n';
    /*while (currentProcessingColumn-- > 0)
    {
        currentProcessingRow = targetFrame->width;
        do
        {
            inputFile.read((char *) &rawPacket, 1);
            if(!(rawPacket & 0x80))
            {
                if(rawPacket & 0x40)
                {
                    rawPacket &= 0x3f;
                    currentProcessingRow -= rawPacket;
                    
                    //covertedPacket = tableof unitColor[ colorbyte+gr_gamenr];
                    targetFrame->frameData.insert(targetFrame->frameData.end(), rawPacket);
                    //vidadr+=packbyte;
                }
                else
                {
                    currentProcessingRow -= rawPacket;
                    tmp = rawPacket;
                    do
                    {
                        inputFile.read((char *)&convertedPacket, 1);
                        //covertedPacket = tableof unitColor[ colorbyte+gr_gamenr];
                        targetFrame->frameData.insert(targetFrame->frameData.end(), convertedPacket);
                    } while (--tmp);
                }
            }
            else
            {
                rawPacket &= 0x7f;
                currentProcessingRow -= rawPacket;
                targetFrame->frameData.insert(targetFrame->frameData.end(), rawPacket);
            }
        }while(currentProcessingRow > 0);*/
        //vidadr += wmaximx;
        //vidadr -= PixelPerLine;
#warning viadr?
    //}

    
    //Finished put the file position back
    //inputFile.seekg(currentHeaderFilePosition);
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
    currentPalette = selectedColorPalette;
    //if(selectedColorPalette != NULL)
    //{
     //   ;
    //}
    //else
    //{
     //       throw "Invalid color palette";
    //}
}

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
#if VERBOSE >= 2
    std::cout << "GRP Image Number of Frames: " << numberOfFrames << " maxWidth: " << maxImageWidth << " maxHeight: " << maxImageHeight << '\n';
#endif
    //Load each GRP Header into a GRPFrame & Allocate the 
    for(int currentGRPFrame = 0; currentGRPFrame < numberOfFrames; currentGRPFrame++)
    {
        GRPFrame *currentImageFrame = new GRPFrame;
        
        inputFile.read((char *) &currentImageFrame->xOffset, 1);
        inputFile.read((char *) &currentImageFrame->yOffset, 1);
        inputFile.read((char *) &currentImageFrame->width, 1);
        inputFile.read((char *) &currentImageFrame->height, 1);
        inputFile.read((char *) &currentImageFrame->dataOffset, 4);

#if VERBOSE >= 2
        std::cout << "Current Frame: " << currentGRPFrame << " Width: " << (int) currentImageFrame->width << " Height: "
        << (int) currentImageFrame->height << "\nxPosition: " << (int) currentImageFrame->xOffset
        << " yPosition: " << (int) currentImageFrame->yOffset << " with offset " << (int)currentImageFrame->dataOffset << '\n';
#endif

        //Decode Frame here
        DecodeGRPFrameData(inputFile, currentImageFrame);
        

        
        //imageFrames.insert(imageFrames.end(), currentImageFrame);
        imageFrames.push_back(currentImageFrame);
    }
    
}

void GRPImage::DecodeGRPFrameData(std::ifstream &inputFile, GRPFrame *targetFrame)
{
    if(targetFrame == NULL || (targetFrame->frameData.size() == 0))
    {
        GRPImageNoFrameLoaded noFrameLoaded;
        noFrameLoaded.SetErrorMessage("No GRP Frame is loaded");
    }
    if(currentPalette == NULL)
    {
        GRPImageNoLoadedPaletteSet noPaletteLoaded;
        noPaletteLoaded.SetErrorMessage("No palette has been set or loaded");
    }
    
    //Save the original file pointer position to continue loading GRPHeaders
    std::ifstream::pos_type currentHeaderFilePosition = inputFile.tellg();
    
    //Seek to the Row offset data
    inputFile.seekg(targetFrame->dataOffset);
    
    //Create a vector of all the Image row offsets
    std::vector<uint16_t> imageRowOffsets;
    imageRowOffsets.resize(targetFrame->height);
    
    //Read in the ImageRow offsets
    for (int currentReadingRowOffset = 0; currentReadingRowOffset < targetFrame->height; currentReadingRowOffset++)
    {
        inputFile.read((char *) &imageRowOffsets.at(currentReadingRowOffset), 2);
    }
    
    //The currentRow (x coordinate) that the decoder is at, it is used to
    //set the image position.
    int currentProcessingRow = 0;

    //The initial byte of data from the GRPFile
    //It is often the operation that will be done
    //of the proceding data
    uint8_t rawPacket;
    
    //The references to a particular color
    uint8_t convertedPacket;
    
    //The struct keeps a (X,Y) coordinates to the position
    //of the referenced color to allow for drawing on the screen
    //or Imagemagick to convert.
    UniquePixel currentUniquePixel;
    

    //Goto each row and process the row data
    for(int currentProcessingHeight = 0; currentProcessingHeight < targetFrame->height; currentProcessingHeight++)
    {
        
#if VERBOSE >= 2
        std::cout << "Current row offset is: " << (targetFrame->dataOffset + (imageRowOffsets.at(currentProcessingHeight))) << '\n';
#endif
        //Seek to the point of the first byte in the rowData from the
        //1.Skip over to the Frame data
        //2.Skip over by the Row offset mentioned in the list
        inputFile.seekg((targetFrame->dataOffset + (imageRowOffsets.at(currentProcessingHeight))));

        currentProcessingRow = 0;
        
        while(currentProcessingRow < targetFrame->width)
        {
            inputFile.read((char *) &rawPacket, 1);
            if(!(rawPacket & 0x80))
            {
                //Repeat Operation (The first byte indicates a repeat pixel operation)
                //The next byte indicates how far down the row to repeat.
                if(rawPacket & 0x40)
                {
                    rawPacket &= 0x3f;
                    inputFile.read((char *) &convertedPacket, 1);
                    
                    //Set the Player color (Not implemented yet :|
                    //covertedPacket = tableof unitColor[ colorbyte+gr_gamenr];
                    int operationCounter = rawPacket;
                    currentUniquePixel.xPosition = currentProcessingRow;
                     do{
                        
                        currentUniquePixel.yPosition = currentProcessingHeight;
                        currentUniquePixel.colorPaletteReference = convertedPacket;
                        targetFrame->frameData.push_back(currentUniquePixel);
                        currentUniquePixel.xPosition++;
                     }while (--operationCounter);

                    currentProcessingRow += rawPacket;
                }
                else
                {
                    //Copy Pixel Operation, and how many pixels to copy directly
                    int operationCounter = rawPacket;
                    do
                    {
                        inputFile.read((char *)&convertedPacket, 1);
                        
                        currentUniquePixel.xPosition = currentProcessingRow;
                        currentUniquePixel.yPosition = currentProcessingHeight;
                        currentUniquePixel.colorPaletteReference = convertedPacket;
                        targetFrame->frameData.push_back(currentUniquePixel);
                        currentProcessingRow++;
                    } while (--operationCounter);
                }
            }
            else
            {
                //Skip the next "rawPacket" # of pixels
                rawPacket &= 0x7f;
                currentProcessingRow += rawPacket;
            }
        }
    }
    
    
    //Finished put the file position back
        inputFile.seekg(currentHeaderFilePosition);
#if VERBOSE >= 5
    std::cout << "Frame data is size: " << targetFrame->frameData.size() << '\n';
    for(std::list<UniquePixel>::iterator it = targetFrame->frameData.begin(); it != targetFrame->frameData.end(); it++)
    {
        std::cout << '(' << it->xPosition << ',' << it->yPosition << ") = " << (int) it->colorPaletteReference << '\n';
    }
#endif
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

#if MAGICKPP_FOUND
void GRPImage::ConvertImage(std::string outFilePath, int startingFrame, int endingFrame, bool singleStitchedImage, int imagesPerRow)
{
    Magick::InitializeMagick(NULL);
    Magick::Image *convertedImage;
    //Due to how Imagemagick creates the image it must be set before usage and must be resized proportionally
    if(singleStitchedImage)
    {
        convertedImage = new Magick::Image(Magick::Geometry((maxImageWidth * imagesPerRow), (maxImageHeight * (ceil( (float)numberOfFrames/imagesPerRow)))), "transparent");
    }
    else
    {
        convertedImage = new Magick::Image(Magick::Geometry(maxImageWidth, maxImageHeight), "transparent");
        //We will erase the image after writing the last processed image to disk
        convertedImage->backgroundColor("transparent");
    }
    colorValues currentPalettePixel;
    std::stringstream fileOutPath;
    Magick::ColorRGB currentMagickPixel;
    currentMagickPixel.alpha(0);
    int currentImageDestinationColumn = 0;
    int currentImageDestinationRow = 0;
    
    
    for(int currentProcessingFrame = startingFrame; currentProcessingFrame < endingFrame; ++currentProcessingFrame)
    {
        GRPFrame *currentFrame = imageFrames.at(currentProcessingFrame);
        
        //If a row in a stitched image is complete, move onto the next row
        if(singleStitchedImage && (currentImageDestinationRow >= imagesPerRow))
        {
            currentImageDestinationColumn++;
            currentImageDestinationRow = 0;
        }
        
        //Start appling the pixels with the refence colorpalettes
        for (std::list<UniquePixel>::iterator currentProcessPixel = currentFrame->frameData.begin(); currentProcessPixel != currentFrame->frameData.end(); currentProcessPixel++)
        {
            currentPalettePixel = currentPalette->GetColorFromPalette(currentProcessPixel->colorPaletteReference);
            
            currentMagickPixel.red(currentPalettePixel.RedElement / 255);
            currentMagickPixel.green(currentPalettePixel.GreenElement / 255);
            currentMagickPixel.blue(currentPalettePixel.BlueElement / 255);

            
           if(singleStitchedImage)
           {
               convertedImage->pixelColor(((currentFrame->xOffset + currentProcessPixel->xPosition) + (maxImageWidth * currentImageDestinationRow)), ((currentFrame->yOffset + currentProcessPixel->yPosition) + (maxImageHeight * currentImageDestinationColumn)), currentMagickPixel);
           }
           else
           {
               convertedImage->pixelColor((currentFrame->xOffset + currentProcessPixel->xPosition), (currentFrame->yOffset + currentProcessPixel->yPosition), currentMagickPixel);
           }

        }
        
        //If not stitched it's time to write the current frame to a file
        if(!singleStitchedImage)
        {
            fileOutPath << std::setw(3) << std::setfill('0') << currentProcessingFrame << outFilePath;
            convertedImage->write(fileOutPath.str());
            fileOutPath.str(std::string());
            convertedImage->erase();
        }
        //Otherwise continue writing down the row
        else
        {
            currentImageDestinationRow++;
        }
        
    }
    //Now that all the pixels are in place, lets write the result to disk
    if(singleStitchedImage)
    {
        convertedImage->write(outFilePath);
    }
    
    
    //Clean up our pointers from earlier.
    delete convertedImage;
    convertedImage = NULL;
    
}
#endif

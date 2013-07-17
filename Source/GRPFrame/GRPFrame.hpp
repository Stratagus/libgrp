#ifndef GRPFrame_Header
#define GRPFrame_Header

#include <vector>
#include "../Exceptions/GRPFrame/GRPFrameException.hpp"

#warning Get a way to query the caller for max width and height

class GRPFrame
{
public:
    GRPFrame();
    ~GRPFrame();
    
    void SetFrameSize(unsigned int inputFrameWidth, unsigned int inputFrameHeight);
    
    std::vector<char> frameData;
    //Tells us where to begin drawing
    uint8_t xPosition;
    uint8_t yPosition;
    
    //The actual width/height of the image in the frame
    uint8_t width;
    uint8_t height;
    
    //Offset of the Framedata (starting at the beginning of the file)
    uint32_t dataOffset;

protected:
    //The actual width and Height of the image (NOT THE FRAME!!!)

private:
};

#endif
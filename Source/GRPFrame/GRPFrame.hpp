#ifndef GRPFrame_Header
#define GRPFrame_Header

#include <list>
#include "../Exceptions/GRPFrame/GRPFrameException.hpp"

//Allow Windows to use 8/16/32 byte values
#if defined(_WIN32)
#include <stdint.h>
    typedef uint8_t u_int8_t;
    typedef uint16_t u_int16_t;
    typedef uint32_t u_int32_t;
#endif

#warning Get a way to query the caller for max width and height

//Used to map what pixels are in a image
//are set to Palette values and location
//Position 0,0 is the upper left corner
struct UniquePixel
{
    int xPosition = 0;
    int yPosition = 0;
    uint8_t colorPaletteReference;
};

class GRPFrame
{
public:
    GRPFrame();
    ~GRPFrame();
    
    void SetFrameSize(uint8_t inputFrameWidth, uint8_t inputFrameHeight);
    
    
    //Tells us where to begin drawing
    uint8_t xPosition;
    uint8_t yPosition;
    
    //The actual width/height of the image in the frame
    uint8_t width;
    uint8_t height;
    
    //Offset of the Framedata (starting at the beginning of the file)
    uint32_t dataOffset;
    
    //The loaded data
    std::list<UniquePixel> frameData;

protected:
    //The actual width and Height of the image (NOT THE FRAME!!!)

private:
};

#endif
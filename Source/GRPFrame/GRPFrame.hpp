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
    std::list<uint8_t> frameData;

protected:
    //The actual width and Height of the image (NOT THE FRAME!!!)

private:
};

#endif
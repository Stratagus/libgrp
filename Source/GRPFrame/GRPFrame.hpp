#ifndef GRPFrame_Header
#define GRPFrame_Header

#include "../Exceptions/GRPFrame/GRPFrameException.hpp"

class GRPFrame
{
public:
    //Frameheader Information
    uint8_t frameLeft; 
    uint8_t frameTop;
    uint8_t frameWidth;
    uint8_t frameHeight;
protected:
private:
};

#endif
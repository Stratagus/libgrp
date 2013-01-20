#ifndef GRPFrame_Header
#define GRPFrame_Header

#include <stdint.h>

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
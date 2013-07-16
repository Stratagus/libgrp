#ifndef GRPFrame_Header
#define GRPFrame_Header

#include <vector>
#include "../Exceptions/GRPFrame/GRPFrameException.hpp"

class GRPFrame
{
public:
    GRPFrame();
    ~GRPFrame();
    //Frameheader Information
    uint8_t frameLeft; 
    uint8_t frameTop;
    uint8_t frameWidth;
    uint8_t frameHeight;
protected:
    std::vector<char> *frameData;
private:
};

#endif
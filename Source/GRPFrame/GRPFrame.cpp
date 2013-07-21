#include "GRPFrame.hpp"
GRPFrame::GRPFrame()
{
}

GRPFrame::~GRPFrame()
{

}

void GRPFrame::SetFrameSize(uint8_t inputFrameWidth, uint8_t inputFrameHeight)
{
    width = inputFrameWidth;
    height = inputFrameHeight;
}

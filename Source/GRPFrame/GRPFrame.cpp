#include "GRPFrame.hpp"
GRPFrame::GRPFrame()
{
    frameData = NULL;
}

GRPFrame::~GRPFrame()
{
    if(frameData != NULL)
    {
        delete frameData;
        frameData = NULL;
    }
}
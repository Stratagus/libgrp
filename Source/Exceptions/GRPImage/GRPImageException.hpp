#ifndef GRPImageException_Header
#define GRPImageException_Header

#include "../GRPException.hpp"
class GRPImageException : public GRPException {};

class GRPImageInvalidFrameNumber : public GRPImageException {};

#endif
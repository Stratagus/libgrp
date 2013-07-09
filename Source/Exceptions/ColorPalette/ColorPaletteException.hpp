#ifndef ColorPaletteException_H
#define ColorPaletteException_H

#include "../GRPException.hpp"
#include <exception>
#include <string>

//!The base exception for which all GrpImage exceptions are based off of
/*!A base exception class
 * \pre NA
 * \post NA
 * \note */

class ColorPaletteException : public GRPException
{
};

class CurruptColorPaletteException : public ColorPaletteException {};
class NoPaletteLoadedException : public ColorPaletteException {};

#endif
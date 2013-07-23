#ifndef ColorPaletteUnitTest_H
#define ColorPaletteUnitTest_H

//Main boost include
#include <boost/test/unit_test.hpp>
#include "../../Source/ColorPalette/ColorPalette.hpp"

#ifdef __APPLE__
#define PALLETTEFILEPATH "../../Documentation/SampleContent/SamplePalette.pal"
#define CURRUPTPALLETTEFILEPATH "../../Documentation/SampleContent/CurruptSamplePalette.pal"

#else

#define PALLETTEFILEPATH "../Documentation/SampleContent/SamplePalette.pal"
#define CURRUPTPALLETTEFILEPATH "../Documentation/SampleContent/CurruptsamplePalette.pal"
#define BADPALLETTEFILEPATH "/lksmdalksmdlkamsda.pal"
#endif

void LoadFileToVector(std::string filePath, std::vector<char> *destinationVector);

#endif
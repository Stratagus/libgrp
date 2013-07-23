#ifndef GRPImageUnitTest_H
#define GRPImageUnitTest_H

//Main boost include
#include <boost/test/unit_test.hpp>
#include "../../Source/GRPImage/GRPImage.hpp"

#ifdef __APPLE__
#define PALETTEFILEPATH "../../Documentation/SampleContent/SamplePalette.pal"
#define GRPIMAGEFILEPATH "../../Documentation/SampleContent/SampleImage.grp"

#else

#define PALETTEFILEPATH "../Documentation/SampleContent/SamplePalette.pal"
#define GRPIMAGEFILEPATH "../../Documentation/SampleContent/SampleImage.grp"
#endif

void LoadFileToVectorImageGRP(std::string filePath, std::vector<char> *destinationVector);

#endif
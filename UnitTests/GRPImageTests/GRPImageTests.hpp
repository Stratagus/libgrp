#ifndef GRPImageUnitTest_H
#define GRPImageUnitTest_H

//Main boost include
#include <boost/test/unit_test.hpp>
#include "../../Source/GRPImage/GRPImage.hpp"

#ifndef QUOTE
	#define Q(x) #x
	#define QUOTE(x) Q(x)
#endif

#ifndef PALETTEFILEPATH
	#define PALETTEFILEPATH QUOTE(SAMPLECONTENTDIR/SamplePalette.pal)
#endif

#ifndef GRPIMAGEFILEPATH
	#define GRPIMAGEFILEPATH QUOTE(SAMPLECONTENTDIR/SampleImage.grp)
#endif

void LoadFileToVectorImageGRP(std::string filePath, std::vector<uint8_t> *destinationVector);

#endif
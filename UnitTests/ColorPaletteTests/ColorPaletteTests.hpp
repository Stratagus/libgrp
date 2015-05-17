#ifndef ColorPaletteUnitTest_H
#define ColorPaletteUnitTest_H

//Main boost include
#include <boost/test/unit_test.hpp>
#include "../../Source/ColorPalette/ColorPalette.hpp"

#ifndef QUOTE
	#define Q(x) #x
	#define QUOTE(x) Q(x)
#endif

#ifndef PALLETTEFILEPATH
	#define PALLETTEFILEPATH  QUOTE(SAMPLECONTENTDIR/SamplePalette.pal)//"../Documentation/SampleContent/SamplePalette.pal"
#endif

#ifndef CURRUPTPALLETTEFILEPATH
	#define CURRUPTPALLETTEFILEPATH QUOTE(SAMPLECONTENTDIR/CurruptSamplePalette.pal) //"../Documentation/SampleContent/CurruptsamplePalette.pal"
#endif

#ifndef BADPALLETTEFILEPATH
	#define BADPALLETTEFILEPATH "/lksmdalksmdlkamsda.pal"
#endif

void LoadFileToVector(std::string filePath, std::vector<uint8_t> *destinationVector);

#endif
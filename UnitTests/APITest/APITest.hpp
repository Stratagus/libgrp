#ifndef PublicAPIUnitTest_H
#define PublicAPIUnitTest_H

//Main boost include
#include <boost/test/unit_test.hpp>

#ifndef QUOTE
	#define Q(x) #x
	#define QUOTE(x) Q(x)
#endif

#ifndef GRPIMAGEFILEPATH
	#define GRPIMAGEFILEPATH QUOTE(SAMPLECONTENTDIR/SampleImage.grp)
#endif

#ifndef BADGRPIMAGEFILEPATH
	#define BADGRPIMAGEFILEPATH "/asdmalskd-sd_--dsdf--w-w-.grp"
#endif

#ifndef PALLETTEFILEPATH
	#define PALLETTEFILEPATH QUOTE(SAMPLECONTENTDIR/SamplePalette.pal)
#endif

#ifndef BADPALLETTEFILEPATH
	#define BADPALLETTEFILEPATH "/lksmdalksmdlkamsda.pal"
#endif

#endif
#ifndef ConvertGRP_H
#define ConvertGRP_H

#include <iostream>
#include "../../Source/libgrp.hpp"

#ifdef __APPLE__
#define PALLETTEFILEPATH "../../Documentation/SampleContent/SamplePalette.pal"
#define GRPIMAGEFILEPATH "../../Documentation/SampleContent/SampleImage.grp"

#else
#define PALLETTEFILEPATH "../Documentation/SampleContent/SamplePalette.pal"
#define GRPIMAGEFILEPATH "../Documentation/SampleContent/SampleImage.grp"
#endif

#endif

#libGRP is a library that allows for the conversion of Blizzard GRP files
#This format is commonly found in Starcraft:Broodwar
#Main Github repository @ https://github.com/ShadowFlare/grpapi
#bradc6 Github repository @ https://github.com/bradc6/grpapi
project(grp)
cmake_minimum_required(VERSION 2.6)

#Set the current version of the library
set(LIBGRP_MAJOR_VERSION 1)
set(LIBGRP_MINOR_VERSION 0)
set(LIBGRP_PATCH_VERSION 0)
#If you want debug information add the flag -DVERBOSE= [1-5]
#1 being basic 5 for everything
IF (NOT DEFINED VERBOSE)
    SET(VERBOSE 0)
ENDIF()
ADD_DEFINITIONS(-DVERBOSE=${VERBOSE})

#Sets the directory for cmake to find Cmake configration packages,
#these packages allow for cmake to find libraries that are not included
#in the standard installation of Cmake. The standard packages can be
#found @ /usr/share/cmake-2.8/Modules
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules
                      ${CMAKE_MODULE_PATH})

#Find optional libraries
find_package(Magick++)

if(Magick++_FOUND)
add_definitions(-DMAGICKPP_FOUND=1)
add_definitions(-DMAGICKCORE_HDRI_ENABLE=0)
add_definitions(-DMAGICKCORE_QUANTUM_DEPTH=16)
endif()

#Source directory variables
#These allow for folders in the source and unittesting to be moved
#without having to manually change each individual filepath, they
#also act as shortcuts.
set (SOURCE_DIR "./Source")
set (SAMPLESOURCE_DIR "./SampleSource")
set (UNITTEST_DIR "./UnitTests")


set(LIBGRP_SOURCE
	${SOURCE_DIR}/libgrp.hpp
	${SOURCE_DIR}/libgrp.cpp
	${SOURCE_DIR}/Exceptions/GRPException.hpp
	${SOURCE_DIR}/Exceptions/GRPException.cpp

   )
set(GRPIMAGE_SOURCE
	${SOURCE_DIR}/GRPImage/GRPImage.hpp
	${SOURCE_DIR}/GRPImage/GRPImage.cpp
	${SOURCE_DIR}/Exceptions/GRPImage/GRPImageException.hpp
	${SOURCE_DIR}/Exceptions/GRPImage/GRPImageException.cpp
	)

set(GRPFRAME_SOURCE
	${SOURCE_DIR}/GRPFrame/GRPFrame.hpp
	${SOURCE_DIR}/GRPFrame/GRPFrame.cpp
	${SOURCE_DIR}/Exceptions/GRPFrame/GRPFrameException.hpp
	${SOURCE_DIR}/Exceptions/GRPFrame/GRPFrameException.cpp
	)

set(COLORPALETTE_SOURCE
	${SOURCE_DIR}/ColorPalette/ColorPalette.hpp
	${SOURCE_DIR}/ColorPalette/ColorPalette.cpp	
	${SOURCE_DIR}/Exceptions/ColorPalette/ColorPaletteException.hpp
	${SOURCE_DIR}/Exceptions/ColorPalette/ColorPaletteException.cpp
	)
set(LIBGRP_UNITTEST_SOURCE
	${UNITTEST_DIR}/main.hpp
	${UNITTEST_DIR}/main.cpp
	${UNITTEST_DIR}/APITest/APITest.hpp
	${UNITTEST_DIR}/APITest/APITest.cpp
   )

set(COLORPALETTE_UNITTEST_SOURCE
	${UNITTEST_DIR}/ColorPaletteTests/ColorPaletteTests.hpp
	${UNITTEST_DIR}/ColorPaletteTests/ColorPaletteTests.cpp
	)

set(GRPIMAGE_UNITTEST_SOURCE
	${UNITTEST_DIR}/GRPImageTests/GRPImageTests.hpp
	${UNITTEST_DIR}/GRPImageTests/GRPImageTests.cpp
	)

set(GRPFRAME_UNITTEST_SOURCE
	${UNITTEST_DIR}/GRPFrameTests/GRPFrameTests.hpp
	${UNITTEST_DIR}/GRPFrameTests/GRPFrameTests.cpp
	)

set(SAMPLES_SHOWPALETTE_SOURCE
	${SAMPLESOURCE_DIR}/ShowPalette/main.hpp
	${SAMPLESOURCE_DIR}/ShowPalette/main.cpp)

set(SAMPLES_SHOWGRP_SOURCE
	${SAMPLESOURCE_DIR}/ShowGRP/main.hpp
	${SAMPLESOURCE_DIR}/ShowGRP/main.cpp)

set(SAMPLES_CONVERTGRP_SOURCE
	${SAMPLESOURCE_DIR}/ConvertGRP/main.hpp
	${SAMPLESOURCE_DIR}/ConvertGRP/main.cpp)

#Code groupings allow for IDEs to put files into collections
#instead of simply throwing all files into a pile. This should
#allow for easy navigation through the code base for novice and
#heavy contributors.
source_group(Main FILES ${LIBGRP_SOURCE})
source_group(ColorPalette FILES ${COLORPALETTE_SOURCE})
source_group(GRPImage FILES ${GRPIMAGE_SOURCE})
source_group(GRPFrame FILES ${GRPFRAME_SOURCE})

source_group(MainTests FILES ${LIBGRP_UNITTEST_SOURCE})
source_group(ColorPaletteTests FILES ${COLORPALETTE_UNITTEST_SOURCE})
source_group(GRPImageTests FILES ${GRPIMAGE_UNITTEST_SOURCE})
source_group(GRPFrameTests FILES ${GRPFRAME_UNITTEST_SOURCE})

#Code groupings allow for IDEs to put files into collections
#instead of simply throwing all files into a pile. This should
#allow for easy navigation through the code base for novice and
#heavy contributors.
#source_group(libgrp FILES ${LIBGRP_SOURCE})
#source_group(UnitTests FILES ${LIBGRP_UNITTEST_SOURCE})

#Set of included libraries if the user does not have
#a packaged version installed via DEB/RPM/Macports
set (LIBRARIES_DIR "./Libraries")

add_library(grp SHARED ${LIBGRP_SOURCE} ${GRPIMAGE_SOURCE} ${COLORPALETTE_SOURCE} ${GRPFRAME_SOURCE})
target_link_libraries(grp ${Magick++_LIBRARIES})

include_directories("/usr/include/ImageMagick")
include_directories("/usr/local/include/ImageMagick")
include_directories("/usr/local/include/")

link_directories("/usr/local/lib")

if(APPLE)

option(MAKEFRAMEWORK "Create FRAMEWORK" OFF)
option(OSXUNIVERSAL "Universal Build" OFF)

#Check MacPorts include/lib folders
include_directories("/opt/local/include")
include_directories("/opt/local/include/ImageMagick")
include_directories("/opt/local/include/ImageMagick-6")

link_directories("/opt/local/lib")

if(OSXUNIVERSAL)
	set(CMAKE_OSX_ARCHITECTURES ppc;i386;ppc64;x86_64) 
endif()

if(MAKEFRAMEWORK)
    set_target_properties(grp PROPERTIES FRAMEWORK true)
    set_target_properties(grp PROPERTIES PUBLIC_HEADER "Source/libgrp.h")
endif()
    set_target_properties(grp PROPERTIES LINK_FLAGS "-framework Carbon")
endif()

if(UNIX)
    set_target_properties(grp PROPERTIES VERSION ${LIBGRP_MAJOR_VERSION}.${LIBGRP_MINOR_VERSION}.${LIBGRP_PATCH_VERSION})
    set_target_properties(grp PROPERTIES SOVERSION ${LIBGRP_MAJOR_VERSION}.${LIBGRP_MINOR_VERSION}.${LIBGRP_PATCH_VERSION})
endif()

if(WIN32)
    set_target_properties(grp PROPERTIES OUTPUT_NAME grp)
endif()

#Unittest configuration settings
option(UNITTESTS "Compile Unittests" OFF)
if(UNITTESTS)
	#Search for the required libraries for the project to properly
	#link and compile.
	find_package(Boost REQUIRED COMPONENTS system date_time unit_test_framework)

	add_executable(libgrpUnitTests ${LIBGRP_UNITTEST_SOURCE} ${COLORPALETTE_UNITTEST_SOURCE} ${GRPFRAME_UNITTEST_SOURCE} ${GRPIMAGE_UNITTEST_SOURCE})
	target_link_libraries(libgrpUnitTests grp ${Boost_LIBRARIES})
endif()

option(SAMPLECODE "Compile SampleCode" OFF)
if(SAMPLECODE)
	find_package(SDL REQUIRED)

	#Example showing only the current application colors
	add_executable(ShowPalette ${SAMPLES_SHOWPALETTE_SOURCE})
	target_link_libraries(ShowPalette grp ${SDL_LIBRARY})

	#Example showing a GRP Image
	add_executable(ShowGRP ${SAMPLES_SHOWGRP_SOURCE})
	target_link_libraries(ShowGRP grp ${SDL_LIBRARY})
if(Magick++_FOUND)
	add_executable(ConvertGRP ${SAMPLES_CONVERTGRP_SOURCE})
	target_link_libraries(ConvertGRP grp)
endif()
endif()

# Write pkgconfig-file:
include(cmake/InstallPkgConfigFile.cmake)
install_pkg_config_file(libgrp
	DESCRIPTION "A library to convert Blizzard GRP images to common image formats"
    CFLAGS
    LIBS ${Magick++_LIBRARIES}
    REQUIRES
    VERSION ${LIBGRP_MAJOR_VERSION}.${LIBGRP_MINOR_VERSION}.${LIBGRP_PATCH_VERSION})

# uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/CMakeUninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

install(DIRECTORY Source/ DESTINATION include/libgrp
          FILES_MATCHING PATTERN "*.hpp")
install(TARGETS grp LIBRARY DESTINATION lib ARCHIVE DESTINATION lib FRAMEWORK DESTINATION /Library/Frameworks)

#Tell the developer the current build options
message("\n\nlibgrp Compile Options\n Unit Tests: ${UNITTESTS} [-DUNITESTS=(off-on)]")
message(" Verbose Level: ${VERBOSE} [-DVERBOSE=[(1-5)] 1-Min 5-Max")
if(APPLE)
message(" Compile Framework: ${MAKEFRAMEWORK} [-DMAKEFRAMEWORK=(off-on)")
endif()
message(" Sample Code: ${SAMPLECODE} [-DSAMPLECODE=(off-on)\n")
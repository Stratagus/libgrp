#libGRP is a library that allows for the conversion of Blizzard GRP files
#This format is commonly found in Starcraft:Broodwar
#Main Github repository @ https://github.com/ShadowFlare/grpapi
#bradc6 Github repository @ https://github.com/bradc6/grpapi
project(libgrp)
cmake_minimum_required(VERSION 2.6)

#Set the current version of the library
set(LIBGRP_VERSION 0.0.1)

#Sets the directory for cmake to find Cmake configration packages,
#these packages allow for cmake to find libraries that are not included
#in the standard installation of Cmake. The standard packages can be
#found @ /usr/share/cmake-2.8/Modules
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules
                      ${CMAKE_MODULE_PATH})


#Source directory variables
#These allow for folders in the source and unittesting to be moved
#without having to manually change each individual filepath, they
#also act as shortcuts.
set (SOURCE_DIR "./Source")
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
	${SOURCE_DIR}/GRPImage/GRPImageException.hpp
	${SOURCE_DIR}/GRPImage/GRPImageException.cpp
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

add_library(libgrp SHARED ${LIBGRP_SOURCE} ${GRPIMAGE_SOURCE} ${COLORPALETTE_SOURCE} ${GRPFRAME_SOURCE})

if(APPLE)
	#Check MacPorts include/lib folders
    include_directories("/opt/local/include")
    link_directories("/opt/local/lib")

    set_target_properties(libgrp PROPERTIES FRAMEWORK true)
    set_target_properties(libgrp PROPERTIES PUBLIC_HEADER "Source/libgrp.hpp")
    set_target_properties(libgrp PROPERTIES LINK_FLAGS "-framework Carbon")
endif()

	#Temporary Includes
    include_directories("~/dev/fakeroot/include")
    link_directories("~/dev/fakeroot/lib")

if(UNIX)
    set_target_properties(libgrp PROPERTIES VERSION ${LIBGRP_VERSION})
    set_target_properties(libgrp PROPERTIES SOVERSION ${LIBGRP_VERSION})
endif()

if(WIN32)
    set_target_properties(libgrp PROPERTIES OUTPUT_NAME libgrp)
endif()

install(TARGETS libgrp RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib FRAMEWORK DESTINATION /Library/Frameworks)
install(FILES Source/libgrp.hpp DESTINATION include)

#Unittest configuration settings
option(UNITTESTS "Compile Unittests" OFF)
if(UNITTESTS)
	#Search for the required libraries for the project to properly
	#link and compile.
	find_package(Boost REQUIRED COMPONENTS system date_time unit_test_framework)

	add_executable(libgrpUnitTests ${LIBGRP_UNITTEST_SOURCE} ${COLORPALETTE_UNITTEST_SOURCE} ${GRPFRAME_UNITTEST_SOURCE} ${GRPIMAGE_UNITTEST_SOURCE})
	target_link_libraries(libgrpUnitTests libgrp ${Boost_LIBRARIES})
endif()

#Tell the developer the current build options
message("\n\nlibgrp Compile Options\n Unit Tests: ${UNITTESTS} [-DUNITESTS=${UNITTESTS}] \n")

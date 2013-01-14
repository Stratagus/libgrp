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
   )
set(LIBGRP_UNITTEST_SOURCE
	${UNITTEST_DIR}/main.hpp
	${UNITTEST_DIR}/main.cpp
   )

#Set of included libraries if the user does not have
#a packaged version installed via DEB/RPM/Macports
set (LIBRARIES_DIR "./Libraries")

add_library(libgrp SHARED ${LIBGRP_SOURCE})

if(APPLE)
	#Check MacPorts include/lib folders
    include_directories("/opt/local/include")
    link_directories("/opt/local/lib")

    set_target_properties(libgrp PROPERTIES FRAMEWORK true)
    set_target_properties(libgrp PROPERTIES PUBLIC_HEADER "Source/libgrp.hpp")
    set_target_properties(libgrp PROPERTIES LINK_FLAGS "-framework Carbon")
endif()

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
	find_package(CPPUnit)

	add_executable(libgrpUnitTests ${LIBGRP_UNITTEST_SOURCE})
	target_link_libraries(libgrpUnitTests libgrp ${CPPUNIT_LIBRARY})
endif()

#Tell the developer the current build options
message("\n\nlibgrp Compile Options\n Unit Tests: ${UNITTESTS} [-DUNITESTS=${UNITTESTS}] \n")
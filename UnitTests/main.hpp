/*!
 *  \brief     Unit Test Runner
 *  \details   The main testrunner for libgrp,
 *              tests for the different classes are written in there
 *              label of <classname>Test.h with the same file structure
 *              as those in the Source/ directory.
 *  \author    Bradley Clemetson
 *  \version   0.0.1
 *  \date      2012 - Present
 */
#ifndef libgrpTestMain_H
#define libgrpTestMain_H

//Main boost include
#include <boost/test/unit_test.hpp>

//Test the following classes
#include "APITest/APITest.hpp"
#include "ColorPaletteTests/ColorPaletteTests.hpp"
#include "GRPFrameTests/GRPFrameTests.hpp"
#include "GRPImageTests/GRPImageTests.hpp"

#endif
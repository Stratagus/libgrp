#include "APITest.hpp"

#include "../../Source/libgrp.hpp"

APITests::APITests() : CppUnit::TestCase("Sample UnitTest")
{
}

#warning Needs to be improved to tell what kind of error
void APITests::TestNoFileOnOpenPalette()
{
    GRPImage *testImage = new GRPImage();
    try
    {
        testImage->LoadPalette("/bad/file/path.wbe");
        CPPUNIT_ASSERT(false);
    }
    catch (...)
    {
        CPPUNIT_ASSERT(true);
    }
    
    delete testImage;
    testImage = NULL;
}

#warning Needs to be improved to tell what kind of error
void APITests::TestNoFileOnOpenImage()
{
    GRPImage *testImage = new GRPImage();
    try
    {
        testImage->LoadImage("/bad/file/path.wbe");
        CPPUNIT_ASSERT(false);
    }
    catch (...)
    {
        CPPUNIT_ASSERT(true);
    }
    
    delete testImage;
    testImage = NULL;
}

void APITests::general()
{
    GRPImage *myImage = new GRPImage;

    myImage->LoadImage("./zergling.grp");
    myImage->LoadPalette("./platform.wpe");
    std::cout << "Loaded image from file\n";
    std::cout << "GRPImage Specs -Frames: " << myImage->getNumberOfFrames()
              << " -MaxWidth of: " << myImage->getMaxWidth() << " -MaxHeight of: " << myImage->getMaxHeight() << '\n';
    
    
    CPPUNIT_ASSERT(true);
}

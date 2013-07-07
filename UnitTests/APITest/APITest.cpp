#include "APITest.hpp"

#include "../../Source/libgrp.hpp"

BOOST_AUTO_TEST_SUITE(PublicAPITests)

#warning Needs to be improved to tell what kind of error (Not Implemented
/*BOOST_AUTO_TEST_CASE(BadFilePathonOpenPallete)
{
    GRPImage *testImage = new GRPImage();
    try
    {
       // testImage->LoadPalette("/bad/file/path.wbe");
        BOOST_ASSERT(false);
    }
    catch (...)
    {
        BOOST_ASSERT(true);
    }
    
    delete testImage;
    testImage = NULL;
}*/

#warning Needs to be improved to tell what kind of error
BOOST_AUTO_TEST_CASE(BadFilePathonOpenImage)
{
    GRPImage *testImage = new GRPImage();
    try
    {
        testImage->LoadImage("/bad/file/path.wbe");
        BOOST_ASSERT(false);
    }
    catch (...)
    {
        BOOST_ASSERT(true);
    }
    
    delete testImage;
    testImage = NULL;
}

BOOST_AUTO_TEST_CASE(QueryGRPImage)
{
    GRPImage sampleImage;
    sampleImage.LoadImage(GRPIMAGEFILEPATH);
    BOOST_ASSERT((sampleImage.getNumberOfFrames() == 296) && (sampleImage.getMaxHeight() == 128) && (sampleImage.getMaxWidth() == 128));
}
BOOST_AUTO_TEST_CASE(Current)
{
    GRPImage *myImage = new GRPImage;

    
    myImage->LoadImage(GRPIMAGEFILEPATH);
    //myImage->LoadPalette(PALLETTEFILEPATH);
    std::cout << "Loaded image from file\n";
    std::cout << "GRPImage Specs -Frames: " << myImage->getNumberOfFrames()
              << " -MaxWidth of: " << myImage->getMaxWidth() << " -MaxHeight of: " << myImage->getMaxHeight() << '\n';
    myImage->DecodeFrame(3);
    
    BOOST_ASSERT(true);
}
BOOST_AUTO_TEST_SUITE_END()
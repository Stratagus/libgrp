#ifndef GlyObjectTest_H
#define GlyObjectTest_H


#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestCaller.h>

class APITests : public CppUnit::TestCase
{
public:
    APITests();

    void general();
    
    void TestNoFileOnOpenPalette();
    void TestNoFileOnOpenImage();
    
    
    static CppUnit::Test *suite()
    {
        CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("libgrp API unit tests");
        suiteOfTests->addTest(new CppUnit::TestCaller<APITests>("No File on LoadPalette",   &APITests::general));
        //suiteOfTests->addTest(new CppUnit::TestCaller<APITests>("No File on LoadPalette",   &APITests::TestNoFileOnOpenPalette));
        //suiteOfTests->addTest(new CppUnit::TestCaller<APITests>("No File on LoadPalette",   &APITests::TestNoFileOnOpenImage));
        return suiteOfTests;
    }
};
#endif
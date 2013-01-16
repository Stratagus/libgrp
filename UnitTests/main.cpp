#include "main.hpp"
#include <iostream>

//Test the following classes
#include "APITest/APITest.hpp"

int main()
{
    std::cout << "libGRP UnitTests\n";
    
    CppUnit::TextUi::TestRunner testRunner;
    
    //Add tests to run
    //Example testRunner.addTest(<TestClassName>::suit());
    testRunner.addTest(APITests::suite());
    
    
    testRunner.run();
    return 0;
}
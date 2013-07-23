libgrp
======

A simple library to convert Blizzard GRP images to common image formats.
 
libgrp Motivation
================
1. Extensive Documentation
2. Cross Platform (Windows, Mac OSX, Linux)
3. C++ (Use of OOP Techniques)

While some libraries may offer 1 or 2 of these
aspects, none were are to fulfill all of the requirments. This is
not to imply that the implementation of any of these libraries were
incorrect (in fact many techniques are pulled from them); the goal
was to make the expirence easier to maintain and utilize in other applications.

GRP Format Motivation
=====================
It was necessary to minimize memory use because we endeavored to make Blizzard games
playable on low-spec systems. Consequently the GRP format needed to be highly compressed 
to maximize the number of frames we could fit in memory. - Patrick Wyatt 

CMake Build Options
===================
There are three parameters that can be modified.
1. VERBOSE - The amount of information outputted to the console
 while processing GRP files and ColorPalettes.
 DEFAULT = 0 Range = [1 - 5]
 To set add the cmake flag "-DVERBOSE=[DesiredValue]"
2. UNITTESTS - Compile the Boost Unit tests inluded with libgrp.
 This will require that the Boost Library with the Unit Test Framework Module
 be compiled and installed. To enable unit tests
 Add the cmake flag "-DUNITTESTS=on"
3. SAMPLECODE - To compile the sample code.
 Add the cmake flag "-DSAMPLECODE=on"
 
Sample Code
===========
Sample code can be found from the root directory folder
"SampleSource/"

Credits
=======
1. Bradley Clemetson
 @ http://codeprogrammers.net


Special Thanks
==============
1. grplib Developers (botik32, infbonzay)
 @ http://sourceforge.net/projects/grplib/
2. grpapi Developer (ShadowFlare)
 @ http://sfsrealm.hopto.org/
3. Author of the GRP Format (Patrick Wyatt)
 @ http://www.codeofhonor.com/blog/
#include "ColorPalette.hpp"

ColorPalette::ColorPalette()
{
#if VERBOSE >= 5
    std::cout << "Constructing ColorPalette Object.\n";
#endif
    transparentColorsTable = NULL;
    greyscaleTable = NULL;
    shadowTable = NULL;
    formattedPaletteData = NULL;
    lightTable = NULL;
    redTable = NULL;
    greenTable = NULL;
    blueTable =NULL;
}

ColorPalette::~ColorPalette()
{
    if(formattedPaletteData != NULL)
    {
        #if VERBOSE >= 5
            std::cout << "Deallocating formattedPalleteData.\n";
        #endif
        delete formattedPaletteData;
        formattedPaletteData = NULL;
    }
    if(transparentColorsTable != NULL)
    {
        #if VERBOSE >= 5
            std::cout << "Deallocating transparentColorsTable.\n";
        #endif
        delete transparentColorsTable;
        transparentColorsTable = NULL;
    }
    if(greyscaleTable != NULL)
    {
        #if VERBOSE >= 5
            std::cout << "Deallocating greyscaleTable.\n";
        #endif
        delete greyscaleTable;
        greyscaleTable = NULL;
    }
    if(shadowTable != NULL)
    {
        #if VERBOSE >= 5
            std::cout << "Deallocating shadowTable.\n";
        #endif
        delete shadowTable;
        shadowTable = NULL;
    }
    if(lightTable != NULL)
    {
        #if VERBOSE >= 5
            std::cout << "Deallocating lightTable.\n";
        #endif
        delete lightTable;
        lightTable = NULL;
    }
    if(redTable != NULL)
    {
        #if VERBOSE >= 5
            std::cout << "Deallocating redTable.\n";
        #endif
        delete redTable;
        redTable = NULL;
    }
    if(greenTable != NULL)
    {
        #if VERBOSE >= 5
            std::cout << "Deallocating greenTable.\n";
        #endif
        delete greenTable;
        greenTable = NULL;
    }
    if(blueTable != NULL)
    {
        #if VERBOSE >= 5
            std::cout << "Deallocating blueTable.\n";
        #endif
        delete blueTable;
        blueTable = NULL;
    }
}

void ColorPalette::LoadPalette(std::vector<char> *inputPalette)
{
    colorValues currentColorProcessing;
    if( (inputPalette != NULL) && ((inputPalette->size() != 768) && (inputPalette->size() != 1024)))
    {
        CurruptColorPaletteException curruptPalette;
        curruptPalette.SetErrorMessage("Invalid or Currupt Color Palette; expecting 768 or 1024.");
        throw(curruptPalette);
    }
    
    //Start loading the Palette into the formattedPaletteData Vector.
    for(int loadCurrentColor = 0; loadCurrentColor < (inputPalette->size() / 3); loadCurrentColor++)
    {
        currentColorProcessing.RedElement = inputPalette->at((3 * loadCurrentColor));
        currentColorProcessing.GreenElement = inputPalette->at((3 * loadCurrentColor) + 1);
        currentColorProcessing.BlueElement = inputPalette->at((3 * loadCurrentColor) + 2);
        
        formattedPaletteData->at(loadCurrentColor) = currentColorProcessing;
    }
    
#if DUMPPALETTEDATA
    std::ofstream outputPalleteData("ColorPalette.dat");
    colorValues currentWriteColor;
    for(int currentColor = 0; currentColor < formattedPaletteData->size(); currentColor++)
    {
        currentWriteColor = formattedPaletteData->at(currentColor);
        
        outputPalleteData.put(currentWriteColor.RedElement);
        outputPalleteData.put(currentWriteColor.GreenElement);
        outputPalleteData.put(currentWriteColor.BlueElement);
    }
    outputPalleteData.close();
#endif
}

void ColorPalette::LoadPalette(std::string filePath)
{
#if VERBOSE >= 2
    std::cout << "Loading Palette from file: " << filePath << '\n';
#endif
    
    int inputFileSize;
    colorValues currentColorProcessing;
    

    
    std::ifstream inputFile(filePath.c_str(), std::ios::binary);
    inputFile.exceptions(std::ifstream::badbit | std::ifstream::failbit | std::ifstream::eofbit);
    
    //Find the file size as to allow for checking if the file
    //is a valid GRP Palette.
    inputFile.seekg (0, std::ios::end);
    inputFileSize = inputFile.tellg();
    inputFile.seekg (0, std::ios::beg);
    
    //Check to see if the file size matches a GRP Palette.
    if((inputFileSize != 768) && (inputFileSize != 1024))
    {
        CurruptColorPaletteException curruptPalette;
        curruptPalette.SetErrorMessage("Invalid or Currupt Color Palette; expecting 768 or 1024.");
        throw(curruptPalette);
    }
    
    //Since the file passed the check allocated or resize the vector
    //to the proper size.
    if(formattedPaletteData == NULL)
    {
        #if VERBOSE >= 5
        std::cout << "Initializing formattedPaletteData.\n";
        #endif
        formattedPaletteData = new std::vector<colorValues>;
    }
    formattedPaletteData->resize(inputFileSize / 3);
    
    //Start loading the Palette into the formattedPaletteData Vector.
    for(int loadCurrentColor = 0; loadCurrentColor < (inputFileSize / 3); loadCurrentColor++)
    {
        currentColorProcessing.RedElement = inputFile.get();
        currentColorProcessing.GreenElement = inputFile.get();
        currentColorProcessing.BlueElement = inputFile.get();
        
        formattedPaletteData->at(loadCurrentColor) = currentColorProcessing;
    }
    
#if VERBOSE >= 5
    std::cout << "Loaded contents of Pallete\n";
    
    //Start loading the Palette into the formattedPaletteData Vector.
    for(int loadCurrentColor = 0; loadCurrentColor < (inputFileSize / 3); loadCurrentColor++)
    {
        currentColorProcessing = formattedPaletteData->at(loadCurrentColor);
        std::cout << "Color: " << loadCurrentColor
                  << "  Red: " << currentColorProcessing.RedElement
                  << " Blue: " << currentColorProcessing.BlueElement
                  << " Green: " <<currentColorProcessing.GreenElement << '\n';
    }
#endif
    
#if DUMPPALETTEDATA
    std::ofstream outputPalleteData("ColorPalette.dat");
    colorValues currentWriteColor;
    for(int currentColor = 0; currentColor < formattedPaletteData->size(); currentColor++)
    {
        currentWriteColor = formattedPaletteData->at(currentColor);
        
        outputPalleteData.put(currentWriteColor.RedElement);
        outputPalleteData.put(currentWriteColor.GreenElement);
        outputPalleteData.put(currentWriteColor.BlueElement);
    }
    outputPalleteData.close();
#endif
}

colorValues ColorPalette::GetColorFromPalette(int colorNumber)
{
    if(colorNumber < 0 || colorNumber > formattedPaletteData->size())
    {
        #if VERBOSE >= 1
            std::cout << "Tried to access color " << colorNumber << '\n';
        #endif
        OutofBoundsColorException colorBoundsError;
        colorBoundsError.SetErrorMessage("Attempted color selection of the bounds");
        throw colorBoundsError;
    }
    return formattedPaletteData->at(colorNumber);
}

void ColorPalette::GenerateTransparentColorsTable()
{
    if(formattedPaletteData == NULL)
    {
        NoPaletteLoadedException paletteError;
        paletteError.SetErrorMessage("No Palette file is loaded!!");
        throw paletteError;
    }
    
    if(transparentColorsTable == NULL)
    {
        //Create a vector with the max number of colors
        transparentColorsTable = new std::vector<char>;
    }
    
    transparentColorsTable->resize(MAXIMUMNUMBEROFCOLORSPERPALETTE * MAXIMUMNUMBEROFCOLORSPERPALETTE);
    
    colorValues currentOnLightColor;
    colorValues currentUnderLightColor;
    colorValues currentCombinedLightColor;
    colorValues differenceColor;

    float leastColorDifference,currentColorDifference;
    
    
    int currentSelectedColor, currentSelectedColor2, findcol, bestfit = 0;
    
    for (currentSelectedColor2 = 0; currentSelectedColor2 < MAXIMUMNUMBEROFCOLORSPERPALETTE; currentSelectedColor2++)
    {
        currentUnderLightColor = GetColorFromPalette(currentSelectedColor2);
        currentUnderLightColor.RedElement *= LIGHTLEVELUNDER;
        currentUnderLightColor.GreenElement *= LIGHTLEVELUNDER;
        currentUnderLightColor.BlueElement *= LIGHTLEVELUNDER;
        
        for (currentSelectedColor = 0; currentSelectedColor < MAXIMUMNUMBEROFCOLORSPERPALETTE; currentSelectedColor++)
        {
            currentOnLightColor = GetColorFromPalette(currentSelectedColor);
            currentOnLightColor.RedElement *= LIGHTLEVELON;
            currentOnLightColor.GreenElement *= LIGHTLEVELON;
            currentOnLightColor.BlueElement *= LIGHTLEVELON;
        
            currentCombinedLightColor.RedElement = (long) (currentOnLightColor.RedElement + currentUnderLightColor.RedElement);
            currentCombinedLightColor.GreenElement = (long) (currentOnLightColor.GreenElement + currentUnderLightColor.GreenElement);
            currentCombinedLightColor.BlueElement = (long) (currentOnLightColor.BlueElement + currentUnderLightColor.BlueElement);
            
            //Set the maximum value of a float to avoid false differences
            leastColorDifference = 655350.0;
            
            for  (findcol = 0; findcol < MAXIMUMNUMBEROFCOLORSPERPALETTE; findcol++)
            {
                differenceColor = GetColorFromPalette(findcol);
                differenceColor = GetColorDifference(differenceColor, currentCombinedLightColor);
                differenceColor.RedElement *= 30;
                differenceColor.GreenElement *= 59;
                differenceColor.BlueElement *= 11;
                

                currentColorDifference = sqrt((differenceColor.RedElement * differenceColor.RedElement) +
                              (differenceColor.BlueElement * differenceColor.BlueElement) +
                              (differenceColor.GreenElement * differenceColor.GreenElement));
                
                if  (currentColorDifference < leastColorDifference)//found best equality
                {
                    leastColorDifference = currentColorDifference;
                    bestfit = findcol;
                }
            }
            //Now that we found the best possible color match, save the result in the table.
            transparentColorsTable->at((currentSelectedColor2 * MAXIMUMNUMBEROFCOLORSPERPALETTE + currentSelectedColor)) = bestfit;
        }
    }

#if VERBOSE >= 5
    std::cout << "Generated values of Greyscale Table with size: " << transparentColorsTable->size() << '\n';
    
    //Start loading the Palette into the formattedPaletteData Vector.
    for(int loadCurrentColor = 0; loadCurrentColor < transparentColorsTable->size(); loadCurrentColor++)
    {
        //std::cout << "Color: " << loadCurrentColor
        //<< "  Red: " << currentColorProcessing.RedElement
        //<< " Blue: " << currentColorProcessing.BlueElement
        //<< " Green: " <<currentColorProcessing.GreenElement << '\n';
        std::cout << (int) transparentColorsTable->at(loadCurrentColor) << '\n';
    }
#endif
    
#if DUMPTRANSPARENTTABLE
    std::ofstream outputTransparentTable("TransparentTable.dat");
    for(int currentColor = 0; currentColor < transparentColorsTable->size(); currentColor++)
    {
        outputTransparentTable.put(transparentColorsTable->at(currentColor));
    }
    outputTransparentTable.close();
#endif
}

void ColorPalette::GenerateGreyscaleTable()
{
    if(formattedPaletteData == NULL)
    {
        NoPaletteLoadedException paletteError;
        paletteError.SetErrorMessage("No Palette file is loaded!!");
        throw paletteError;
    }
    
    if(greyscaleTable == NULL)
    {
        //Create a vector with the max number of colors
        greyscaleTable = new std::vector<char>;
    }
    
    greyscaleTable->resize(MAXIMUMNUMBEROFCOLORSPERPALETTE);
    
    colorValues currentColor, findColor;
    float lowest, colorDifference;
    int currentColorIndex,findcol,bestfit=0;
    
    int maxpalettecolor=256;
    for (currentColorIndex = 0; currentColorIndex < maxpalettecolor; currentColorIndex++)
    {
        currentColor = GetColorFromPalette(currentColorIndex);
        currentColor.RedElement *= 30;
        currentColor.BlueElement *= 59;
        currentColor.GreenElement *= 11;
        
        //Don't think this does anything : \
        //c1 = (currentColor.RedElement + currentColor.BlueElement + currentColor.GreenElement) / 100;
        
        currentColor.RedElement = (int) currentColor.RedElement;
        currentColor.BlueElement = (int) currentColor.BlueElement;
        currentColor.GreenElement = (int) currentColor.GreenElement;
        
        //Max value of an float
        //lowest = 655350.0;
        lowest = std::numeric_limits<float>::max();
        for  (findcol = 0; findcol < maxpalettecolor; findcol++)
        {
            findColor = GetColorFromPalette(findcol);
            findColor = GetColorDifference(findColor, currentColor);
            findColor.RedElement *= 30;
            findColor.BlueElement *= 11;
            findColor.GreenElement *= 59;
            
    	    colorDifference = sqrt((findColor.RedElement * findColor.RedElement) +
                          (findColor.BlueElement * findColor.BlueElement) +
                          (findColor.GreenElement * findColor.GreenElement));
    	    if  (colorDifference < lowest)
    	    {
                lowest = colorDifference;
                bestfit = findcol;
    	    }
        }
        greyscaleTable->at(currentColorIndex) = bestfit;
    }
#if DUMPGREYSCALETABLE
    std::ofstream outputGreyscaleTable("tomono.grd");
    for(int currentColor = 0; currentColor < greyscaleTable->size(); currentColor++)
    {
        outputGreyscaleTable.put(greyscaleTable->at(currentColor));
    }
    outputGreyscaleTable.close();
#endif
}


std::vector<colorValues> ColorPalette::GenerateGlowColors(unsigned int maxGradation, colorValues initialColor, colorValues finalColor)
{
    #if VERBOSE >= 2
        std::cout << "GlowColors-Creating vector of size: " << maxGradation << '\n';
    #endif
    
    
    std::vector<colorValues> finalGlowColors;
    finalGlowColors.resize(maxGradation + 1);
    
    colorValues trColor, currentProcessColor;
    
    int i = 0;
    
    float mgr3 = maxGradation/3;
	float mgr31 = mgr3*1.67;
    for(; i < mgr3; i++)
    {
        currentProcessColor.RedElement = (initialColor.RedElement * (i/mgr31 + 0.4));
        currentProcessColor.GreenElement = (initialColor.GreenElement * (i/mgr31 + 0.4));
        currentProcessColor.BlueElement = (initialColor.BlueElement * (i/mgr31 + 0.4));
        finalGlowColors.at(i) = currentProcessColor;
    }
    
    float mgr23 = mgr3 * 2;
    trColor.RedElement = finalColor.RedElement - initialColor.RedElement;
    trColor.GreenElement = finalColor.GreenElement - initialColor.GreenElement;
    trColor.BlueElement = finalColor.BlueElement - initialColor.BlueElement;
    
    for(; i < maxGradation; i++)
    {
        float togo = (i-mgr3)/mgr23;
        currentProcessColor.RedElement = (initialColor.RedElement + trColor.RedElement * togo);
        currentProcessColor.GreenElement = (initialColor.GreenElement + trColor.GreenElement * togo);
        currentProcessColor.BlueElement = (initialColor.BlueElement + trColor.BlueElement * togo);
        finalGlowColors.at(i) = currentProcessColor;
    }
    
    if(finalColor.RedElement && finalColor.GreenElement && finalColor.BlueElement)
    {
        currentProcessColor.RedElement = 255;
        currentProcessColor.GreenElement = 255;
        currentProcessColor.BlueElement = 255;
        
        finalGlowColors.at(i) = currentProcessColor;
    }
    else
    {
        currentProcessColor.RedElement = 0;
        currentProcessColor.GreenElement = 0;
        currentProcessColor.BlueElement = 0;
        
        finalGlowColors.at(i) = currentProcessColor;
    }
    
#if DUMPGLOWTABLE 
    std::ofstream outGlowTable("GlowTable.dat");
    for(int currentColor = 0; currentColor < finalGlowColors.size(); currentColor++)
    {
        currentProcessColor = finalGlowColors.at(currentColor);
        outGlowTable.put(currentProcessColor.RedElement);
        outGlowTable.put(currentProcessColor.GreenElement);
        outGlowTable.put(currentProcessColor.BlueElement);
        
    }
    outGlowTable.close();
#endif
    return finalGlowColors;
}
std::vector<char> *ColorPalette::GenerateColorizedTable(int maxGradation, colorValues startingGlowColor, colorValues endingGlowColor)
{
    if(maxGradation > MAXIMUMNUMBEROFCOLORSPERPALETTE || maxGradation < 0)
    {
        InvalidGradationValueException gradationError;
        gradationError.SetErrorMessage("Invalid maxGradation size");
        throw gradationError;
    }
    
    std::vector<char> *finalColorizedTable = new std::vector<char>;
    finalColorizedTable->resize(MAXIMUMNUMBEROFCOLORSPERPALETTE * maxGradation);
    
    colorValues firstColor, secondColor, differenceColor;
    float lowest, totalColorDifference;
    int currentBestFit = -1, currentColor, currentGradation, findColor;
    std::vector<colorValues> glowColors = GenerateGlowColors(maxGradation, startingGlowColor, endingGlowColor);
    
    for(currentColor = 0; currentColor < maxGradation; currentColor++)
    {
        for(currentGradation = 0; currentGradation < maxGradation; currentGradation++)
        {
            firstColor = GetColorFromPalette(currentColor);
            firstColor.RedElement = glowColors.at(currentGradation).RedElement * (currentGradation + 1);
            firstColor.GreenElement = glowColors.at(currentGradation).GreenElement * (currentGradation + 1);
            firstColor.BlueElement = glowColors.at(currentGradation).BlueElement * (currentGradation + 1);
            
            firstColor.RedElement /= maxGradation;
            firstColor.GreenElement /= maxGradation;
            firstColor.BlueElement /= maxGradation;
            
            lowest = 655350.0;
            for (findColor = 0; findColor < MAXIMUMNUMBEROFCOLORSPERPALETTE; findColor++)
            {
                secondColor = GetColorFromPalette(findColor);
                differenceColor = GetColorDifference(secondColor, firstColor);
                differenceColor.RedElement *= 33;
                differenceColor.GreenElement *= 33;
                differenceColor.BlueElement *= 33;
                
                totalColorDifference = sqrt( (differenceColor.RedElement * differenceColor.RedElement) +
                                             (differenceColor.GreenElement * differenceColor.GreenElement) +
                                            (differenceColor.BlueElement * differenceColor.BlueElement));
                
                if(totalColorDifference < lowest)
                {
                    lowest = totalColorDifference;
                    currentBestFit = findColor;
                }
            }
            finalColorizedTable->at(MAXIMUMNUMBEROFCOLORSPERPALETTE * currentGradation + currentColor) = currentBestFit;
        }
    }
    return finalColorizedTable;
}

std::vector<colorValues> ColorPalette::GenerateTableWithConstraints(colorValues baseColor, float addGradation)
{
    std::vector<colorValues> finalConstrainedColorTable;
    finalConstrainedColorTable.resize(MAXIMUMNUMBEROFCOLORSPERPALETTE);
    
    colorValues firstColor, secondColor, cachedColor, differenceColor;
    
    
    int bestFittingColor = -1;
    float lowest, finalColorDifference;
    
    for (int currentColor = 0; currentColor < MAXIMUMNUMBEROFCOLORSPERPALETTE; currentColor ++)
    {
        cachedColor = GetColorFromPalette(currentColor);
        
#warning Assuming (int) type cast on red element
        firstColor.RedElement = (float) cachedColor.RedElement * baseColor.RedElement * (int)(addGradation / 100);
        if(firstColor.RedElement > 255)
        {
            firstColor.RedElement = 255;
        }
        
        firstColor.GreenElement = (float) cachedColor.GreenElement * baseColor.GreenElement * (int) (addGradation / 100);
        if(firstColor.GreenElement > 255)
        {
            firstColor.GreenElement = 255;
        }
        
        firstColor.BlueElement = (float) cachedColor.BlueElement * baseColor.BlueElement * (int) (addGradation / 100);
        if(firstColor.BlueElement > 255)
        {
            firstColor.BlueElement = 255;
        }
        
        lowest = 655350;
        
        for(int findColor = 0; findColor < MAXIMUMNUMBEROFCOLORSPERPALETTE; findColor++)
        {
            secondColor = GetColorFromPalette(findColor);
            differenceColor = GetColorDifference(secondColor, firstColor);
            differenceColor.RedElement *= baseColor.RedElement;
            differenceColor.GreenElement *= baseColor.GreenElement;
            differenceColor.BlueElement *= baseColor.BlueElement;
            
            finalColorDifference = sqrtf((differenceColor.RedElement * differenceColor.RedElement) +
                                         (differenceColor.GreenElement * differenceColor.GreenElement) +
                                         (differenceColor.BlueElement * differenceColor.BlueElement));
            if(finalColorDifference < lowest)
            {
                lowest = finalColorDifference;
                bestFittingColor = findColor;
            }
        }
        finalConstrainedColorTable.at(currentColor) = GetColorFromPalette(bestFittingColor);
    }
    return finalConstrainedColorTable;
}

colorValues ColorPalette::GetColorDifference(colorValues initialColor, colorValues operationColor)
{
    colorValues difference;
    difference.RedElement = initialColor.RedElement - operationColor.RedElement;
    difference.GreenElement = initialColor.GreenElement - operationColor.GreenElement;
    difference.BlueElement = initialColor.BlueElement - operationColor.BlueElement;
    
    return difference;
}

void ColorPalette::GenerateShadowtable()
{
    colorValues blackColor;
    blackColor.RedElement = 0;
    blackColor.GreenElement = 0;
    blackColor.BlueElement = 0;
    
    if(shadowTable != NULL);
    {
        delete shadowTable;
        shadowTable = NULL;
    }
    
    shadowTable = GenerateColorizedTable(32, blackColor, blackColor);
#if DUMPSHADOWTABLE
    std::ofstream outputShadowTable("toblack.grd");
    for(int currentColor = 0; currentColor < shadowTable->size(); currentColor++)
    {
        outputShadowTable.put(shadowTable->at(currentColor));
    }
    outputShadowTable.close();
#endif
}

void ColorPalette::GenerateLighttable()
{
    colorValues whiteColor;
    whiteColor.RedElement = 240;
    whiteColor.GreenElement = 240;
    whiteColor.BlueElement = 240;
    
    if(lightTable != NULL)
    {
        delete lightTable;
        lightTable = NULL;
    }
    lightTable = GenerateColorizedTable(32, whiteColor, whiteColor);
#if DUMPLIGHTTABLE
    std::ofstream outputLightTable("towhite.grd");
    for(int currentColor = 0; currentColor < lightTable->size(); currentColor++)
    {
        outputLightTable.put(lightTable->at(currentColor));
    }
    outputLightTable.close();
#endif
}
void ColorPalette::GenerateRedtable()
{
    colorValues redColor;
    redColor.RedElement = 120;
    redColor.GreenElement = 0;
    redColor.BlueElement = 0;
    
    colorValues lightRedColor;
    lightRedColor.RedElement = 224;
    lightRedColor.GreenElement = 228;
    lightRedColor.BlueElement = 144;
    
    if(redTable != NULL)
    {
        delete redTable;
        redTable = NULL;
    }
    redTable = GenerateColorizedTable(32, redColor, lightRedColor);
    
#if DUMPREDTABLE
    std::ofstream outputRedTable("tored.grd");
    for(int currentColor = 0; currentColor < redTable->size(); currentColor++)
    {
        outputRedTable.put(redTable->at(currentColor));
    }
    outputRedTable.close();
#endif
}
void ColorPalette::GenerateGreentable()
{
    colorValues greenColor;
    greenColor.RedElement = 0;
    greenColor.GreenElement = 140;
    greenColor.BlueElement = 0;
    
    colorValues lightGreenColor;
    lightGreenColor.RedElement = 252;
    lightGreenColor.GreenElement = 252;
    lightGreenColor.BlueElement = 56;
    
    greenTable = GenerateColorizedTable(32, greenColor, lightGreenColor);
    
#if DUMPGREENTABLE
    std::ofstream outputGreenTable("togreen.grd");
    for(int currentColor = 0; currentColor < greenTable->size(); currentColor++)
    {
        outputGreenTable.put(greenTable->at(currentColor));
    }
    outputGreenTable.close();
#endif
}
void ColorPalette::GenerateBluetable()
{
    colorValues blueColor;
    blueColor.RedElement = 0;
    blueColor.GreenElement = 60;
    blueColor.BlueElement = 150;
    
    colorValues lightBlueColor;
    lightBlueColor.RedElement = 204;
    lightBlueColor.GreenElement = 248;
    lightBlueColor.BlueElement = 248;
    
    blueTable = GenerateColorizedTable(32, blueColor, lightBlueColor);
    
#if DUMPBLUETABLE
    std::ofstream outputBlueTable("toblue.grd");
    for(int currentColor = 0; currentColor < blueTable->size(); currentColor++)
    {
        outputBlueTable.put(blueTable->at(currentColor));
    }
    outputBlueTable.close();
#endif
}

void ColorPalette::GenerateBasicColorTables()
{
    GenerateTransparentColorsTable();
    GenerateGreyscaleTable();
    GenerateShadowtable();
    GenerateLighttable();
    GenerateRedtable();
    GenerateGreentable();
    GenerateBluetable();
}
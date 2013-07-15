#include "ColorPalette.hpp"

ColorPalette::ColorPalette()
{
#if VERBOSE >= 5
    std::cout << "Constructing ColorPalette Object.\n";
#endif
    transparentColorsTable = NULL;
    greyscaleTable = NULL;
    rgbTable = NULL;
    formattedPaletteData = NULL;
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
    if(rgbTable != NULL)
    {
        #if VERBOSE >= 5
            std::cout << "Deallocating rgbTable.\n";
        #endif
        delete rgbTable;
        rgbTable = NULL;
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
    inputFile.seekg (0, inputFile.beg);
    
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
    
    colorValues currentColor;
    colorValues currentOnLightColor;
    colorValues currentUnderLightColor;
    colorValues currentCombinedLightColor;

    float leastColorDifference,colorDifference;
    
    
    int currentSelectedColor, currentSelectedColor2, findcol, bestfit = 0;
    
    for (currentSelectedColor2 = 0; currentSelectedColor2 < MAXIMUMNUMBEROFCOLORSPERPALETTE; currentSelectedColor2++)
    {
        currentUnderLightColor = GetColorFromPalette(currentSelectedColor2);
        
        for (currentSelectedColor = 0; currentSelectedColor < MAXIMUMNUMBEROFCOLORSPERPALETTE; currentSelectedColor++)
        {
            currentOnLightColor = GetColorFromPalette(currentSelectedColor);
        
            currentCombinedLightColor.RedElement = (currentOnLightColor.RedElement + currentUnderLightColor.RedElement);
            currentCombinedLightColor.BlueElement = (currentOnLightColor.BlueElement + currentUnderLightColor.BlueElement);
            currentCombinedLightColor.GreenElement = (currentOnLightColor.GreenElement + currentUnderLightColor.GreenElement);
            
            //Set the maximum value of a float to avoid false differences
            leastColorDifference = 655350.0;
            
            for  (findcol = 0; findcol < MAXIMUMNUMBEROFCOLORSPERPALETTE; findcol++)
            {
                currentColor = GetColorFromPalette(findcol);
                currentColor.RedElement = (currentColor.RedElement - currentCombinedLightColor.RedElement) * 30;
                currentColor.BlueElement = (currentColor.BlueElement - currentCombinedLightColor.BlueElement) * 59;
                currentColor.GreenElement = (currentColor.GreenElement - currentCombinedLightColor.GreenElement) * 11;

                colorDifference = sqrt((currentColor.RedElement * currentColor.RedElement) +
                              (currentColor.BlueElement * currentColor.BlueElement) +
                              (currentColor.GreenElement * currentColor.GreenElement));
                
                if  (colorDifference < leastColorDifference)//found best equality
                {
                    leastColorDifference = colorDifference;
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
    
    greyscaleTable->resize(MAXIMUMNUMBEROFCOLORSPERPALETTE * MAXIMUMNUMBEROFCOLORSPERPALETTE);
    
    colorValues currentColor;
    colorValues findColor;
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
            
            findColor.RedElement = (findColor.RedElement - currentColor.RedElement) * 30;
            findColor.BlueElement = (findColor.BlueElement - currentColor.BlueElement) * 11;
            findColor.GreenElement = (findColor.GreenElement - currentColor.GreenElement) * 59;
            
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
    std::ofstream outputGreyscaleTable("GreyScaleTable.dat");
    for(int currentColor = 0; currentColor < greyscaleTable->size(); currentColor++)
    {
        outputGreyscaleTable.put(greyscaleTable->at(currentColor));
    }
    outputGreyscaleTable.close();
#endif
}

#warning Untested
std::vector<colorValues> ColorPalette::GenerateGlowColors(int maxGradation, colorValues startingColor, colorValues endingColor)
{
    #if VERBOSE >= 2
        std::cout << "Creating vector of size: " << maxGradation << '\n';
    #endif
    
    
    std::vector<colorValues> finalGlowColors;
    finalGlowColors.resize(maxGradation);
    
    colorValues trColor, currentProcessColor;
	
    int i = 0;
    
    float mgr3 = maxGradation/3;
	float mgr31 = mgr3*1.67;
    for(; i < mgr3; i++)
    {
        currentProcessColor.RedElement = (startingColor.RedElement * (i/mgr31 + 0.4));
        currentProcessColor.GreenElement = (startingColor.GreenElement * (i/mgr31 + 0.4));
        currentProcessColor.BlueElement = (startingColor.BlueElement * (i/mgr31 + 0.4));
        finalGlowColors.at(i) = currentProcessColor;
    }
    
    float mgr23 = mgr3 * 2;
    trColor.RedElement = endingColor.RedElement - startingColor.RedElement;
    trColor.GreenElement = endingColor.GreenElement - startingColor.GreenElement;
    trColor.BlueElement = endingColor.BlueElement - startingColor.BlueElement;
    
    for(; i < maxGradation; i++)
    {
        float togo = (i-mgr3)/mgr23;
        currentProcessColor.RedElement = (startingColor.RedElement + trColor.RedElement * togo);
        currentProcessColor.GreenElement = (startingColor.GreenElement + trColor.GreenElement * togo);
        currentProcessColor.BlueElement = (startingColor.BlueElement + trColor.BlueElement * togo);
        finalGlowColors.at(i) = currentProcessColor;
    }
    
    if(endingColor.RedElement && endingColor.GreenElement && endingColor.BlueElement)
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
    return finalGlowColors;
}
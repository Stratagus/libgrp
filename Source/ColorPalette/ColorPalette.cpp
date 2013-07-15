#include "ColorPalette.hpp"

ColorPalette::ColorPalette()
{
    paletteData = NULL;
    transparentColorsTable = NULL;
    greyscaleTable = NULL;
    rgbTable = NULL;
    formattedPaletteData = NULL;
}

ColorPalette::~ColorPalette()
{
    if(paletteData != NULL)
    {
        delete paletteData;
        paletteData = NULL;
    }
    if(formattedPaletteData != NULL)
    {
        delete formattedPaletteData;
        formattedPaletteData = NULL;
    }
    if(transparentColorsTable != NULL)
    {
        delete transparentColorsTable;
        transparentColorsTable = NULL;
    }
    if(greyscaleTable != NULL)
    {
        delete greyscaleTable;
        greyscaleTable = NULL;
    }
    if(rgbTable != NULL)
    {
        delete rgbTable;
        rgbTable = NULL;
    }
}

void ColorPalette::LoadPalette(std::vector<char> *inputPalette)
{
    
    if( (inputPalette != NULL) && ((inputPalette->size() != 768) && (inputPalette->size() != 1024)))
    {
        CurruptColorPaletteException curruptPalette;
        curruptPalette.SetErrorMessage("Invalid or Currupt Color Palette; expecting 768 or 1024.");
        throw(curruptPalette);
    }
    if(paletteData != NULL)
    {
        delete paletteData;
    }
    paletteData = inputPalette;
}

void ColorPalette::LoadPalette(std::string filePath)
{
    int inputFileSize;
    colorValues currentColorProcessing;
    
    if(paletteData == NULL)
    {
        paletteData = new std::vector<char>;
    }
    else
    {
        delete paletteData;
        paletteData = new std::vector<char>;
    }
    
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
        if(paletteData != NULL)
        {
            delete paletteData;
            paletteData = NULL;
        }
        CurruptColorPaletteException curruptPalette;
        curruptPalette.SetErrorMessage("Invalid or Currupt Color Palette; expecting 768 or 1024.");
        throw(curruptPalette);
    }
    
    //Since the file passed the check allocated or resize the vector
    //to the proper size.
    if(formattedPaletteData == NULL)
    {
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
}

colorValues ColorPalette::GetColorFromPalette(int colorNumber)
{
    colorValues selectedColor;
    selectedColor.RedElement = paletteData->at((colorNumber * 3) + 0);
    selectedColor.BlueElement = paletteData->at((colorNumber * 3) + 2);
    selectedColor.GreenElement = paletteData->at((colorNumber * 3) + 1);
    
    return selectedColor;
}

void ColorPalette::GenerateTransparentColorsTable()
{
    if(paletteData == NULL)
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
}

void ColorPalette::GenerateGreyscaleTable()
{
    if(paletteData == NULL)
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
        
        lowest = 655350.0;
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
}

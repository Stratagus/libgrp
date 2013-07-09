#include "ColorPalette.hpp"

ColorPalette::ColorPalette()
{
    paletteData = NULL;
    transparentColorTable = NULL;
}

ColorPalette::~ColorPalette()
{
    if(paletteData != NULL)
    {
        delete paletteData;
        paletteData = NULL;
    }
    if(transparentColorTable != NULL)
    {
        delete transparentColorTable;
        transparentColorTable = NULL;
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
    if(paletteData == NULL)
    {
        paletteData = new std::vector<char>;
    }
    else
    {
        delete paletteData;
        paletteData = new std::vector<char>;
    }
    LoadPaletteFileToVector(filePath, paletteData);
    if((paletteData->size() != 768) && (paletteData->size() != 1024))
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
}

void ColorPalette::LoadPaletteFileToVector(std::string filePath, std::vector<char> *destinationVector)
{
    
    std::fstream inputFile(filePath.c_str());
    
    inputFile.exceptions(std::ifstream::badbit | std::ifstream::failbit | std::ifstream::eofbit);
    
    inputFile.seekg(0, std::ios::end);
    
    std::streampos length(inputFile.tellg());
    
    if (length)
    {
        inputFile.seekg(0, std::ios::beg);
        destinationVector->resize(static_cast<std::size_t>(length));
        inputFile.read(&destinationVector->front(), static_cast<std::size_t>(length));
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
    if(transparentColorTable == NULL)
    {
        //Create a vector with the max number of colors
        transparentColorTable = new std::vector<char>;
        transparentColorTable->resize(MAXIMUMNUMBEROFCOLORSPERPALETTE * MAXIMUMNUMBEROFCOLORSPERPALETTE);
    }
    
    colorValues currentColor;
    colorValues currentOnLightColor;
    colorValues currentUnderLightColor;
    colorValues currentCombinedLightColor;
    
    
    float fr, fg, fb;
    float fr2, fg2, fb2;
    float ir, ig, ib,lowest,coldif;
    
    float absr, absg, absb;
    
    int col,col2,findcol,bestfit=0;
    
    
    /* Lightlevelon + lightlevelunder must equal to 1 */
    
    /* Transparency is created by taking two colors, multiplying the
     RGB values by a percentage, and adding the RGB values together.  The
     new color will contain a little bit of each original color. */
    
    
    /* For each of the 256 colors, we can mix with any other color, therefore
     we need a 256x256 table. */
    
    int maxpalettecolor=256;
    for (col2 = 0; col2 < MAXIMUMNUMBEROFCOLORSPERPALETTE; col2++)
    {
        std::cout << "Current col2: " << col2 << '\n';
        //fr2 = (float)REDELEM(col2) * LIGHTLEVELUNDER;
        //fg2 = (float)GREENELEM(col2) * LIGHTLEVELUNDER;
        //fb2 = (float)BLUEELEM(col2) * LIGHTLEVELUNDER;
        
        currentUnderLightColor = GetColorFromPalette(col2);
        
        for (col = 0; col < maxpalettecolor; col++)
        {
            //fr= (float)REDELEM(col) * LIGHTLEVELON;
            //fg= (float)GREENELEM(col) * LIGHTLEVELON;
            //fb= (float)BLUEELEM(col) * LIGHTLEVELON;
            currentOnLightColor = GetColorFromPalette(col);
            
            
            
            currentCombinedLightColor.RedElement = (currentOnLightColor.RedElement + currentUnderLightColor.RedElement);
            currentCombinedLightColor.BlueElement = (currentOnLightColor.BlueElement + currentUnderLightColor.BlueElement);
            currentCombinedLightColor.GreenElement = (currentOnLightColor.GreenElement + currentUnderLightColor.GreenElement);
            //ir = (long)(fr + fr2);
            //ig = (long)(fg + fg2);
            //ib = (long)(fb + fb2);
            
            lowest = 655350.0;
            for  (findcol = 0; findcol < MAXIMUMNUMBEROFCOLORSPERPALETTE; findcol++)
            {
                
                //std::cout << "FindCol: " << findcol << " Current Inside Access: " << " RED " <<(findcol - ir) << " GREEN " <<(findcol - ig) << " BLUE " <<(findcol - ib) << " of vector size "  << paletteData->size() << '\n';
                
                currentColor = GetColorFromPalette(findcol);
                currentColor.RedElement = (currentColor.RedElement - currentCombinedLightColor.RedElement) * 30;
                currentColor.BlueElement = (currentColor.BlueElement - currentCombinedLightColor.BlueElement) * 59;
                currentColor.GreenElement = (currentColor.GreenElement - currentCombinedLightColor.GreenElement) * 11;
                
                //absr = ((float)REDELEM(findcol) - ir) * 30;//r-percentage RED in any color
                //absg = ((float)GREENELEM(findcol) - ig) * 59;//g-percentage GREEN in any color
                //absb = ((float)BLUEELEM(findcol) - ib) * 11;//b-percentage BLUE in any color
                
                //coldif = sqrt(absr*absr + absg*absg + absb*absb);
                coldif = sqrt((currentColor.RedElement * currentColor.RedElement) +
                              (currentColor.BlueElement * currentColor.BlueElement) +
                              (currentColor.GreenElement * currentColor.GreenElement));
                
                if  (coldif < lowest)//found best equality
                {
                    lowest = coldif;
                    bestfit = findcol;
                }
            }
            //std::cout << "Bestfit " << bestfit << " to position " << (col2 * MAXIMUMNUMBEROFCOLORSPERPALETTE + col) << '\n';
            transparentColorTable->at((col2 * MAXIMUMNUMBEROFCOLORSPERPALETTE + col)) = bestfit;
            //outfortrbuffer[col2 * maxpalettecolor + col] = bestfit;
        }
    }
}
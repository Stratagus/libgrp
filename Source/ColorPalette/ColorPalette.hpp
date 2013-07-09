#ifndef ColorPalette_Header
#define ColorPalette_Header

#include <string>
#include <vector>
#include <fstream>
#include <math.h>

#include "../Exceptions/ColorPalette/ColorPaletteException.hpp"

#warning debug include
#include <iostream>

//The maximum number of colors supported by the table
//ie (256*256) Table
#define MAXIMUMNUMBEROFCOLORSPERPALETTE 256

#define LIGHTLEVELON    0.5                  /* Percent of color 1 */
#define LIGHTLEVELUNDER (1-LIGHTLEVELON)     /* Percent of color 2 */

//Define the base colors
#define REDCOLOR		0
#define GREENCOLOR		1
#define BLUECOLOR		2

#define NRELEM(elem,nr)	paletteData->at((elem)*3+nr)

#define REDELEM(elem) 	NRELEM(elem,REDCOLOR)
#define GREENELEM(elem) NRELEM(elem,GREENCOLOR)
#define BLUEELEM(elem)	NRELEM(elem,BLUECOLOR)

//Used to select a specific color from the Palette
//Each color in the palette has three elements, Red(Byte 0), Green (Byte 1) and Blue (Byte 3)
//So to select a color from the Palette (for example the third color we would go 3 sets of 3 down
// the list (3*3). Which we will be at the Red (at Byte 0), we then simple add 1 (for Green) or
// 2 (for Blue) to get the element of that specific color.
struct colorValues
{
    float RedElement;
    float BlueElement;
    float GreenElement;
};

class ColorPalette
{
	public:
		ColorPalette();
		~ColorPalette();
    
    
        //!Set palette data from memory
        /*! Use the palette data that is loaded in a the specified
        * vector.
        * \pre The inputPalette vector must be defined and contain
        *      valid wpe palette data. Otherwise there will be decoding
        *      errors. (Colors will not display correctly)
        * \param[in] inputPalette The memory location of the palette
        *      to use with the GRPImage.
        * \warning This will not make a copy of the std::vector<char> data
        *      so if you delete the vector before/during processing it will crash.
        * \note NA*/
        void LoadPalette(std::vector<char> *inputPalette);
    
        //!Load palette data from a file (.wpe)
        /*! Load a GRP Palette file to use when decoding/encoding
        * a GRPImage.
        * \pre Filepath must be to a valid .pal palette file
        * \post The file is loaded into memory for the GRPImage
        * \param[in] filePath The file path to the palette file
        *\note NA
        */
        void LoadPalette(std::string filePath);

        void LoadPaletteFileToVector(std::string filePath, std::vector<char> *destinationVector);
    
    
        void GenerateTransparentColorsTable();

	protected:
        std::vector<char> *paletteData;
        std::vector<char> *transparentColorTable;
    
        //!Gets the Red/Blue/Green values for a specific color in the Palette
        /*! Details
         * \pre
         * \post
         * \warning
         * \note NA*/
        colorValues GetColorFromPalette(int colorNumber);
	private:
};

#endif

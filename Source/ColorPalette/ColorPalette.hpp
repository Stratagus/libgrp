/*!
 *  \brief     A datastructure for holding a GRP Palette
 *  \details   Datastructure that generates the color tables, loads the palette
 *              and allows for easy color access.
 *  \author    Bradley Clemetson, GRPLib Authors https://sourceforge.net/projects/grplib
 *  \version   0.0.1
 *  \date      July 8, 2013
 *  \copyright LGPL
 */

#ifndef ColorPalette_Header
#define ColorPalette_Header

#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <math.h>

#include "../Exceptions/ColorPalette/ColorPaletteException.hpp"

#if VERBOSE
    #include <iostream>
#endif

//#define DUMPCOLORTABLE
#define DUMPPALETTEDATA 1
#define DUMPTRANSPARENTTABLE 1
#define DUMPGREYSCALETABLE 1

#warning Finish documentation

//The maximum number of colors supported by the table
//ie (256*256) Table
#define MAXIMUMNUMBEROFCOLORSPERPALETTE 256

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
        * \warning The method will not delete the vector, called remains responsible for
        *       inputPalette vector deallocation.
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
    
        //!Generates the TransparentColor Table to be applied to the GRP images
        /* \pre A valid GRP Palette must be loaded to paletteData
         * \post A transparent color table will be generated based off
         *      the palette file input.
         * \note NA*/
        void GenerateTransparentColorsTable();
    
        //!Generates the GreyscaleColor Table to be applied to the GRP images
        /* \pre A valid GRP Palette must be loaded to paletteData
        * \post A greyscale color table will be generated based off
        *      the palette file input.
        * \note NA*/
        void GenerateGreyscaleTable();
  
#warning Document method?
        //!Generates the RGBColor Table to be applied to the GRP images
        /* \pre
         * \param[in] startGlowColor
         * \param[in] endGlowColor
         * \param[in] maxGradations
         * \post
         * \note NA*/
        void GenerateRGBTable(int startGlowColor, int endGlowColor, int maxGradations);

	protected:

        //!Generates the Glow Colors of a specific image
        /*! Details here
         * \pre
         * \post
         * \param [in] maxGradation How fine set of colors to be generated
         * \param [in] startingColor The starting color to begin color shades
         * \param [in] endingColor The target color of the gradient generation
         * \note NA*/
        std::vector<colorValues> GenerateGlowColors(int maxGradation, colorValues startingColor, colorValues endingColor);
    
        //!Gets the Red/Blue/Green values for a specific color in the Palette
        /*! Details
         * \pre
         * \post
         * \warning
         * \note NA*/
        colorValues GetColorFromPalette(int colorNumber);
    
        //Loaded formatted Palette Data
        std::vector<colorValues> *formattedPaletteData;
    
        //The generated Transparent Color Table
        std::vector<char> *transparentColorsTable;
        //The generated Greyscale Table
        std::vector<char> *greyscaleTable;
        //The generated RBG Table
        std::vector<char> *rgbTable;
    
	private:
};

#endif

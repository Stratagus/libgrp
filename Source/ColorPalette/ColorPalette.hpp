/*!
 *  \brief     A datastructure for holding a GRP Palette
 *  \details   Datastructure that generates the color tables, loads the palette
 *              and allows for easy color access.
 *  \author    Bradley Clemetson, GRPLib Authors https://sourceforge.net/projects/grplib
 *  \version   1.0.0
 *  \date      July 8, 2013
 *  \copyright LGPLv2
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

//Uncomment each to dump the raw output vectors to files
//for inspection.
#define DUMPPALETTEDATA 0
#define DUMPTRANSPARENTTABLE 0
#define DUMPGREYSCALETABLE 0
#define DUMPGLOWTABLE 0
#define DUMPCOLORIZETABLE 0

#define DUMPSHADOWTABLE 0
#define DUMPLIGHTTABLE 0
#define DUMPREDTABLE 0
#define DUMPGREENTABLE 0
#define DUMPBLUETABLE 0

//The maximum number of colors supported by the table
//ie (256*256) Table
#define MAXIMUMNUMBEROFCOLORSPERPALETTE 256

#define LIGHTLEVELON    0.5                  /* Percent of color 1 */
#define LIGHTLEVELUNDER (1-LIGHTLEVELON)     /* Percent of color 2 */

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
  
        //!Generates Colorization tables
        /*! Generates Colorization table (the table colors the start 
         *  from startingGlowColor and transform to endingglowColor.
         * \pre A valid palette file must be loaded
         * \returns A table with colors from startingGlowColor to endingGlowColor
         * \param [in] maxGradation The number of colors (shades) to generate
         * \param [in] startingGlowColor The starting color
         * \param [in] endingGlowColor The target color to generate towards
         * \note NA*/
        std::vector<uint8_t> *GenerateColorizedTable(int maxGradation, colorValues startingGlowColor, colorValues endingGlowColor);
    
        //!Generate Colortable with the rules of passed in color and multiplicator
        /*! Details here
         * \pre
         * \post
         * \param [in]
         * \param [in]
         * \returns
         * \note NA*/
        std::vector<colorValues> GenerateTableWithConstraints(colorValues baseColor, float addGradation);
    
        //!Generate all base color tables
        /*!A simple convience method to call all the different
         *  table generators.
         * \pre A valid palette file must be loaded.
         * \post Shadow/Light/Red/Green/Blue tables are generated
         * \note NA*/
        void GenerateBasicColorTables(int gradation = 32);
    
        //!Generate the Shadow Table
        /*! Generates different shades of black that 
         *  can/will be applied to unit shadows
         * \pre A valid palette file must be loaded
         * \post Generates a 8192byte set of shades
         * \note NA*/
        void GenerateShadowtable(int gradation = 32);
    
        //!Generate the Light Table
        /*! Generates different shade of white that
         *  can/will be applied to images for highlights.
         * \pre A valid palette file must be loaded
         * \post Generates a 8192byte set of shades
         * \note NA*/
        void GenerateLighttable(int gradation = 32);
    
        //!Generate the Red Table
        /*! Generates multiple shades of Red that
         *  can/will be used for different art assets (blood, ect)
         * \pre A valid palette file must be loaded
         * \post Generates a 8192byte set of shades
         * \note NA*/
        void GenerateRedtable(int gradation = 32);
    
        //!Generate the Green Table
        /*! Generates multiple shades of Green that
        *  can/will be used for different art assets (plants, ect)
        * \pre A valid palette file must be loaded
        * \post Generates a 8192byte set of shades
        * \note NA*/
        void GenerateGreentable(int gradation = 32);
    
        //!Generate the Blue Table
        /*! Generates multiple shades of Blue that
         *  can/will be used for different art assets (water, ect)
         * \pre A valid palette file must be loaded
         * \post Generates a 8192byte set of shades
         * \note NA*/
        void GenerateBluetable(int gradation = 32);

	protected:

        //!Generates the Glow Colors of a specific image
        /*! Generates a byte glow table (shades) based on the
         *  color values entered in initialColor to finalColor
         * \pre A palette file must be loaded, colorvalues defined and maxGradation
         *       a positive value.
         * \returns A colorValues vector containing the best fit colors from the palette
         * \param [in] maxGradation How fine set of colors to be generated
         * \param [in] startingColor The starting color to begin color shades
         * \param [in] endingColor The target color of the gradient generation
         * \note NA*/
        std::vector<colorValues> GenerateGlowColors(unsigned int maxGradation, colorValues initialColor, colorValues finalColor);
    
        //!Gets the Red/Blue/Green values for a specific color in the Palette
        /*! A simple getter to grab the Red/Blue/Green elements of a specific
         *      color.
         * \pre A palette must be loaded and colorNumber a valid Color palette #
         * \returns A colorValues struct with the loaded element values.
         * \note NA*/
        colorValues GetColorFromPalette(int colorNumber);
    
        //!Gets the difference in between two colors
        /*! Subtracts the operationColor from the Initialcolor
         * \pre Both colorValues structs must be declared and defined
         * \returns A new colorValues struct of initialColor - operationColor
         * \note difference = initialColor - operationColor NA*/  
        colorValues GetColorDifference(colorValues initialColor, colorValues operationColor);
    
        //Loaded formatted Palette Data
        std::vector<colorValues> *formattedPaletteData;
    
        //The generated Transparent Color Table
        std::vector<uint8_t> *transparentColorsTable;
        //The generated Greyscale Table
        std::vector<uint8_t> *greyscaleTable;
    
        //The generated Light Color Table (White)
        std::vector<uint8_t> *lightTable;
    
        //The generated Shadow Color Table (Black)
        std::vector<uint8_t> *shadowTable;
    
        //The generated Red Color Table
        std::vector<uint8_t> *redTable;
    
        //The generated Green Color Table
        std::vector<uint8_t> *greenTable;
    
        //The generated Blue Color Table
        std::vector<uint8_t> *blueTable;
    
	private:
};

#endif

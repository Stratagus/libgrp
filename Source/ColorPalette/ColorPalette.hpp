#ifndef ColorPalette_Header
#define ColorPalette_Header

/*!ColorPalette Datastructure
 *  \brief     A datastructure for holding a GRP Palette data
 *  \details   Datastructure that generates the color tables, loads the palette
 *              and allowing for easy color access.
 *  \author    Bradley Clemetson, GRPLib Authors https://sourceforge.net/projects/grplib
 *  \version   1.0.0
 *  \date      July 8, 2013
 *  \copyright LGPLv2
 *  \section basicColorPaletteFileLayout ColorPalette File Layout
 *  The standard GRP Color palette is either 768 or 1024 bytes
 *  each byte (uint8_t) represents one color element (Red, Blue, Green).
 *  \image html ColorPaletteFileLayout.png ![Diagram of GRP Color Palette Layout] 
 */


#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <math.h>
#include <inttypes.h>

#include "../Exceptions/ColorPalette/ColorPaletteException.hpp"

#if VERBOSE
    #include <iostream>
#endif

//Allow Windows to use 8/16/32 byte values
#if defined(_WIN32)
#include <stdint.h>
    typedef uint8_t u_int8_t;
    typedef uint16_t u_int16_t;
    typedef uint32_t u_int32_t;
#else
#include <inttypes.h>
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
    
        //Convience constructors to load
        ColorPalette(std::vector<char> *inputPalette);
        ColorPalette(std::string filePath);
    
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
        * \throws CurruptColorPaletteException - Bad Colorpalette detected
        * \note NA*/
        void LoadPalette(std::vector<char> *inputPalette);
    
        //!Load palette data from a file (.wpe)
        /*! Load a GRP Palette file to use when decoding/encoding
        * a GRPImage.
        * \pre Filepath must be to a valid .pal palette file
        * \post The file is loaded into memory for the GRPImage
        * \param[in] filePath The file path to the palette file
        * \throws CurruptColorPaletteException
        * \note NA*/
        void LoadPalette(std::string filePath);
    
        //!Gets the number of colors on the Palette
        /*! A simple getter to get the number of colors in a Palette
        * \pre NA
        * \returns The number of colors in a palette
        * \note NA*/
        int GetNumberOfColors();
    
        //!Gets the Red/Blue/Green values for a specific color in the Palette
        /*! A simple getter to grab the Red/Blue/Green elements of a specific
        *      color.
        * \pre A palette must be loaded and colorNumber a valid Color palette #
        * \returns A colorValues struct with the loaded element values.
        * \throws OutofBoundsColorException
        * \throws NoPaletteLoadedException
        * \note NA*/
        colorValues GetColorFromPalette(int colorNumber);
    
        //!Generates the TransparentColor Table to be applied to the GRP images
        /* \pre A valid GRP Palette must be loaded to paletteData
         * \post A transparent color table will be generated based off
         *      the palette file input.
         * \throws NoPaletteLoadedExpception
         * \note NA*/
        void GenerateTransparentColorsTable();
    
        //!Generates the GreyscaleColor Table to be applied to the GRP images
        /* \pre A valid GRP Palette must be loaded to paletteData
         * \post A greyscale color table will be generated based off
         *      the palette file input.
         * \throws NoPaletteLoadedException
         * \note NA*/
        void GenerateGreyscaleTable();
    
        //!Generate all base color tables
        /*!A simple convience method to call all the different
         *  table generators.
         * \pre A valid palette file must be loaded.
         * \post Shadow/Light/Red/Green/Blue tables are generated
         * \throws NoPaletteLoadedException
         * \note NA*/
        void GenerateColorTables(int gradation = 32);
    
        //!Generate the Shadow Table
        /*! Generates different shades of black that 
         *  can/will be applied to unit shadows
         * \pre A valid palette file must be loaded
         * \post Generates a 8192byte set of shades
         * \throws NoPaletteLoadedException
         * \note NA*/
        void GenerateShadowtable(int gradation = 32);
    
        //!Generate the Light Table
        /*! Generates different shade of white that
         *  can/will be applied to images for highlights.
         * \pre A valid palette file must be loaded
         * \post Generates a 8192byte set of shades
         * \throws NoPaletteLoadedException
         * \note NA*/
        void GenerateLighttable(int gradation = 32);
    
        //!Generate the Red Table
        /*! Generates multiple shades of Red that
         *  can/will be used for different art assets (blood, ect)
         * \pre A valid palette file must be loaded
         * \post Generates a 8192byte set of shades
         * \throws NoPaletteLoadedException
         * \note NA*/
        void GenerateRedtable(int gradation = 32);
    
        //!Generate the Green Table
        /*! Generates multiple shades of Green that
        *  can/will be used for different art assets (plants, ect)
        * \pre A valid palette file must be loaded
        * \post Generates a 8192byte set of shades
         * \throws NoPaletteLoadedException
        * \note NA*/
        void GenerateGreentable(int gradation = 32);
    
        //!Generate the Blue Table
        /*! Generates multiple shades of Blue that
         *  can/will be used for different art assets (water, ect)
         * \pre A valid palette file must be loaded
         * \post Generates a 8192byte set of shades
         * \throws NoPaletteLoadedException
         * \note NA*/
        void GenerateBluetable(int gradation = 32);
    
        //!Apply values from the shadow table to image
        /*!Generates (if needed) and applied the value on all Colorelements of the base color
         * \pre PaletteData loaded and targetApplication be in bounds
         * \returns colorValues with the applied color table
         * \param[in] basecolor The starting color the table should apply
         * \param[in] The desired application value
         * \throws NoPaletteLoadedException
         * \throw OutofBoundsColorException
         * \note NA*/
        colorValues ApplyShadowValue(colorValues baseColor, int targetApplication);
    
        //!Apply values from the light table to image
        /*!Generates (if needed) and applied the value on all Colorelements of the base color
        * \pre PaletteData loaded and targetApplication be in bounds
        * \returns colorValues with the applied color table
        * \param[in] basecolor The starting color the table should apply
        * \param[in] The desired application value
        * \throws NoPaletteLoadedException
        * \throw OutofBoundsColorException
        * \note NA*/
        colorValues ApplyLightValue(colorValues baseColor, int targetApplication);
    
        //!Apply values from the Red table to image
        /*!Generates (if needed) and applied the value on all Colorelements of the base color
        * \pre PaletteData loaded and targetApplication be in bounds
        * \returns colorValues with the applied color table
        * \param[in] basecolor The starting color the table should apply
        * \param[in] The desired application value
        * \throws NoPaletteLoadedException
        * \throw OutofBoundsColorException
        * \note NA*/
        colorValues ApplyRedValue(colorValues baseColor, int targetApplication);
    
        //!Apply values from the Blue table to image
        /*!Generates (if needed) and applied the value on all Colorelements of the base color
        * \pre PaletteData loaded and targetApplication be in bounds
        * \returns colorValues with the applied color table
        * \param[in] basecolor The starting color the table should apply
        * \param[in] The desired application value
        * \throws NoPaletteLoadedException
        * \throw OutofBoundsColorException
        * \note NA*/
        colorValues ApplyBlueValue(colorValues baseColor, int targetApplication);
    
        //!Apply values from the Blue table to image
        /*!Generates (if needed) and applied the value on all Colorelements of the base color
        * \pre PaletteData loaded and targetApplication be in bounds
        * \returns colorValues with the applied color table
        * \param[in] basecolor The starting color the table should apply
        * \param[in] The desired application value
        * \throws NoPaletteLoadedException
        * \throw OutofBoundsColorException
        * \note NA*/
        colorValues ApplyGreenValue(colorValues baseColor, int targetApplication);
    
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
         * \pre Color Palette must be loaded
         * \param [in] baseColor The starting to generate the table
         * \param [in] addGradation How fine of shades between colors to create
         * \returns A new constraind table
         * \note NA*/
        std::vector<colorValues> GenerateTableWithConstraints(colorValues baseColor, float addGradation);
    
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
    
    
        //!Gets the difference in between two colors
        /*! Subtracts the operationColor from the Initialcolor
         * \pre Both colorValues structs must be declared and defined
         * \returns A new colorValues struct of initialColor - operationColor
         * \note difference = initialColor - operationColor NA*/  
        colorValues GetColorDifference(colorValues initialColor, colorValues operationColor);
    
        //!Ensures that all tables are NULL or deleted.
        /*!Cleans out all the palettes in order to ensure all data is deleted
         * \pre NA
         * \post All the ColorPalette tables are deleted
         * \note NA*/
        void ClearAllTables();
    
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

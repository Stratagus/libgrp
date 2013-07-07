#ifndef ColorPalette_Header
#define ColorPalette_Header

#include <string>
#include <vector>
#include <fstream>

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
        * \pre Filepath must be to a valid .wpe palette file
        * \post The file is loaded into memory for the GRPImage
        * \param[in] filePath The file path to the palette file
        *\note NA
        */
        void LoadPalette(std::string filePath);

        void LoadFileToVector(std::string filePath, std::vector<char> *destinationVector);

		void GenerateColorTables();
		void GenerateRedColorTable();
		void GenerateGreenColorTable();
		void GenerateBlueColorTable();
		void GenerateBlackColorTable();
		void GenerateWhiteColorTable();

	protected:
        std::vector<char> *paletteData;
	private:
};

#endif

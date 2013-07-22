/*!
 *  \brief     The main
 *  \details   This class runs all the underlying generic functions required
 * 				for nearly all objects in the framework
 *  \author    Bradley Clemetson, from GRPLib Authors
 *  \version   0.0.1
 *  \date      Jan 13, 2013
 *  \copyright LGPLv2
 *  \section basicsGRPFormat Basic Format Aspects
 *  \section conventions Naming Conventions
 *  \section av
 *  \image html GRPFileLayout.png
 */
#ifndef GRPImage_Header
#define GRPImage_Header

#include "../GRPFrame/GRPFrame.hpp"
#include "../ColorPalette/ColorPalette.hpp"

#include "../Exceptions/GRPImage/GRPImageException.hpp"
#include <list>
#include <fstream>
#include <tr1/unordered_map>

//Gives the ability to convert images to other formats.
#if MAGICKPP_FOUND
    #include <sstream>
    #include <iomanip>
    #include <Magick++/Image.h>
    #include <Magick++/Pixels.h>
#endif

//Allow Windows to use 8/16/32 byte values
#if defined(_WIN32)
#include <stdint.h>
    typedef uint8_t u_int8_t;
    typedef uint16_t u_int16_t;
    typedef uint32_t u_int32_t;
#endif

enum GRPImageType {STANDARD, SHADOW};

class GRPImage
{
    
public:
        GRPImage(std::vector<char> *inputImage, bool removeDuplicates = true);
        GRPImage(std::string filePath, bool removeDuplicates = true);
        ~GRPImage();
    
    //!Set image data from memory
    /*! Use the image data that is loaded in a the specified
     * vector.
     * \pre The inputInput vector must be defined and contain
     *      valid grp image data. Otherwise there will be decoding
     *      errors. (garbled up junk images)
     * \param[in] inputPalette The memory location of the image
     *      to be decoded/encoded.
     * \warning This will not make a copy of the std::vector<char> data
     *      so if you delete the vector before/during processing it will likly crash.
     * \note NA*/
    void LoadImage(std::vector<char> *inputImage);
    
    //!Load image data from a file (.wpe)
    /*! Load a GRP file to use when decoding/encoding
     * a GRPImage.
     * \pre Filepath must be to a valid .grp image file
     * \post The file is loaded into memory for the GRPImage
     * \param[in] filePath The file path to the grp image file
     * \note NA
     */
    void LoadImage(std::string filePath, bool removeDuplicates = false);
    
    //!Return the number of frames in a GRPImage
    /*! Return the number of frames in a GRP image animation.
     * \pre GRP image data must be defined and loaded into
     *      imageData.
     * \returns The number of image frames in a GRP Image.
     */
    uint16_t getNumberOfFrames() const;
    
    //!Return the maximum width of any GRP image Frame
    /*! Returns the maximum width of any GRP image Frame
     *  allowing for easier decoding and encoding to a
     *  single image.
     * \pre GRPImage must be defined and have imageData loaded
     * \returns The maximum width of any individual GRP Frame.
     * \note NA*/
    uint16_t getMaxImageWidth() const;
    //!Return the maximum height of any GRP image Frame
    /*! Returns the maximum height of any GRP image Frame
     *  allowing for easier decoding and encoding to a
     *  single image.
     * \pre GRPImage must be defined and have imageData loaded
     * \returns The maximum height of any individual GRP Frame.
     * \note NA*/
    uint16_t getMaxImageHeight() const;
    
    
    void SetColorPalette(ColorPalette *selectedColorPalette);

#if MAGICKPP_FOUND
    void ConvertImage(std::string outFilePath, int startingFrame, int endingFrame, bool singleStitchedImage = true, int imagesPerRow = 1);
#endif
protected:
    void CleanGRPImage();
    
    void DecodeGRPFrameData(std::ifstream &inputFile, GRPFrame *targetFrame);
    
    //!Load file into a std::vector<char>
    /*!Subroutine function to load a file into the internal imageData or
     * or palette data (depending on the function call).
     * \pre GRPImage must be defined and initialized, sourceFilePath must be a valid
     *      file path. destinationVector must be defined and initialized (blank).
     * \post The destinationVector contains the data from the file at path sourceFilePath
     * \note NA*/
    void LoadFileToVector(std::string sourceFilePath, std::vector<unsigned char> *destinationVector);
    
private:
    std::vector<unsigned char> *imageData;
    std::vector<GRPFrame *> imageFrames;
    ColorPalette *currentPalette;
    
    
    //GRPiamge Header
    uint16_t numberOfFrames;
    uint16_t maxImageWidth;
    uint16_t maxImageHeight;
};
#endif

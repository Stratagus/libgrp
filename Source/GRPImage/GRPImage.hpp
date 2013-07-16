/*!
 *  \brief     The main
 *  \details   This class runs all the underlying generic functions required
 * 				for nearly all objects in the framework
 *  \author    Bradley Clemetson, GRPLib Authors https://sourceforge.net/projects/grplib
 *  \version   0.0.1
 *  \date      Jan 13, 2013
 *  \copyright LGPLv2
 */
#ifndef GRPImage_Header
#define GRPImage_Header

#include "../GRPFrame/GRPFrame.hpp"
#include "../ColorPalette/ColorPalette.hpp"

#include "../Exceptions/GRPImage/GRPImageException.hpp"

class GRPImage
{
    
public:
    GRPImage();
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
    void LoadImage(std::string filePath);
    
    void ProcessGRPImage();
    
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
    void UnpackGRPImages();
    
protected:
    
    void LoadImageToFrame(unsigned int FrameNumber);
    
    //!Extract basic GRP information from the header
    /*!Extract basic information about the GRP image data
     * including the numberOfFrames, maxWidth and maxHeight. This
     * function is ran on the imageData immediatly after the data is loaded.
     * \pre imageData must be defined and contain valid GRP Image data.
     * \post numberOfFrames,maxWidth,maxHeight are given the correct
     *       GRP image metadata values.
     * \note NA*/
    void ExtractMetaData();
    
    //!Load file into a std::vector<char>
    /*!Subroutine function to load a file into the internal imageData or
     * or palette data (depending on the function call).
     * \pre GRPImage must be defined and initialized, sourceFilePath must be a valid
     *      file path. destinationVector must be defined and initialized (blank).
     * \post The destinationVector contains the data from the file at path sourceFilePath
     * \note NA*/
    void LoadFileToVector(std::string sourceFilePath, std::vector<char> *destinationVector);
    
private:
    std::vector<char> *imageData;
    std::vector<GRPFrame> *imageFrames;
    ColorPalette *currentPalette;
    
    
    
    //GrpInfo Header
    uint16_t numberOfFrames;
    uint16_t maxImageWidth;
    uint16_t maxImageHeight;
};
#endif

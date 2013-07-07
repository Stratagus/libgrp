#ifndef GRPException_H
#define GRPException_H

#include <exception>
#include <string>

//!The base exception for which all GrpImage exceptions are based off of
/*!A base exception class
 * \pre NA
 * \post NA
 * \note */

class GRPException : public virtual std::exception
{
    
public:
    void SetErrorMessage(const std::string &errorMessage);
    
    ~GRPException() throw() {}
    virtual std::string GetErrorMessage();
protected:
       std::string humanReadableError;
private:
    
};

//!An exception for filesystem based errors
/*!A Exception
 * \pre NA
 * \post NA
 * \note */
class GRPImageFilesystemException : public GRPException
{
public:
    void SetFilePath(const std::string &FilePath);
    std::string GetFilePath();
protected:
    std::string *problemPath;
    
};

#endif
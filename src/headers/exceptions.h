
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>
#include <exception>

class WhatCustomException : public std::exception
{
  std::string whatException;
public:
  WhatCustomException(std::string exceptionString)
  : whatException(exceptionString){}
  virtual const char* what() const throw ()
  {
       return whatException.c_str();
  }
};

class NotEnoughImagesException : public std::exception
{
public:
    virtual const char* what() const throw ()
    {
         return "Błąd: za mało obrazków do przeprowadzenia operacji.";
    }
};

class ExceptionDecodePNG : public std::exception
{
public:
    virtual const char* what() const throw ()
    {
         return "Błąd: nie udało się wczytać PNG. Niepoprawny format obrazka. Musi być to jeden z obrazków (Grayscale-1-bit, Grayscale-8-bit, Truecolor-24-bit).";
    }
};

class WrongImageType : public std::exception
{
public:
    virtual const char* what() const throw ()
    {
         return "Błąd: format obrazka jest niepoprawny, program przyjmuje tylko (Grayscale 1-bit, Grayscale 8-bit, Truecolor 24-bit).";
    }
};

class ImageAreColorfulException : public std::exception
{
public:
    virtual const char* what() const throw ()
    {
         return "Błąd: obrazki powinny być barwy szarej.";
    }
};

class ImageAreNotColorfulException : public std::exception
{
public:
    virtual const char* what() const throw ()
    {
         return "Błąd: obrazki powinny być barwny.";
    }
};

class ImageAreGreyException : public std::exception
{
public:
    virtual const char* what() const throw ()
    {
         return "Błąd: obrazki powinny być barwny.";
    }
};

class ImagesAreNotSameSizeException : public std::exception
{
public:
    virtual const char* what() const throw ()
    {
         return "Błąd: obrazki nie są tej samej wielkości.";
    }
};

class WrongPointType : public std::exception
{
public:
    virtual const char* what() const throw ()
    {
         return "Błąd: zły typ punkta.";
    }
};

#endif //EXCEPTIONS_H

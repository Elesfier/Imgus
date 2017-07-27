
#ifndef POINT_H
#define POINT_H

#include "exceptions.h"
#include <cstdint>

namespace Point
{
  struct Point_t
  {
    uint64_t x;
    uint64_t y;
  };

  enum class POINT_TYPES
  {
    BINARY,
    GRAY_SCALE,
    RGB,
    GRAY_SCALE_NORMA,
    RGB_NORMA
  };

  class PointType
  {
  protected:
    virtual void onSuccessValidation (PointType *point) = 0;
  public:
    virtual ~PointType(){}
    virtual void setBlank() = 0;
    virtual void set (PointType *point) final
    {
      if (point->type() == this->type())
      {
        this->onSuccessValidation(point);
      }
      else
      {
        throw WrongPointType();
      }
    }
    virtual POINT_TYPES type() const = 0;
  };

  class Binary : public PointType
  {
    void onSuccessValidation (PointType *point)
    {
      this->pixel = dynamic_cast<Binary*>(point)->pixel;
    }
  public:
    bool pixel;
    Binary():pixel(false){}
    Binary(bool p):pixel(p){}
    void setBlank(){ this->pixel = false; }
    Binary(Binary &binary){ this->pixel = binary.pixel; }
    POINT_TYPES type() const { return POINT_TYPES::BINARY; }
  };

  class GrayScale : public PointType
  {
    void onSuccessValidation (PointType *point)
    {
      this->scale = dynamic_cast<GrayScale*>(point)->scale;
    }
  public:
    unsigned char scale;
    GrayScale():scale(255){}
    GrayScale(unsigned char s):scale(s){}
    void setBlank(){ this->scale = 255; }
    GrayScale(GrayScale &grayScale){ this->scale = grayScale.scale; }
    POINT_TYPES type() const { return POINT_TYPES::GRAY_SCALE; }
  };

  class GrayScaleForNormalization : public PointType
  {
    void onSuccessValidation (PointType *point)
    {
      this->scale = dynamic_cast<GrayScaleForNormalization*>(point)->scale;
    }
  public:
    double scale;
    GrayScaleForNormalization():scale(255.0){}
    GrayScaleForNormalization(double s):scale(s){}
    void setBlank(){ this->scale = 255.0; }
    GrayScaleForNormalization(GrayScaleForNormalization &grayScale){ this->scale = grayScale.scale; }
    POINT_TYPES type() const { return POINT_TYPES::GRAY_SCALE_NORMA; }
  };

  class RedGreenBlue : public PointType
  {
    void onSuccessValidation (PointType *point)
    {
      RedGreenBlue RGBPoint = (*dynamic_cast<RedGreenBlue*>(point));
      this->red = RGBPoint.red;
      this->green = RGBPoint.green;
      this->blue = RGBPoint.blue;
    }
  public:
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    RedGreenBlue():red(255),green(255),blue(255){}
    RedGreenBlue(unsigned char r, unsigned char g, unsigned char b):red(r),green(g),blue(b){}
    RedGreenBlue(RedGreenBlue &redGreenBlue){
      this->red = redGreenBlue.red;
      this->green = redGreenBlue.green;
      this->blue = redGreenBlue.blue;
    }
    void setBlank(){
      this->red = 255;
      this->green = 255;
      this->blue = 255;
    }
    POINT_TYPES type() const { return POINT_TYPES::RGB; }
  };

  class RedGreenBlueForNormalization : public PointType
  {
    void onSuccessValidation (PointType *point)
    {
      RedGreenBlueForNormalization RGBPoint = (*dynamic_cast<RedGreenBlueForNormalization*>(point));
      this->red = RGBPoint.red;
      this->green = RGBPoint.green;
      this->blue = RGBPoint.blue;
    }
  public:
    double red;
    double green;
    double blue;
    RedGreenBlueForNormalization():red(255.0),green(255.0),blue(255.0){}
    RedGreenBlueForNormalization(double r, double g, double b):red(r),green(g),blue(b){}
    RedGreenBlueForNormalization(RedGreenBlueForNormalization &redGreenBlue){
      this->red = redGreenBlue.red;
      this->green = redGreenBlue.green;
      this->blue = redGreenBlue.blue;
    }
    void setBlank(){
      this->red = 255.0;
      this->green = 255.0;
      this->blue = 255.0;
    }
    POINT_TYPES type() const { return POINT_TYPES::RGB_NORMA; }
  };
}

#endif //POINT_H

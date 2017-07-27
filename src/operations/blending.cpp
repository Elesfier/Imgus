
#include "src/headers/common.h"
#include "src/headers/image.h"
#include "src/headers/operation.h"
#include "src/headers/exceptions.h"

//
// 1.3 & 2.3 Mieszanie Obrazów
//
namespace Operations
{
  class Blending : public Operation
  {
  public:

    Blending()
    {
      name = "Mieszanie Obrazów";
      fileExt = "_Mieszanie_Obrazow_";
      isMulti = true;
      isOnlyMulti = true;
      hasParams = true;
      params = {{"Współczynnik", "n0.2"}};
      disableBinary = true;
    }

    unsigned char count (double f, double s, double wsp)
    {
      unsigned char counted = double(wsp * f + (1.0 - wsp) * s);
      if (counted > 255) counted = 255;
      if (counted < 0) counted = 0;
      return counted;
    }

    // Multi Operation
    void operate (ImagePack pack, ParamsPack params)
    {
      Image::Image *first = pack[0];
      Image::Image *second = pack[1];

      const long double wsp = Common::convertToNumber(params["Współczynnik"]);
      if (wsp < 0 || wsp > 1)
        throw WhatCustomException("BŁĄD OPERACJI: potrzeba współczynnika z przedziału 0-1.");

      first->forEach <Point::GrayScale> (second,
        [this,wsp](Point::GrayScale *pt1, Point::GrayScale *pt2){
          pt1->scale = count(pt1->scale, pt2->scale, wsp);
        }
      );

      first->forEach <Point::RedGreenBlue> (second,
        [this,wsp](Point::RedGreenBlue *pt1, Point::RedGreenBlue *pt2){
          pt1->red = count(pt1->red, pt2->red, wsp);
          pt1->green = count(pt1->green, pt2->green, wsp);
          pt1->blue = count(pt1->blue, pt2->blue, wsp);
        }
      );
    }
  };
}

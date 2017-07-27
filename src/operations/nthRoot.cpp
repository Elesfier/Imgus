
#include "src/headers/common.h"
#include "src/headers/image.h"
#include "src/headers/operation.h"
#include <cmath>

//
// 1.6 & 2.6 Pierwiastkowanie Obrazu
//
namespace Operations
{
  class NthRoot : public Operation
  {
  public:

    NthRoot()
    {
      name = "Pierwiastkowanie Obrazu";
      fileExt = "_Pierwiastkowanie_Obrazu_";
      disableBinary = true;
    }

    // Single Operation
    void operate (Image::Image *img, ParamsPack params)
    {
      std::vector <unsigned char> minMax = img->MinMax();

      img->forEach<Point::GrayScale>([&](Point::GrayScale *pt){
          pt->scale = 255.0 * std::sqrt(double(pt->scale)/double(minMax[1]));
      });

      img->forEach<Point::RedGreenBlue>([&](Point::RedGreenBlue *pt){
          pt->red = 255.0 * std::sqrt(double(pt->red)/double(minMax[3]));
          pt->green = 255.0 * std::sqrt(double(pt->green)/double(minMax[4]));
          pt->blue = 255.0 * std::sqrt(double(pt->blue)/double(minMax[5]));
      });
    }
  };
}

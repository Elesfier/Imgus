
#include "src/headers/common.h"
#include "src/headers/image.h"
#include "src/headers/operation.h"
#include <cmath>
#include <vector>

//
// 1.7 & 2.7 Logarytmowanie Obrazu
//
namespace Operations
{
  class Log : public Operation
  {
  public:

    Log()
    {
      name = "Logarytmowanie Obrazu";
      fileExt = "_Logarytmowanie_Obrazu_";
      disableBinary = true;
    }

    // Single Operation
    void operate (Image::Image *img, ParamsPack params)
    {
      std::vector <unsigned char> minMax = img->MinMax();

      img->forEach<Point::GrayScale>([&](Point::GrayScale *pt){
          pt->scale = 255.0 * std::log10(1.0 + double(pt->scale))/std::log10(1.0+double(minMax[1]));
      });

      img->forEach<Point::RedGreenBlue>([&](Point::RedGreenBlue *pt){
          pt->red = 255.0 * std::log10(1.0 + double(pt->red))/std::log10(1.0+double(minMax[3]));
          pt->green = 255.0 * std::log10(1.0 + double(pt->green))/std::log10(1.0+double(minMax[4]));
          pt->blue = 255.0 * std::log10(1.0 + double(pt->blue))/std::log10(1.0+double(minMax[5]));
      });
    }
  };
}

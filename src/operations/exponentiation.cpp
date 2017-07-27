
#include "src/headers/common.h"
#include "src/headers/image.h"
#include "src/headers/operation.h"
#include <cmath>

//
// 1.4 & 2.4 Potęgowanie Obrazu
//
namespace Operations
{
  class Exponentiation : public Operation
  {
  public:

    Exponentiation()
    {
      name = "Potęgowanie Obrazu";
      fileExt = "Potegowanie_Obrazu_";
      hasParams = true;
      params = {{"Potęga", "n2"}};
      disableBinary = true;
    }

    // Single Operation
    void operate (Image::Image *img, ParamsPack params)
    {
      const uint64_t potega = Common::convertToNumber(params["Potęga"]);

      std::vector <unsigned char> minMax = img->MinMax();

      img->forEach<Point::GrayScale>([&](Point::GrayScale *pt){
          pt->scale = 255.0 * std::pow(double(pt->scale)/double(minMax[1]), potega);
      });

      img->forEach<Point::RedGreenBlue>([&](Point::RedGreenBlue *pt){
          pt->red = 255.0 * std::pow(double(pt->red)/double(minMax[3]), potega);
          pt->green = 255.0 * std::pow(double(pt->green)/double(minMax[4]), potega);
          pt->blue = 255.0 * std::pow(double(pt->blue)/double(minMax[5]), potega);
      });
    }
  };
}

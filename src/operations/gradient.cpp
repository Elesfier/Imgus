
#include "src/headers/common.h"
#include "src/headers/image.h"
#include "src/headers/operation.h"

//
// 8.3 Filtry Gradientowe
//
namespace Operations
{
  class Gradient  : public Operation
  {
  public:

    Gradient()
    {
      name = "Filtr Gradientowy";
      fileExt = "_Filtr_Gradientowy_";
      disableBinary = true;
    }

    void operate(Image::Image *img, Operations::ParamsPack params)
    {
      double highpassKernel[9] = {-1.0, -1.0, 1.0, -1.0, -2.0, 1.0, 1.0, 1.0, 1.0};

      img->morphologyOperation<Point::GrayScale>(
        [this,highpassKernel](Point::GrayScale* pixelStructure[9]) -> Point::PointType* {

          long double newValue = 0;
          for (unsigned char i = 0; i < 9; ++i)
          {
            if (pixelStructure[i])
            {
              newValue += ((highpassKernel[i])*(pixelStructure[i]->scale));
            }
          }
          if (newValue > 255) newValue = 255;
          if (newValue < 0) newValue = 0;
          return (new Point::GrayScale(newValue));
        }
      );

      img->morphologyOperation<Point::RedGreenBlue>(
        [this,highpassKernel](Point::RedGreenBlue* pixelStructure[9]) -> Point::PointType* {

          long double red = 0;
          long double green = 0;
          long double blue = 0;

          for (unsigned char i = 0; i < 9; ++i)
          {
            if(pixelStructure[i]){
               red += (highpassKernel[i]) * pixelStructure[i]->red;
               green += (highpassKernel[i]) * pixelStructure[i]->green;
               blue += (highpassKernel[i]) * pixelStructure[i]->blue;
            }
          }

          if (red > 255) red = 255;
          if (red < 0) red = 0;
          if (green > 255) green = 255;
          if (green < 0) green = 0;
          if (blue > 255) blue = 255;
          if (blue < 0) blue = 0;
          return (new Point::RedGreenBlue(red, green, blue));
        }
      );
    }
  };
}

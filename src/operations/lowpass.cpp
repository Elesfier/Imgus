
#include "src/headers/common.h"
#include "src/headers/image.h"
#include "src/headers/operation.h"

//
// 8.1 Filtr Dolnoprzepustowy
//
namespace Operations
{
  class Lowpass  : public Operation
  {
  public:

    Lowpass()
    {
      name = "Filtr Dolnoprzepustowy";
      fileExt = "_Filtr_Dolnoprzepustowy_";
      disableBinary = true;
    }

    void operate(Image::Image *img, Operations::ParamsPack params)
    {
      img->morphologyOperation<Point::GrayScale>(
        [](Point::GrayScale* pixelStructure[9]) -> Point::PointType* {

          float newValue = 0;
          for (unsigned char i = 0; i < 9; ++i)
          {
            if (pixelStructure[i]) {
              newValue += ((1.0/9.0) * pixelStructure[i]->scale);
            }
          }
          if (newValue > 255) newValue = 255;
          if (newValue < 0) newValue = 0;
          return (new Point::GrayScale(newValue));
        }
      );

      img->morphologyOperation<Point::RedGreenBlue>(
        [](Point::RedGreenBlue* pixelStructure[9]) -> Point::PointType* {

          float red = 0;
          float green = 0;
          float blue = 0;

          for (unsigned char i = 0; i < 9; ++i)
          {
            if(pixelStructure[i]){
               red += (1.0/9.0) * pixelStructure[i]->red;
               green += (1.0/9.0) * pixelStructure[i]->green;
               blue += (1.0/9.0) * pixelStructure[i]->blue;
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

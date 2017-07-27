
#include "src/headers/common.h"
#include "src/headers/image.h"
#include "src/headers/operation.h"

//
// 6.2 & 7.2 Dylatacja Obrazu
//
namespace Operations
{
  class Dilatation : public Operation
  {
  public:

    Dilatation()
    {
      name = "Dylatacja Obrazu";
      fileExt = "Dylatacja_Obrazu_";
      disableRGB = true;
    }

    void operate(Image::Image *img, ParamsPack params)
    {
        img->morphologyOperation<Point::Binary>(
          [](Point::Binary* pixelStructure[9]) -> Point::PointType* {
            for (unsigned char i = 1; i < 8; i+=2){
              if (pixelStructure[i] && pixelStructure[i]->pixel)
                return (new Point::Binary(true));
            }
            return (new Point::Binary(false));
          }
        );

        img->morphologyOperation<Point::GrayScale>(
          [](Point::GrayScale* pixelStructure[9]) -> Point::PointType* {
            unsigned char maximum = pixelStructure[4]->scale;
            for (unsigned char i = 1; i < 8; i+=2)
            {
              if(pixelStructure[i] != nullptr && pixelStructure[i]->scale > maximum)
                maximum = pixelStructure[i]->scale;
            }
            return (new Point::GrayScale(maximum));
          }
        );
    }
  };
}

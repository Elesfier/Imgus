
#include "src/headers/common.h"
#include "src/headers/image.h"
#include "src/headers/operation.h"

//
// 6.1 & 7.1 Erozja Obrazu
//
namespace Operations
{
  class Erosion : public Operation
  {
  public:

    Erosion()
    {
      name = "Erozja Obrazu";
      fileExt = "Erozja_Obrazu_";
      disableRGB = true;
    }

    void operate(Image::Image *img, ParamsPack params)
    {
        img->morphologyOperation<Point::Binary>(
          [](Point::Binary* pixelStructure[9]) -> Point::PointType* {
            unsigned char counter = 0;
            unsigned char comparison = 4;
            for (unsigned char i = 1; i < 8; i+=2){
              if (pixelStructure[i]){
                if (pixelStructure[i]->pixel == true) counter++;
              }
              else comparison--;
            }
            return (new Point::Binary((counter == comparison)?(true):(false)));
          }
        );

        img->morphologyOperation<Point::GrayScale>(
          [](Point::GrayScale* pixelStructure[9]) -> Point::PointType* {
            unsigned char minimum = pixelStructure[4]->scale;
            for (unsigned char i = 1; i < 8; i+=2)
            {
              if(pixelStructure[i] != nullptr && pixelStructure[i]->scale < minimum)
                minimum = pixelStructure[i]->scale;
            }
            return (new Point::GrayScale(minimum));
          }
        );
    }
  };
}

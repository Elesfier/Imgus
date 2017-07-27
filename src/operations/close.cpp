
#include "src/headers/common.h"
#include "src/headers/image.h"
#include "src/headers/operation.h"

//
// 6.4 & 7.4 Zamknięcie Obrazu
//
namespace Operations
{
  class Close  : public Operation
  {
  public:

    Close()
    {
      name = "Zamknięcie Obrazu";
      fileExt = "Zamknięcie_Obrazu_";
      disableRGB = true;
    }

    void operate(Image::Image *img, ParamsPack params)
    {
        //Dylatacja
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

        //Erozja
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

        //Dylatacja
        img->morphologyOperation<Point::Binary>(
          [](Point::Binary* pixelStructure[9]) -> Point::PointType* {
            for (unsigned char i = 1; i < 8; i+=2){
              if (pixelStructure[i] && pixelStructure[i]->pixel)
                return (new Point::Binary(true));
            }
            return (new Point::Binary(false));
          }
        );

        //Erozja
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
    }
  };
}

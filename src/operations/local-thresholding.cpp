
#include "src/headers/common.h"
#include "src/headers/image.h"
#include "src/headers/operation.h"

//
// 4.4 & 5.6 Progowanie Lokalne Histogramu
//
namespace Operations
{
  class LocalThresholding  : public Operation
  {
  public:

    LocalThresholding()
    {
      name = "Progowanie Lokalne";
      fileExt = "Progowanie_Lokalne_";
      disableBinary = true;
    }

    unsigned char RGBtoGrayScale (float R, float G, float B)
    {
      return (0.21*R + 0.72*G + 0.07*B);
    }

    void operate(Image::Image *img, Operations::ParamsPack params)
    {
      if (img->type() == Point::POINT_TYPES::GRAY_SCALE)
      {
        img->morphologyOperationPlus<Point::GrayScale, 7>(
          [](Point::GrayScale* pixelStructure[49]) -> Point::PointType* {

            unsigned char min = 255;
            unsigned char max = 0;

            for(int i = 0; i < 49; ++i)
            {
              if (pixelStructure[i])
              {
                if (pixelStructure[i]->scale < min)
                  min = pixelStructure[i]->scale;
                if (pixelStructure[i]->scale > max)
                  max = pixelStructure[i]->scale;
              }
            }

            if (pixelStructure[24]->scale > ((max+min)/2))
              return (new Point::GrayScale(255));
            else
              return (new Point::GrayScale(0));
          }
        );
      }

      if (img->type() == Point::POINT_TYPES::RGB)
      {
        img->morphologyOperationPlus<Point::RedGreenBlue, 7>(
          [this](Point::RedGreenBlue* pixelStructure[49]) -> Point::PointType* {

            unsigned char min = 255;
            unsigned char max = 0;

            for(int i = 0; i < 49; ++i)
            {
              if (pixelStructure[i])
              {
                unsigned char intensity = RGBtoGrayScale(pixelStructure[i]->red, pixelStructure[i]->green, pixelStructure[i]->blue);
                if (intensity < min) min = intensity;
                if (intensity > max) max = intensity;
              }
            }
            unsigned char middle = RGBtoGrayScale(pixelStructure[24]->red, pixelStructure[24]->green, pixelStructure[24]->blue);
            if (middle > ((max+min)/2))
              return (new Point::RedGreenBlue(255,255,255));
            else
              return (new Point::RedGreenBlue(0,0,0));
          }
        );
      }
    }

  };
}

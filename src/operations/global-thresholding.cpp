
#include "src/headers/common.h"
#include "src/headers/image.h"
#include "src/headers/operation.h"

//
// 4.5 & 5.7 Progowanie Globalne Histogramu
//
namespace Operations
{
  class GlobalThresholding : public Operation
  {
  public:

    GlobalThresholding()
    {
      name = "Progowanie Globalne";
      fileExt = "Progowanie_Globalne_";
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
        unsigned char min = 255;
        unsigned char max = 0;
        img->forEach <Point::GrayScale> ([&]( Point::GrayScale *pt ){
            if (min > pt->scale) min = pt->scale;
            if (max < pt->scale) max = pt->scale;
        });
        unsigned char thresholding = (max+min)/2;
        img->forEach <Point::GrayScale> ([thresholding]( Point::GrayScale *pt ){
            if (pt->scale > thresholding)
              pt->scale = 255;
            else
              pt->scale = 0;
        });
      }

      if (img->type() == Point::POINT_TYPES::RGB)
      {
        unsigned char min = 255;
        unsigned char max = 0;
        img->forEach <Point::RedGreenBlue> ([this,&min,&max]( Point::RedGreenBlue *pt ){
            unsigned char intensity = RGBtoGrayScale(pt->red, pt->green, pt->blue);
            if (min > intensity) min = intensity;
            if (max < intensity) max = intensity;
        });
        unsigned char thresholding = (max+min)/2;
        img->forEach <Point::RedGreenBlue> ([this,thresholding]( Point::RedGreenBlue *pt ){
            unsigned char intensity = RGBtoGrayScale(pt->red, pt->green, pt->blue);
            if (intensity > thresholding)
            {
              pt->red = 255;
              pt->green = 255;
              pt->blue = 255;
            }
            else
            {
              pt->red = 0;
              pt->green = 0;
              pt->blue = 0;
            }
        });

      }
    }

  };
}

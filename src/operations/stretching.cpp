
#include "src/headers/common.h"
#include "src/headers/image.h"
#include "src/headers/operation.h"
#include <algorithm>

//
// 4.3 & 5.3 Rozciąganie Histogramu
//
namespace Operations
{
  class Stretching  : public Operation
  {
  public:

    Stretching()
    {
      name = "Rozciąganie Histogramu";
      fileExt = "Rozciąganie_Histogramu_";
      disableBinary = true;
    }

    void operate(Image::Image *img, Operations::ParamsPack params)
    {
      if (img->type() == Point::POINT_TYPES::GRAY_SCALE)
      {
        unsigned char min = 255;
        unsigned char max = 0;

        img->forEach <Point::GrayScale> ([&]( Point::GrayScale *pt ){
            if (pt->scale < min) min = pt->scale;
            if (pt->scale > max) max = pt->scale;
        });

        img->forEach <Point::GrayScale> ([&]( Point::GrayScale *pt ){
            pt->scale = 255.0*(((double)(pt->scale-min))/(max-min));
        });
      }

      if (img->type() == Point::POINT_TYPES::RGB)
      {
        unsigned char min[] = {255, 255, 255};
        unsigned char max[] = {0, 0, 0};

        img->forEach <Point::RedGreenBlue> ([&]( Point::RedGreenBlue *pt ){
            if (pt->red < min[0]) min[0] = pt->red;
            if (pt->red > max[0]) max[0] = pt->red;
            if (pt->green < min[1]) min[1] = pt->green;
            if (pt->green > max[1]) max[1] = pt->green;
            if (pt->blue < min[2]) min[2] = pt->blue;
            if (pt->blue > max[2]) max[2] = pt->blue;
        });

        img->forEach <Point::RedGreenBlue> ([&]( Point::RedGreenBlue *pt ){
            pt->red = 255.0*(((double)(pt->red-min[0]))/(max[0]-min[0]));
            pt->green = 255.0*(((double)(pt->green-min[1]))/(max[1]-min[1]));
            pt->blue = 255.0*(((double)(pt->blue-min[2]))/(max[2]-min[2]));
        });

      }
    }

  };
}

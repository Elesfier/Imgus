
#include "src/headers/common.h"
#include "src/headers/image.h"
#include "src/headers/operation.h"

//
// 5.5 Progowanie Wieloprogowe Histogramu
//
namespace Operations
{
  class MultiThresholding  : public Operation
  {
  public:

    MultiThresholding()
    {
      name = "Progowanie Wieloprogowe";
      fileExt = "Progowanie_Wieloprogowe_";
      hasParams = true;
      params = {{"T1", "n40"}, {"T2", "n200"}};
      disableBinary = true;
      disableGrayScale = true;
    }

    unsigned char RGBtoGrayScale (float R, float G, float B)
    {
      return (0.21*R + 0.72*G + 0.07*B);
    }

    void operate(Image::Image *img, Operations::ParamsPack params)
    {
        const uint64_t T1 = Common::convertToNumber(params["T1"]);
        const uint64_t T2 = Common::convertToNumber(params["T2"]);

        img->forEach<Point::RedGreenBlue>([this,T1,T2](Point::RedGreenBlue *pt){
            unsigned char intensity = RGBtoGrayScale(pt->red, pt->green, pt->blue);
            if (intensity < T1)
            {
              pt->red = 255;
              pt->green = 0;
              pt->blue = 0;
            }
            else if (T1 < intensity < T2)
            {
              pt->red = 0;
              pt->green = 255;
              pt->blue = 0;
            }
            else if (intensity > T2)
            {
              pt->red = 0;
              pt->green = 0;
              pt->blue = 255;
            }
        });
    }
  };
}

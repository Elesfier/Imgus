
#include "src/headers/common.h"
#include "src/headers/image.h"
#include "src/headers/operation.h"
#include "src/headers/window.h"

//
// 4.1 & 5.1 Obliczanie Histogramu / Wyświetlanie Histogramu
//
namespace Operations
{
  class Histogram  : public Operation
  {
  public:

    Histogram()
    {
      name = "Wyświetlanie Histogramu";
      fileExt = "Wyświetlony_Histogram_";
      disableBinary = true;
    }

    void operate(Image::Image *img, Operations::ParamsPack params)
    {
        if (img->type() == Point::POINT_TYPES::GRAY_SCALE)
        {
          MAIN_WINDOW_TYPE::generateChart( "Szary", Image::getGreyCounter<>(img));
        }

        if (img->type() == Point::POINT_TYPES::RGB)
        {
          Image::RGBCounter <> counter = Image::getRGBCounter<>(img);
          MAIN_WINDOW_TYPE::generateChart( "Czerwony", counter.red );
          MAIN_WINDOW_TYPE::generateChart( "Zielony", counter.green );
          MAIN_WINDOW_TYPE::generateChart( "Niebieski", counter.blue );
        }
    }

  };
}

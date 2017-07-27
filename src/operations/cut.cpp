
#include "src/headers/common.h"
#include "src/headers/image.h"
#include "src/headers/operation.h"

//
// 3.5. Wycinanie Fragmentu Obrazu
//
namespace Operations
{
  class Cut : public Operation
  {
  public:

    Cut() : Operation()
    {
      name = "Wycinanie Fragmentu Obrazu";
      fileExt = "Wyciety_Fragment_Obraz_";
      hasParams = true;
      params = {{"Heigth", "n10"}, {"Width", "n10"}, {"X", "n0"}, {"Y", "n0"}};
    }

    void operate (Image::Image *img, Operations::ParamsPack params)
    {
      const uint64_t startX = Common::convertToNumber(params["X"]);
      const uint64_t startY = Common::convertToNumber(params["Y"]);
      const uint64_t heigth = Common::convertToNumber(params["Heigth"]);
      const uint64_t width = Common::convertToNumber(params["Width"]);

      img->cutFragment(width, heigth, startX, startY);
    }

  };
}

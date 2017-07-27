
#include "src/headers/common.h"
#include "src/headers/image.h"
#include "src/headers/operation.h"

//
// 3.6. Kopiowanie Fragmentu Obrazu
//
namespace Operations
{
  class Copy : public Operation
  {
  public:

    Copy()
    {
      name = "Kopiowanie Fragmentu Obrazka";
      fileExt = "Kopiuj_Wklej_Obraz_";
      hasParams = true;
      params = {
        {"Heigth", "n20"}, {"Width", "n20"}, {"X", "n0"},
        {"Y", "n0"}, {"X2", "n30"}, {"Y2", "n30"}
      };
    }

    void operate(Image::Image *img, Operations::ParamsPack params)
    {
      const uint64_t startX = Common::convertToNumber(params["X"]);
      const uint64_t startY = Common::convertToNumber(params["Y"]);
      const uint64_t heigth = Common::convertToNumber(params["Heigth"]);
      const uint64_t width = Common::convertToNumber(params["Width"]);
      const uint64_t pasteX = Common::convertToNumber(params["X2"]);
      const uint64_t pasteY = Common::convertToNumber(params["Y2"]);

      img->copyFragment(img->cutFragment(width, heigth, startX, startY), pasteX, pasteY);
    }
  };
}

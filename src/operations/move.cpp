
#include "src/headers/common.h"
#include "src/headers/image.h"
#include "src/headers/operation.h"

//
// 3.1. Przemieszczenie Obrazu
//
namespace Operations
{
  class Move : public Operation
  {
  public:

    Move()
    {
      name = "Przemieszczenie Obrazu";
      fileExt = "Przemieszczenie_Obrazu_";
      hasParams = false;
      params = { {"X", "n30"}, {"Y", "n30"} };
    }

    void operate(Image::Image *img, Operations::ParamsPack params)
    {
      const uint64_t moveX = Common::convertToNumber(params["X"]);
      const uint64_t moveY = Common::convertToNumber(params["Y"]);

      img->geometricAction(
        [moveX,moveY] (uint64_t x, uint64_t y) -> Point::Point_t
        {
          return Point::Point_t { x + moveX, y + moveY };
        }
      );
    }

  };
}

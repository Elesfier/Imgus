
#include "src/headers/common.h"
#include "src/headers/image.h"
#include "src/headers/operation.h"
#include <algorithm>

//
// 8.4 Filtry Medianowy
//
namespace Operations
{
  class Mediana  : public Operation
  {
  public:

    Mediana()
    {
      name = "Filtr Medianowy";
      fileExt = "_Filtr_Medianowy_";
      disableBinary = true;
    }

    void operate(Image::Image *img, Operations::ParamsPack params)
    {
      img->morphologyOperation<Point::GrayScale>(
        [](Point::GrayScale* pixelStructure[9]) -> Point::PointType* {

          unsigned char median = 0;
          std::vector <unsigned char> vec;

          for (unsigned char i = 0; i < 9; ++i)
            if (pixelStructure[i]) vec.push_back(pixelStructure[i]->scale);

          sort(vec.begin(), vec.end());

          if (vec.size() % 2 == 0)
          {
            median = (vec[vec.size() / 2 - 1] + vec[vec.size() / 2]) / 2;
          }
          else
          {
            median = vec[vec.size() / 2];
          }

          return (new Point::GrayScale(median));
        }
      );

      img->morphologyOperation<Point::RedGreenBlue>(
        [](Point::RedGreenBlue* pixelStructure[9]) -> Point::PointType* {

          unsigned char median[3] = {0, 0, 0};
          std::vector <unsigned char> vec[3];

          for (unsigned char i = 0; i < 9; ++i)
            for (unsigned char j = 0; j < 3; ++j)
              if (pixelStructure[i]){
                if (j == 0) vec[j].push_back(pixelStructure[i]->red);
                if (j == 1) vec[j].push_back(pixelStructure[i]->green);
                if (j == 2) vec[j].push_back(pixelStructure[i]->blue);
              }

          for (unsigned char i = 0; i < 3; ++i)
            sort(vec[i].begin(), vec[i].end());

          for (unsigned char j = 0; j < 3; ++j)
            if (vec[j].size() % 2 == 0)
            {
              median[j] = (vec[j][vec[j].size() / 2 - 1] + vec[j][vec[j].size() / 2]) / 2;
            }
            else
            {
              median[j] = vec[j][vec[j].size() / 2];
            }

          return (new Point::RedGreenBlue(median[0], median[1], median[2]));
        }
      );
    }
  };
}

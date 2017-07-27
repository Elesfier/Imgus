
#include "src/headers/common.h"
#include "src/headers/image.h"
#include "src/headers/operation.h"
#include <cmath>

//
// 1.5 & 2.5 Dzielenie Obrazów
//
namespace Operations
{
  class Division : public Operation
  {

    public:

      Division()
      {
        name = "Dzielenie Obrazka/ów";
        fileExt = "_Dzielenie_Obrazka_";
        isMulti = true;
        hasParams = true;
        params = {{"Dzielnik", "n4"}};
        disableBinary = true;
      }

      unsigned char div (unsigned char f, int s)
      {
        return std::floor(float(f)/s);
      }

      // Single Operation
      void operate (Image::Image *img, ParamsPack params)
      {
        const uint64_t dzielnik = Common::convertToNumber(params["Dzielnik"]);

        img->forEach<Point::GrayScale>([this,dzielnik](Point::GrayScale *pt){
            pt->scale = div(pt->scale, dzielnik);
        });

        img->forEach<Point::RedGreenBlue>([this,dzielnik](Point::RedGreenBlue *pt){
            pt->red = div(pt->red, dzielnik);
            pt->green = div(pt->green, dzielnik);
            pt->blue = div(pt->blue, dzielnik);
        });
      }

      // Multi Operation
      void operate (ImagePack pack, ParamsPack params)
      {
        /*
        Image::Image *first = pack[0];
        Image::Image *second = pack[1];

        first->forEach <Point::GrayScale> (second,
          [&](Point::GrayScale *pt1, Point::GrayScale *pt2){
            pt1->scale = double(pt1->scale)/double((pt2->scale != 0)?(pt2->scale):(1.0));
          }
        );

        first->forEach <Point::RedGreenBlue> (second,
          [&](Point::RedGreenBlue *pt1, Point::RedGreenBlue *pt2){
            pt1->red = double(pt1->red)/double((pt2->red != 0)?(pt2->red):(1.0));
            pt1->green = double(pt1->green)/double((pt2->green != 0)?(pt2->green):(1.0));
            pt1->blue = double(pt1->blue)/double((pt2->blue != 0)?(pt2->blue):(1.0));
          }
        );*/

        pack[0]->normalization<
          Point::POINT_TYPES::GRAY_SCALE,
          Point::POINT_TYPES::GRAY_SCALE_NORMA,
          Point::GrayScale,
          Point::GrayScaleForNormalization
        >(pack[0], pack[1],
        [](Point::GrayScaleForNormalization* pt1, Point::GrayScaleForNormalization* pt2){

          pt1->scale = pt1->scale / pt2->scale;

        },
        [](Point::RedGreenBlueForNormalization* pt1, Point::RedGreenBlueForNormalization* pt2){});

        pack[0]->normalization<
          Point::POINT_TYPES::RGB,
          Point::POINT_TYPES::RGB_NORMA,
          Point::RedGreenBlue,
          Point::RedGreenBlueForNormalization
        >(pack[0], pack[1],
        [](Point::GrayScaleForNormalization* pt1, Point::GrayScaleForNormalization* pt2){},
        [](Point::RedGreenBlueForNormalization* pt1, Point::RedGreenBlueForNormalization* pt2){

          pt1->red = pt1->red / pt2->red;
          pt1->green = pt1->green / pt2->green;
          pt1->blue = pt1->blue / pt2->blue;
        });

        //first->normalization();
      }
  };
}


#include "src/headers/common.h"
#include "src/headers/image.h"
#include "src/headers/operation.h"

//
// 1.1 & 2.1 Sumowanie Obrazów
//
namespace Operations
{
  class Sum : public Operation
  {

  public:

    Sum()
    {
      name = "Sumowanie Obrazka/ów";
      fileExt = "_Sumowanie_Obrazka_";
      isMulti = true;
      hasParams = true;
      params = {{"Stała", "n40"}};
      disableBinary = true;
    }

    unsigned char sum (unsigned char f, signed short s)
    {
      unsigned char su = f + s;
      if (s < 0)
        { if (su > f) su = 0; }
      else
        { if (su < f) su = 255; }
      return (su);
    }

    // Single Operation
    void operate (Image::Image *img, ParamsPack params)
    {
      const int64_t stala = Common::convertToNumber(params["Stała"]);

      img->forEach<Point::GrayScale>([this,stala](Point::GrayScale *pt){
          pt->scale = sum(pt->scale, stala);
      });

      img->forEach<Point::RedGreenBlue>([this,stala](Point::RedGreenBlue *pt){
          pt->red = sum(pt->red, stala);
          pt->green = sum(pt->green, stala);
          pt->blue = sum(pt->blue, stala);
      });
    }

    // Multi Operation
    void operate (ImagePack pack, ParamsPack params)
    {

      pack[0]->normalization<
        Point::POINT_TYPES::GRAY_SCALE,
        Point::POINT_TYPES::GRAY_SCALE_NORMA,
        Point::GrayScale,
        Point::GrayScaleForNormalization
      >(pack[0], pack[1],
      [](Point::GrayScaleForNormalization* pt1, Point::GrayScaleForNormalization* pt2){

        pt1->scale = pt1->scale + pt2->scale;

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

        pt1->red = pt1->red + pt2->red;
        pt1->green = pt1->green + pt2->green;
        pt1->blue = pt1->blue + pt2->blue;
      });

      /*Image::Image *first = pack[0];
      Image::Image *second = pack[1];

      first->forEach <Point::GrayScale> (second,
        [this](Point::GrayScale *pt1, Point::GrayScale *pt2){
          pt1->scale = sum(pt1->scale, pt2->scale);
        }
      );

      first->forEach <Point::RedGreenBlue> (second,
        [this](Point::RedGreenBlue *pt1, Point::RedGreenBlue *pt2){
          pt1->red = sum(pt1->red, pt2->red);
          pt1->green = sum(pt1->green, pt2->green);
          pt1->blue = sum(pt1->blue, pt2->blue);
        }
      );*/

      //first->normalization();
    }

  };
}

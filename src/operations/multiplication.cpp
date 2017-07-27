
#include "src/headers/common.h"
#include "src/headers/image.h"
#include "src/headers/operation.h"
#include <iostream>

//
// 1.2 & 2.2 Mnożenie Obrazów
//
namespace Operations
{
  class Multiplication : public Operation
  {
  public:

    Multiplication()
    {
      name = "Mnożenie Obrazka/ów";
      fileExt = "_Mnożenie_Obrazka_";
      isMulti = true;
      hasParams = true;
      params = {{"Mnożnik", "n2"}};
      disableBinary = true;
    }

    unsigned char multi (double f, double s)
    {
      return (f*s > 255)?(255):(f*s);
    }

    // Single Operation
    void operate (Image::Image *img, ParamsPack params)
    {
      const uint64_t mnoznik = Common::convertToNumber(params["Mnożnik"]);

      img->forEach<Point::GrayScale>([this,mnoznik](Point::GrayScale *pt){
          pt->scale = multi(pt->scale, mnoznik);
      });

      img->forEach<Point::RedGreenBlue>([this,mnoznik](Point::RedGreenBlue *pt){
          pt->red = multi(pt->red, mnoznik);
          pt->green = multi(pt->green, mnoznik);
          pt->blue = multi(pt->blue, mnoznik);
      });
    }

    // Multi Operation
    void operate (ImagePack pack, ParamsPack params)
    {
      //Image::Image *f = pack[0];
      //Image::Image *s = pack[1];

      pack[0]->normalization<
        Point::POINT_TYPES::GRAY_SCALE,
        Point::POINT_TYPES::GRAY_SCALE_NORMA,
        Point::GrayScale,
        Point::GrayScaleForNormalization
      >(pack[0], pack[1],
      [](Point::GrayScaleForNormalization* pt1, Point::GrayScaleForNormalization* pt2){

        pt1->scale = pt1->scale * pt2->scale;

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
        
        pt1->red = pt1->red * pt2->red;
        pt1->green = pt1->green * pt2->green;
        pt1->blue = pt1->blue * pt2->blue;
      });

      /*first->forEach <Point::GrayScale> (second,
        [this](Point::GrayScale *pt1, Point::GrayScale *pt2){
          pt1->scale = multi(pt1->scale, pt2->scale);
        }
      );*/

      /*first->forEach <Point::RedGreenBlue> (second,
        [this](Point::RedGreenBlue *pt1, Point::RedGreenBlue *pt2){
          pt1->red = multi(pt1->red, pt2->red);
          pt1->green = multi(pt1->green, pt2->green);
          pt1->blue = multi(pt1->blue, pt2->blue);
        }
      );*/

      //first->normalization();
    }
  };
}

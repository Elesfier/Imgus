
#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <functional>
#include "common.h"
#include "point.h"
#include <iostream>
#include <cmath>

namespace Image
{
  typedef std::function<void(Point::PointType *point)> lambdaForEachPoint_t;
  typedef std::function<Point::Point_t(uint64_t, uint64_t)> lambdaForEachGeoPoint_t;

  class TemporaryImage
  {
    std::vector<std::vector<Point::PointType*>> temporaryImage;

  public:
    const uint64_t height;
    const uint64_t width;
    Point::POINT_TYPES pointType;

    TemporaryImage(
      const uint64_t h,
      const uint64_t w,
      Point::POINT_TYPES pointt
    ) : height(h), width(w), pointType(pointt)
    {

      temporaryImage.resize(h);
      for(auto &vec : temporaryImage)
      {
        vec.resize(w);
        for(auto &pt : vec)
        {
          if (pointType == Point::POINT_TYPES::BINARY)
          {
            pt = new Point::Binary();
          }
          else if (pointType == Point::POINT_TYPES::GRAY_SCALE)
          {
            pt = new Point::GrayScale();
          }
          else if (pointType == Point::POINT_TYPES::RGB)
          {
            pt = new Point::RedGreenBlue();
          }
          else if (pointType == Point::POINT_TYPES::RGB_NORMA)
          {
            pt = new Point::RedGreenBlueForNormalization();
          }
          else if (pointType == Point::POINT_TYPES::GRAY_SCALE_NORMA)
          {
            pt = new Point::GrayScaleForNormalization();
          }
          else
          {
            pt = nullptr;
          }
        }
      }
    }

    ~TemporaryImage()
    {
      //WHY dlaczego nie wolno kasować pamięci w vector
      /*for(auto &vec : this->temporaryImage)
      {
        for(auto &pt : vec)
        {
          if(pt) delete pt;
        }
      }*/
    }

    template <typename PixelType>
    void forEach (
      TemporaryImage anotherTemporaryImage,
      std::function<void(PixelType* firstPixel, PixelType* secondPixel)> lambda
    ){
      for (uint64_t y = 0; y < height; ++y)
      {
        for (uint64_t x = 0; x < width; ++x)
        {
          PixelType* pi = dynamic_cast<PixelType*>((*this)(x, y));
          PixelType* pi2 = dynamic_cast<PixelType*>((anotherTemporaryImage)(x, y));
          if (pi && pi2)
          {
            lambda(pi, pi2);
          }
          else
          {
            return;
          }
        }
      }
    }

    Point::PointType* operator () (uint64_t x, uint64_t y)
    {
        return temporaryImage[y][x];
    }

    Point::PointType* operator () (Point::Point_t point)
    {
        return temporaryImage[point.y][point.x];
    }

  };

  class Image
  {
  protected:
      const Common::String extension;
      Common::String fileName;
      Common::String types;
      TemporaryImage *tmpImg;
      unsigned height;
      unsigned width;
  public:
      Image(Common::String fn, Common::String ext) : fileName(fn), extension(ext){}
      virtual ~Image(){}
      virtual void save() = 0;
      virtual void save(Common::String fileName) = 0;

      Point::PointType* get(uint64_t x, uint64_t y)
      {
        if (x > width || y > height) return nullptr;
        else return (*tmpImg)(x, y);
      }

      Point::PointType* operator()(uint64_t x, uint64_t y)
      {
        if (x > width || y > height) return nullptr;
        else return (*tmpImg)(x, y);
      }

      Point::PointType* operator()(Point::Point_t point)
      {
        if (point.x > width || point.y > height) return nullptr;
        else return (*tmpImg)(point.x, point.y);
      }

      Common::String getExtension() const
      {
          return this->extension;
      }

      template <typename PixelType, int PixelStructureSize = 3>
      void morphologyOperationPlus (
        std::function <Point::PointType*(PixelType* pixelStructure[PixelStructureSize*PixelStructureSize])> lambda
      ){
        PixelType pixelTellsWhatType;
        TemporaryImage newMorphologyImage(height, width, pixelTellsWhatType.type());
        struct Pointer { int x; int y; };

        int middleIndex = std::floor(((double)(PixelStructureSize*PixelStructureSize))/2);
        int basicAligment = std::floor((double(PixelStructureSize)/2));

        Pointer morPoints[PixelStructureSize*PixelStructureSize];

        int aliX = (-1)*basicAligment-1;
        int aliY = basicAligment;

        for (int i = 0; i < PixelStructureSize*PixelStructureSize; ++i)
        {
          aliX++;
          morPoints[i] = {aliX, aliY};
          if (aliX == basicAligment)
          {
            aliX = (-1)*basicAligment-1;
            aliY--;
          }
        }

        auto morHelper = [this](uint32_t x, uint32_t y, Pointer pt) -> PixelType* {
          if (x+pt.x >= 0 && x+pt.x < width && y+pt.y >= 0 && y+pt.y < height)
            return dynamic_cast<PixelType*>((*tmpImg)(x+pt.x, y+pt.y));
          else
            return nullptr;
        };
        for (uint64_t y = 0; y < height; ++y)
        {
          for (uint64_t x = 0; x < width; ++x)
          {
            PixelType* pixelStructure[PixelStructureSize*PixelStructureSize];
            if (pixelStructure[middleIndex] = dynamic_cast<PixelType*>((*tmpImg)(x, y)));
            else return;

            for (unsigned char i = 0; i < PixelStructureSize*PixelStructureSize; ++i)
            {
              if (i != middleIndex)
              {
                pixelStructure[i] = morHelper(x, y, morPoints[i]);
              }
            }
            newMorphologyImage(x, y)->set(lambda(pixelStructure));
          }
        }
        this->copyFragment(newMorphologyImage);
      }

      template <typename PixelType>
      void morphologyOperation (
        std::function <Point::PointType*(PixelType* pixelStructure[9])> lambda
      ){
        PixelType pixelTellsWhatType;
        TemporaryImage newMorphologyImage(height, width, pixelTellsWhatType.type());
        struct Pointer { int x; int y; };
        Pointer morPoints[9] = {
          {-1, 1}, {0, 1}, {1, 1}, {-1,0}, {0, 0},
          {1, 0}, {-1,-1}, {0,-1}, {1,-1}
        };
        auto morHelper = [this](uint32_t x, uint32_t y, Pointer pt) -> PixelType* {
          if (x+pt.x >= 0 && x+pt.x < width && y+pt.y >= 0 && y+pt.y < height)
            return dynamic_cast<PixelType*>((*tmpImg)(x+pt.x, y+pt.y));
          else
            return nullptr;
        };
        for (uint64_t y = 0; y < height; ++y)
        {
          for (uint64_t x = 0; x < width; ++x)
          {
            PixelType* pixelStructure[9];
            if (pixelStructure[4] = dynamic_cast<PixelType*>((*tmpImg)(x, y)));
            else return;

            for (unsigned char i = 0; i < 9; ++i)
            {
              if (i != 4)
              {
                pixelStructure[i] = morHelper(x, y, morPoints[i]);
              }
            }
            newMorphologyImage(x, y)->set(lambda(pixelStructure));
          }
        }
        this->copyFragment(newMorphologyImage);
      }

      template <typename PixelType>
      void forEach (std::function<void(PixelType* pixel)> lambda)
      {
        for (uint64_t y = 0; y < height; ++y)
        {
          for (uint64_t x = 0; x < width; ++x)
          {
            if (PixelType* pi = dynamic_cast<PixelType*>((*tmpImg)(x, y)))
            {
              lambda(pi);
            }
            else
            {
              return;
            }
          }
        }
      }

      template <typename PixelType>
      void forEach (
        Image *anotherImage,
        std::function<void(PixelType* firstPixel, PixelType* secondPixel)> lambda
      ){
        for (uint64_t y = 0; y < height; ++y)
        {
          for (uint64_t x = 0; x < width; ++x)
          {
            PixelType* pi = dynamic_cast<PixelType*>((*tmpImg)(x, y));
            PixelType* pi2 = dynamic_cast<PixelType*>((*anotherImage)(x, y));
            if (pi && pi2)
            {
              lambda(pi, pi2);
            }
            else
            {
              return;
            }
          }
        }
      }

      Point::POINT_TYPES type()
      {
          if (types == "binary")
          {
            return Point::POINT_TYPES::BINARY;
          }
          else if (types == "gray")
          {
            return Point::POINT_TYPES::GRAY_SCALE;
          }
          else if (types == "color")
          {
            return Point::POINT_TYPES::RGB;
          }
      }

      uint64_t getHeight() const
      {
          return static_cast<uint64_t>(this->height);
      }

      uint64_t getWidth() const
      {
          return static_cast<uint64_t>(this->width);
      }



      virtual bool notSame (Image *img)
      {
        return (
          (this->getHeight() != img->getHeight()) ||
          (this->getWidth() != img->getWidth()) ||
          (this->type() != img->type())
        );
      }

      Point::PointType* cutPixel(Point::Point_t point)
      {
        Point::PointType *cutted;
        if ((*tmpImg)(point)->type() == Point::POINT_TYPES::BINARY)
        {
          cutted = new Point::Binary();
        }
        else if ((*tmpImg)(point)->type() == Point::POINT_TYPES::GRAY_SCALE)
        {
          cutted = new Point::GrayScale();
        }
        else if ((*tmpImg)(point)->type() == Point::POINT_TYPES::RGB)
        {
          cutted = new Point::RedGreenBlue();
        }
        cutted->set((*tmpImg)(point));
        ((*tmpImg)(point))->setBlank();
        return cutted;
      }

      virtual TemporaryImage cutFragment(
          uint64_t w = 0,
          uint64_t h = 0,
          uint64_t x = 0,
          uint64_t y = 0
      ){

          uint64_t startX = x;
          if (this->getHeight() < h) h = this->getHeight();
          if (this->getWidth() < w) w = this->getWidth();
          h = h + y;
          w = w + x;

          TemporaryImage tmpImg(h, w, this->type());

          for (; y < h; ++y)
          {
            for (x = startX; x < w; ++x)
            {
              tmpImg(x, y)->set(this->cutPixel(Point::Point_t{x, y}));
              Point::RedGreenBlue* rgb = dynamic_cast<Point::RedGreenBlue*>(tmpImg(x, y));
            }
          }

          return tmpImg;
      }

      virtual void copyFragment(
          TemporaryImage tmpImg,
          uint64_t startX = 0,
          uint64_t startY = 0
      ) final {

          uint64_t h = std::min(tmpImg.height + startY, getHeight());
          uint64_t w = std::min(tmpImg.width + startX, getWidth());

          uint64_t x;
          uint64_t y;

          for (y = startY; y < h; ++y)
          {
            for (x = startX; x < w; ++x)
            {
              this->get(x, y)->set(tmpImg(x - startX, y - startY));
            }
          }
      }

      std::vector <unsigned char> MinMax()
      {
        std::vector <unsigned char> minMax;
        if (this->type() == Point::POINT_TYPES::GRAY_SCALE)
        {
          minMax.push_back(255);
          minMax.push_back(0);
          forEach<Point::GrayScale>([&](Point::GrayScale *pt){
            if (pt->scale < minMax[0]) minMax[0] = pt->scale;
            if (pt->scale > minMax[1]) minMax[1] = pt->scale;
          });
        }
        else if (this->type() == Point::POINT_TYPES::RGB)
        {
          minMax.push_back(255);
          minMax.push_back(255);
          minMax.push_back(255);
          minMax.push_back(0);
          minMax.push_back(0);
          minMax.push_back(0);
          forEach<Point::RedGreenBlue>([&](Point::RedGreenBlue *pt){
              if (pt->red < minMax[0]) minMax[0] = pt->red;
              if (pt->green < minMax[1]) minMax[1] = pt->green;
              if (pt->blue < minMax[2]) minMax[2] = pt->blue;
              if (pt->red > minMax[3]) minMax[3] = pt->red;
              if (pt->green > minMax[4]) minMax[4] = pt->green;
              if (pt->blue > minMax[5]) minMax[5] = pt->blue;
          });
        }
        return minMax;
      }

      template <
        Point::POINT_TYPES TType,
        Point::POINT_TYPES NTType,
        typename NormalType,
        typename NormalizationType
      >
      void normalization(
        Image *f,
        Image *s,
        std::function<void(Point::GrayScaleForNormalization* firstPixel, Point::GrayScaleForNormalization* secondPixel)> lambdaGray,
        std::function<void(Point::RedGreenBlueForNormalization* firstPixel, Point::RedGreenBlueForNormalization* secondPixel)> lambdaRGB
      ){
        TemporaryImage first(f->getHeight(), f->getWidth(), NTType);
        TemporaryImage second(s->getHeight(), s->getWidth(), NTType);

        if (TType == Point::POINT_TYPES::GRAY_SCALE)
        {
          for (int y = 0; y < f->getHeight(); ++y)
          {
            for (int x = 0; x < f->getWidth(); ++x)
            {
              Point::GrayScaleForNormalization* pt1 = dynamic_cast<Point::GrayScaleForNormalization*>(first(x, y));
              Point::GrayScale* ptIn1 = dynamic_cast<Point::GrayScale*>((*f)(x, y));
              Point::GrayScaleForNormalization* pt2 = dynamic_cast<Point::GrayScaleForNormalization*>(second(x, y));
              Point::GrayScale* ptIn2 = dynamic_cast<Point::GrayScale*>((*s)(x, y));
              if (pt1 && ptIn1 && pt2 && ptIn2)
              {
                pt1->scale = ptIn1->scale;
                pt2->scale = ptIn2->scale;
              }
            }
          }
        }
        else if (TType == Point::POINT_TYPES::RGB)
        {
          for (int y = 0; y < f->getHeight(); ++y)
          {
            for (int x = 0; x < f->getWidth(); ++x)
            {
              Point::RedGreenBlueForNormalization* pt1 = dynamic_cast<Point::RedGreenBlueForNormalization*>(first(x, y));
              Point::RedGreenBlue* ptIn1 = dynamic_cast<Point::RedGreenBlue*>((*f)(x, y));
              Point::RedGreenBlueForNormalization* pt2 = dynamic_cast<Point::RedGreenBlueForNormalization*>(second(x, y));
              Point::RedGreenBlue* ptIn2 = dynamic_cast<Point::RedGreenBlue*>((*s)(x, y));
              if (pt1 && ptIn1 && pt2 && ptIn2)
              {
                pt1->red = ptIn1->red;
                pt1->green = ptIn1->green;
                pt1->blue = ptIn1->blue;
                pt2->red = ptIn2->red;
                pt2->green = ptIn2->green;
                pt2->blue = ptIn2->blue;
              }
            }
          }
        }

        long double minOld = 255;
        long double maxOld = 0;

        long double minRedOld = 255;
        long double maxRedOld = 0;
        long double minGreenOld = 255;
        long double maxGreenOld = 0;
        long double minBlueOld = 255;
        long double maxBlueOld = 0;

        if (TType == Point::POINT_TYPES::GRAY_SCALE)
        {
          first.forEach<Point::GrayScaleForNormalization>(second,
            [&](Point::GrayScaleForNormalization* pt1, Point::GrayScaleForNormalization* pt2){
              lambdaGray(pt1, pt2);
              if (minOld > pt1->scale) minOld = pt1->scale;
              if (maxOld < pt1->scale) maxOld = pt1->scale;
            }
          );
        }
        else if (TType == Point::POINT_TYPES::RGB)
        {
          first.forEach<Point::RedGreenBlueForNormalization>(second,
            [&](Point::RedGreenBlueForNormalization* pt1, Point::RedGreenBlueForNormalization* pt2){
              lambdaRGB(pt1, pt2);
              if (minRedOld > pt1->red) minRedOld = pt1->red;
              if (minGreenOld > pt1->green) minGreenOld = pt1->green;
              if (minBlueOld > pt1->blue) minBlueOld = pt1->blue;
              if (maxRedOld < pt1->red) maxRedOld = pt1->red;
              if (maxGreenOld < pt1->green) maxGreenOld = pt1->green;
              if (maxBlueOld < pt1->blue) maxBlueOld = pt1->blue;
            }
          );
        }

        long double rangeOld = maxOld - minOld;

        long double rangeRedOld = maxRedOld - minRedOld;
        long double rangeGreenOld = maxGreenOld - minGreenOld;
        long double rangeBlueOld = maxBlueOld - minBlueOld;

        long double minNew = 0;
        long double maxNew = 255;
        long double rangeNew = maxNew - minNew;

        if (TType == Point::POINT_TYPES::GRAY_SCALE)
        {
          for (int y = 0; y < f->getHeight(); ++y)
          {
            for (int x = 0; x < f->getWidth(); ++x)
            {
              Point::GrayScaleForNormalization* pt = dynamic_cast<Point::GrayScaleForNormalization*>(first(x, y));
              Point::GrayScale* ptIn = dynamic_cast<Point::GrayScale*>((*f)(x, y));
              if (pt && ptIn)
              {
                long double scale = (pt->scale - minOld)/rangeOld;
                ptIn->scale = (rangeNew*scale)+minNew;
              }
            }
          }
        }
        else if (TType == Point::POINT_TYPES::RGB)
        {
          for (int y = 0; y < f->getHeight(); ++y)
          {
            for (int x = 0; x < f->getWidth(); ++x)
            {
              Point::RedGreenBlueForNormalization* pt = dynamic_cast<Point::RedGreenBlueForNormalization*>(first(x, y));
              Point::RedGreenBlue* ptIn = dynamic_cast<Point::RedGreenBlue*>((*f)(x, y));
              if (pt && ptIn)
              {
                long double scale = (pt->red - minRedOld)/rangeRedOld;
                ptIn->red = (rangeNew*scale)+minNew;
                scale = (pt->green - minGreenOld)/rangeGreenOld;
                ptIn->green = (rangeNew*scale)+minNew;
                scale = (pt->blue - minBlueOld)/rangeBlueOld;
                ptIn->blue = (rangeNew*scale)+minNew;
              }
            }
          }
        }
      }

      virtual void geometricAction(
          lambdaForEachGeoPoint_t lambda,
          uint64_t startX = 0,
          uint64_t startY = 0,
          uint64_t geoWidth = 0,
          uint64_t geoHeight = 0
      ){
          if (!geoWidth) geoWidth = this->getWidth();
          if (!geoHeight) geoHeight = this->getHeight();

          TemporaryImage tmpImg(geoHeight, geoWidth, type());
          Point::Point_t point;
          uint64_t x;
          uint64_t y;

          for (y = startY; y < geoHeight; ++y)
          {
            for (x = startX; x < geoWidth; ++x)
            {
              point = lambda(x, y);
              if (!(point.x >= tmpImg.width || point.y >= tmpImg.height))
              {
                tmpImg(point)->set((*this)(x, y));
              }
            }
          }
          this->copyFragment(tmpImg);
      }
  };

  template <typename T = uint64_t>
  struct RGBCounter
  {
    Common::ColorCounter <T> red;
    Common::ColorCounter <T> green;
    Common::ColorCounter <T> blue;
  };

  template <typename T = uint64_t>
  Common::ColorCounter <T> getGreyCounter ( Image *img )
  {
    Common::ColorCounter <T> greyCounter;
    img->forEach <Point::GrayScale> ([&]( Point::GrayScale *pt ){
        if (pt->scale >= 0 && pt->scale < 256)
          greyCounter [pt->scale] += 1;
    });
    return greyCounter;
  }

  template <typename T = uint64_t>
  RGBCounter <T> getRGBCounter ( Image *img )
  {
    RGBCounter <T> counter;
    img->forEach<Point::RedGreenBlue>([&](Point::RedGreenBlue *pt){
          if (pt->red && pt->green && pt->blue &&
            pt->red != 255 && pt->green != 255 && pt->blue != 255)
          {
            counter.red[pt->red] += 1;
            counter.green[pt->green] += 1;
            counter.blue[pt->blue] += 1;
          }
    });
    return counter;
  }
}

#endif //IMAGE_H

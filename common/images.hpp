
#ifndef COMMON_IMAGES_HPP
#define COMMON_IMAGES_HPP

#include "common.hpp"

#define png_infopp_NULL (png_infopp)NULL
#define int_p_NULL (int*)NULL

#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/io/png_dynamic_io.hpp>
using namespace boost::gil;

namespace Common
{
    typedef unsigned short color_rgb_t;

    struct RGB
    {
        color_rgb_t red;
        color_rgb_t green;
        color_rgb_t blue;
        String getString()
        {
            String re = "(";
            re += std::to_string(this->red) + ",";
            re += std::to_string(this->green) + ",";
            re += std::to_string(this->blue) + ")";
            return re;
        }
    };

    class Image
    {
    public:
        Image(){}
        virtual ~Image(){}
        virtual bool save() = 0;
        virtual bool save(String fileName) = 0;
        virtual RGB getRGB(const unsigned int x, const unsigned int y) = 0;
        virtual bool setRGB(const unsigned int x, const unsigned int y, RGB rgb) = 0;
        virtual unsigned int getHeight() = 0;
        virtual unsigned int getWidth() = 0;
    };

    class PNG : public Image
    {
        String fileName;
        rgb8_image_t image;
        unsigned int height;
        unsigned int width;

    public:

        PNG(String declarationFileName) : Image()
        {
            fileName = declarationFileName;
            png_read_and_convert_image(fileName, image);
            height = (unsigned int)image.height();
            width = (unsigned int)image.width();
        }

        bool save()
        {
            png_write_view(fileName, const_view(image));
        }

        bool save(String declarationFileName)
        {
            png_write_view(declarationFileName, const_view(image));
            return true;
        }

        RGB getRGB(const unsigned int x, const unsigned int y)
        {
            RGB rgb;
            rgb8_pixel_t pixel = view(image)(x, y);
            rgb.red = (color_rgb_t)pixel[0];
            rgb.green = (color_rgb_t)pixel[1];
            rgb.blue = (color_rgb_t)pixel[2];
            return rgb;
        }

        bool setRGB(const unsigned int x, const unsigned int y, RGB rgb)
        {
            rgb8_pixel_t pixel;
            pixel[0] = rgb.red;
            pixel[1] = rgb.green;
            pixel[2] = rgb.blue;
            view(image)(x, y) = pixel;
            return true;
        }

        unsigned int getHeight()
        {
            return height;
        }

        unsigned int getWidth()
        {
            return width;
        }
    };

    class Operation
    {
    public:
        virtual bool operate(Image *img) = 0;
    };

    class DoubleOperation
    {
    public:
        virtual bool operate(Image *fimg, Image *simg) = 0;
    };

    TEMPLATE_FUNC
    bool operate(Image *img, Operation *op)
    {
        return op->operate(img);
    }

    TEMPLATE_FUNC
    bool operate(Image *fimg, Image *simg, DoubleOperation *op)
    {
        return op->operate(fimg, simg);
    }
}

#endif //COMMON_IMAGES_HPP

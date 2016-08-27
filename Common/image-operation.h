
#ifndef SPAM_COMMON_IMAGE_OPERATION_H
#define SPAM_COMMON_IMAGE_OPERATION_H

#include <string>
typedef std::string String;

#include "bitmap/bitmap_image.hpp"

#define png_infopp_NULL (png_infopp)NULL
#define int_p_NULL (int*)NULL

#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/io/png_io.hpp>
#include <boost/gil/extension/io/png_dynamic_io.hpp>
using namespace boost::gil;

namespace Common
{
    struct RGB
    {
        unsigned char red;
        unsigned char green;
        unsigned char blue;
    };

    class Image
    {
    public:
        Image(){}
        virtual ~Image(){}
        virtual bool save(String fileName) = 0;
        virtual RGB getRGB(const unsigned int x, const unsigned int y) = 0;
        virtual bool setRGB(const unsigned int x, const unsigned int y, RGB rgb) = 0;
        virtual unsigned int getHeight() = 0;
        virtual unsigned int getWidth() = 0;
    };

    class BMP final: public Image
    {
        String fileName;
        bitmap_image *image;
        unsigned int height;
        unsigned int width;

    public:

        BMP(String declarationFileName) : fileName(declarationFileName)
        {
            image = new bitmap_image(fileName);
            if (image)
            {
                height = image->height();
                width  = image->width();
            }
        }

        ~BMP()
        {
            delete image;
        }

        bool save(String declarationFileName = "")
        {
            if (declarationFileName.size() == 0)
            {
                image->save_image(fileName);
            }
            else
            {
                image->save_image(declarationFileName);
            }
        }

        bool setRGB(const unsigned int x, const unsigned int y, RGB rgb)
        {
            return false;
        }

        RGB getRGB(const unsigned int x, const unsigned int y)
        {
            RGB rgb;
            image->get_pixel(x, y, rgb.red, rgb.green, rgb.blue);
            return rgb;
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

    class TIFF // : public Image
    {
        //TODO
    };

    class PNG : public Image
    {
        String fileName;
        rgb8_image_t *image;
        unsigned int height;
        unsigned int width;

    public:

        PNG(const char* declarationFileName)
        {
            //fileName = declarationFileName;
            png_read_image(declarationFileName, (*image));

            height = 0;
            width = 0;
        }

        virtual ~PNG()
        {
            delete image;
        }

        bool save(String declarationFileName)
        {
            if (declarationFileName.size() == 0)
            {
                //png_write_view(fileName, const_view(img));
                //png_write_view(fileName, image);
            }
            else
            {
                //png_write_view("redsquare.png", const_view(img));
                //png_write_view(declarationFileName, image);
            }
            return true;
        }

        RGB getRGB(const unsigned int x, const unsigned int y)
        {
            RGB rgb;
            return rgb;
        }

        bool setRGB(const unsigned int x, const unsigned int y, RGB rgb)
        {
            return false;
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

    class GIF // : public Image
    {
        //TODO
    };

    class Operation
    {
    public:
        virtual bool operate(Image *img) = 0;
    };

    template<typename T = int>
    bool operate(Image *img, Operation *op)
    {
        return op->operate(img);
    }

    template<typename T = int>
    bool showImg(Image *img)
    {
        //TODO
        return false;
    }
}

#endif //SPAM_COMMON_IMAGE_OPERATION_H

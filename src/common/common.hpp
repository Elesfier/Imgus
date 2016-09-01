
#ifndef COMMON_COMMON_HPP
#define COMMON_COMMON_HPP

#include <string>
#include <vector>
#include <boost/filesystem/operations.hpp>

namespace Common
{
    typedef std::string String;
    typedef unsigned char RGBColor;

    struct RGB
    {
        RGBColor red;
        RGBColor green;
        RGBColor blue;
    };

    namespace Formats
    {
        class Image;
        typedef std::vector<Image*> ImagePack;

        class Image
        {
        public:
            Image(){}
            virtual ~Image(){}
            virtual bool save() = 0;
            virtual bool save(String fileName) = 0;
            //TODO(aszajdecki): funkcja dzieki ktorej bedzie ladniejszy dostep do piksela
            //virtual RGB& operator()(const uint32_t x, const uint32_t y) = 0;
            virtual RGB getRGB(const unsigned int x, const unsigned int y) = 0;
            virtual bool setRGB(const unsigned int x, const unsigned int y, RGB rgb) = 0;
            virtual uint32_t getHeight() const = 0;
            virtual uint32_t getWidth() const = 0;
            //TODO(aszajdecki): funkcja ktora by przez kazdy piksel przechodzila
            //virtual forEach(lambda) = 0;
        };

        class Operation
        {
        public:
            Operation(){}
            virtual ~Operation(){}
            virtual bool operate(Image *img){ return false; };
            virtual bool operate(ImagePack pack){ return false; };
        };

        template<typename null_t = nullptr_t>
        bool operate(Image *img, Operation *op)
        {
            return op->operate(img);
        }

        template<typename null_t = nullptr_t>
        bool operate(ImagePack pack, Operation *op)
        {
            return op->operate(pack);
        }
    }

    namespace Windows
    {
        class GUI
        {
        public:
            virtual int execute(int argc, char *argv[]) = 0;
        };
    }

    template<typename null_t = nullptr_t>
    String getCurrentPath()
    {
        return boost::filesystem::current_path().string();
    }
}

#endif //COMMON_COMMON_HPP

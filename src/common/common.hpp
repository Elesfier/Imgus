
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
            virtual RGB getRGB(const uint32_t x, const uint32_t y) = 0;
            virtual bool setRGB(const uint32_t x, const uint32_t y, RGB rgb) = 0;
            virtual uint32_t getHeight() const = 0;
            virtual uint32_t getWidth() const = 0;
            //TODO(aszajdecki): funkcja ktora by przez kazdy piksel przechodzila
            //virtual void forEach(lambda) = 0;
        };

        class Operation
        {
        public:
            Operation(){}
            virtual ~Operation(){}
            virtual void operate(Image *img){ };
            virtual void operate(ImagePack pack){ };
        };

        template<typename null_t = nullptr_t>
        void operate(Image *img, Operation *op)
        {
            return op->operate(img);
        }

        template<typename null_t = nullptr_t>
        void operate(ImagePack pack, Operation *op)
        {
            return op->operate(pack);
        }

        struct OperationDefinition
        {
            Operation* op;
            String className;
            String polishName;
            bool hasParams;
            bool isMulti;
        };

        class OperationsDefinition
        {
        public:
            static OperationsDefinition& get()
            {
                static OperationsDefinition instance;
                return instance;
            }
            std::vector<OperationDefinition> ops;
            OperationsDefinition(OperationsDefinition const&) = delete;
            void operator=(OperationsDefinition const&) = delete;
        private:
            OperationsDefinition() {};
        };

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

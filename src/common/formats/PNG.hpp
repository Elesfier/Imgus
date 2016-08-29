
#ifndef COMMON_FORMATS_PNG_HPP
#define COMMON_FORMATS_PNG_HPP

#include "../common.hpp"

#define png_infopp_NULL (png_infopp)NULL
#define int_p_NULL (int*)NULL

#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/io/png_dynamic_io.hpp>

namespace Common
{
    namespace Formats
    {
        using namespace boost::gil;

        class PNG : public Image
        {
            String fileName;
            //TODO(aszajdecki): zeby tutaj png obsluzyl wiecej obrazkow o roznych bitach
            rgb8_image_t image;
        public:
            PNG() = delete;
            PNG(String declarationFileName);
            bool save();
            bool save(String declarationFileName);
            RGB getRGB(const unsigned int x, const unsigned int y);
            bool setRGB(const unsigned int x, const unsigned int y, RGB rgb);
            uint32_t getHeight() const;
            uint32_t getWidth() const;
        };
    }
}

#endif //COMMON_FORMATS_PNG_HPP

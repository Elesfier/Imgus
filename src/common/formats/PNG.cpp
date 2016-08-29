
#include "PNG.hpp"

Common::Formats::PNG::PNG(Common::String declarationFileName) : fileName(declarationFileName)
{
    png_read_and_convert_image(fileName, image);
}

bool Common::Formats::PNG::save() {
    try { png_write_view(fileName, const_view(image)); }
    catch (...) { return false; }
    return true;
}

bool Common::Formats::PNG::save(Common::String declarationFileName) {
    try { png_write_view(declarationFileName, const_view(image)); }
    catch (...) { return false; }
    return true;
}

Common::RGB Common::Formats::PNG::getRGB(const unsigned int x, const unsigned int y) {
    //FIXME: zeby ladniej wygladala ta implementacja
    rgb8_pixel_t pixel = view(image)(x, y);
    RGB rgb {(RGBColor)pixel[0], (RGBColor)pixel[1], (RGBColor)pixel[2]};
    return rgb;
}

bool Common::Formats::PNG::setRGB(const unsigned int x, const unsigned int y, Common::RGB rgb) {
    //FIXME: zeby ladniej wygladala ta implementacja
    rgb8_pixel_t pixel;
    pixel[0] = rgb.red;
    pixel[1] = rgb.green;
    pixel[2] = rgb.blue;
    view(image)(x, y) = pixel;
    return true;
}

uint32_t Common::Formats::PNG::getHeight() const {
    return static_cast<uint32_t>(image.height());
}

uint32_t Common::Formats::PNG::getWidth() const {
    return static_cast<uint32_t>(image.width());
}

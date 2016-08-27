
#include "../../../common/images.hpp"

//
// 1.1. Negacja obrazu
//
class ImageNegation : public Common::Operation
{
    bool operate(Common::Image *img)
    {
        unsigned short heigth = img->getHeight();
        unsigned short width = img->getWidth();

        for (unsigned short i = 0; i < heigth; ++i)
        {
            for (unsigned short j = 0; j < width; ++j)
            {
                Common::RGB newRGB = img->getRGB(i, j);
                newRGB.red = 255 - newRGB.red;
                newRGB.green = 255 - newRGB.green;
                newRGB.blue = 255 - newRGB.blue;
                img->setRGB(i, j, newRGB);
            }
        }

        return true;
    }
};

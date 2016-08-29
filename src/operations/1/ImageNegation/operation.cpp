
#include "../../../common/common.hpp"

//
// 1.1. Negacja obrazu
//
class ImageNegation : public Common::Formats::Operation
{
    bool operate(Common::Formats::Image *img)
    {
        try
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
        }
        catch(...)
        {
            return false;
        }
        return true;
    }
};


#ifndef PNG_MANUALLY_H
#define PNG_MANUALLY_H

#include "src/headers/point.h"
#include "src/headers/image.h"
#include "src/headers/exceptions.h"
#include "src/formats/PNG-decoder-encoder.h"
#include <vector>
#include <fstream>

namespace Image
{
    class PNG_MANUALLY : public Image
    {
        std::vector <unsigned char> image;
        lodepng::State state;
        LodePNGColorType colortype;
        unsigned bitdepth;

    public:

        PNG_MANUALLY(Common::String declarationFileName);
        void save();
        void save(Common::String declarationFileName);
        void fillImageContainer ();
    };
}

#endif //PNG_MANUALLY_H

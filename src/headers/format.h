
#ifndef FORMAT_H
#define FORMAT_H

//Standard Format
#include "src/formats/PNG-manually.h"
typedef Image::PNG_MANUALLY MAIN_FORMAT_TYPE;

template <typename null_t = nullptr_t>
Common::String GET_MAIN_FORMAT_NAME(){ return "PNG"; }

template <typename null_t = nullptr_t>
Common::String GET_MAIN_EXTENSION_NAME(){ return ".png"; }

#endif //FORMAT_H

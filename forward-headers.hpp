
#ifndef FORWARD_HEADERS_HPP
#define FORWARD_HEADERS_HPP

//Common
#include "src/common/common.hpp"

//Formats
#include "src/common/formats/PNG.hpp"
typedef Common::Formats::PNG MAIN_FORMAT_TYPE;

namespace Operations
{
    //ImageNegation
    #include "src/operations/1/ImageNegation/operation.cpp"
    //TODO: niskopoziomowy mechanizm, dla wczytywania operacji dla windows
}

//GUI
#include "src/common/windows/QT.hpp"
typedef Common::Windows::QT MAIN_WINDOW_TYPE;

#endif //FORWARD_HEADERS_HPP

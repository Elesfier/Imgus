
#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <vector>
#include <utility>
#include <boost/filesystem/operations.hpp>

namespace Common
{
    typedef std::string String;

    template < typename ChartPointType_t = uint64_t >
    class ColorCounter : public std::vector < ChartPointType_t >
    {
    public:
      ColorCounter() : std::vector < ChartPointType_t > (256, 0) {}
    };

    template <typename null_t = nullptr_t>
    String getCurrentPath()
    {
        return boost::filesystem::current_path().string();
    }

    //[FIXME]: tak nie powinno być
    template <typename null_t = nullptr_t>
    long double convertToNumber (String number)
    {
        std::size_t found = number.find(".");
        number[found] = ',';
        return std::stold(number);
    }

    //[FIXME]: tak nie powinno być
    template <typename null_t = nullptr_t>
    Common::String convertToString (uint64_t number)
    {
        return std::to_string(number);
    }
}

#endif //COMMON_H

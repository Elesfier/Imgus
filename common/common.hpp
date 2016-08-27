
#ifndef COMMON_HPP
#define COMMON_HPP

#include <string>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <iostream>

namespace Common
{
    typedef std::string String;

    class EMPTY_TEMPLATE_CLASS {};

    #define TEMPLATE_FUNC template<class clazz=EMPTY_TEMPLATE_CLASS>

    TEMPLATE_FUNC
    String getCurrentDirectory()
    {
        boost::filesystem::path full_path(boost::filesystem::current_path());
        return full_path.string();
    }
}

#endif //COMMON_HPP

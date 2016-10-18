
#ifndef OPERATIONS_OPERATIONS_HPP
#define OPERATIONS_OPERATIONS_HPP

#include "src/common/common.hpp"

#define __QUOTEME(x) __QUOTEME_1(x)
#define __QUOTEME_1(x) #x
#define NAME_OPERATION_FILE(x) __QUOTEME(x/operation.cpp)

#include NAME_OPERATION_FILE(ImageNegation)
#include NAME_OPERATION_FILE(LogicalSumPaintings)
#include NAME_OPERATION_FILE(ProductOfLogicalPaintings)
#include NAME_OPERATION_FILE(XOROperation)

template<typename null_t = nullptr_t>
void SETUP_OPERATIONS()
{
    Common::Formats::OperationsDefinition::get().ops.push_back({
           new ImageNegation(),
           "ImageNegation",
           "Negacja Obrazu",
           false,
           false
    });

    Common::Formats::OperationsDefinition::get().ops.push_back({
           new LogicalSumPaintings(),
           "LogicalSumPaintings",
           "Suma Logiczna Obrazów",
           false,
           true
    });
}

#endif //OPERATIONS_OPERATIONS_HPP

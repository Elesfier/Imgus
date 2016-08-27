
#include "forward-declaration.h"

#include <iostream>

using namespace Common;
using namespace Operations;

int main()
{
    try
    {
        const char* fileName = "/home/elesfier/ClionProjects/SPAM/Obrazek.png";

        Image *img = new PNG(fileName);
        Operation *op = new ImageNegation();

        //showImg(img);

        operate(img, op);

        //showImg(img);
    }
    catch(...)
    {
        std::cout << std::endl << "Wyjatek" << std::endl;
    }

    std::cout << std::endl << "Koniec programu." << std::endl;
    return 0;
}

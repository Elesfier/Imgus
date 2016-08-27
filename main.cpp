
#include "forward-declaration.hpp"

using namespace Common;
using namespace Operations;

int main()
{
    String currentImageStoragePath = "/graphics/Drugi.png";
    String currentDirectory = Common::getCurrentDirectory();
    String fileName = currentDirectory + currentImageStoragePath;

    Image *img = new PNG(fileName);
    Operation *op = new ImageNegation();
    operate(img, op);
    img->save();

    std::cout << std::endl << "END" << std::endl << std::endl;
    return 0;
}

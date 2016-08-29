
#include "forward-headers.hpp"

void preTest()
{
    using namespace Common;
    using namespace Common::Formats;
    using namespace Common::Windows;
    using namespace Operations;

    String currentImageStoragePath = "/img/ok.png";
    String currentDirectory = Common::getCurrentPath();
    String fileName = currentDirectory + currentImageStoragePath;

    //TODO: Tworzenie GUI
    //GUI* gui = new QT();
    //gui->run();

    Image *img = new PNG(fileName);
    Operation *op = new ImageNegation();
    operate(img, op);
    img->save();

    delete img;
    delete op;
}

int main()
{
    preTest();

    return 0;
}

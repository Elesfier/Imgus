
#include "QT.hpp"

Common::Windows::QT::QT() {
    window = nullptr;
}

Common::Windows::QT::~QT() {
    if (window != nullptr) delete window;
}

int Common::Windows::QT::execute(int argc, char **argv) {
    QApplication app(argc, argv);
    window = new QMainWindow();
    setupMainWindow();
    setupLayouts();
    setupWestLayout();
    setupEastLayout();
    setupMiddleLayout();
    setupEvents();
    window->show();
    return app.exec();
}

void Common::Windows::QT::setupMainWindow() {
    window->setWindowTitle("Program do przetwarzania obrazów");
    window->setGeometry(
            QStyle::alignedRect(
                    Qt::LeftToRight,
                    Qt::AlignCenter,
                    window->size(),
                    qApp->desktop()->availableGeometry()
            )
    );
}

void Common::Windows::QT::setupLayouts() {
    //TODO
}

void Common::Windows::QT::setupWestLayout() {
    //TODO
}

void Common::Windows::QT::setupEastLayout() {
    //TODO
}

void Common::Windows::QT::setupMiddleLayout() {
    //TODO
}

void Common::Windows::QT::setupEvents() {
    //TODO
}

/* PRZYKLAD UZYCIA OBRAZKOW I OPERACJI
void preTest()
{
    using namespace Common;
    using namespace Common::Formats;
    using namespace Common::Windows;
    using namespace Operations;

    String currentImageStoragePath = "/img/ok.png";
    String currentDirectory = Common::getCurrentPath();
    String fileName = currentDirectory + currentImageStoragePath;

    //GUI* gui = new QT();
    //gui->run();

    Image *img = new PNG(fileName);
    Operation *op = new ImageNegation();
    operate(img, op);
    img->save();

    delete img;
    delete op;
}
*/
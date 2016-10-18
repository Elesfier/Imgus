

//Common
#include "src/common/common.hpp"

//Operations
namespace Operations
{
    #include "src/operations/operations.hpp"
}

//GUI
#include "src/common/windows/QT.hpp"
typedef Common::Windows::QT MAIN_WINDOW_TYPE;

int main(int argc, char *argv[])
{
    Operations::SETUP_OPERATIONS<>();
    MAIN_WINDOW_TYPE gui;
    return gui.execute(argc, argv);
}

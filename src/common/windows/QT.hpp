
#ifndef COMMON_WINDOWS_QT_HPP
#define COMMON_WINDOWS_QT_HPP

#include "../common.hpp"
#include <QApplication>
#include <QMainWindow>
#include <QStyle>
#include <QDesktopWidget>

namespace Common
{
    namespace Windows
    {
        class QT : public GUI
        {
            QMainWindow* window;
        public:
            QT();
            ~QT();
            int execute(int argc, char *argv[]);
            void setupMainWindow();
            void setupLayouts();
            void setupWestLayout();
            void setupEastLayout();
            void setupMiddleLayout();
            void setupEvents();
        };
    }
}

#endif //COMMON_WINDOWS_QT_HPP

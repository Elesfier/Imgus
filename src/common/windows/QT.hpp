
#ifndef COMMON_WINDOWS_QT_HPP
#define COMMON_WINDOWS_QT_HPP

#include "src/common/common.hpp"

#include <QApplication>
#include <QMainWindow>
#include <QStyle>
#include <QDesktopWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QFrame>
#include <QFileDialog>
#include <QDir>
#include <QGraphicsPixmapItem>

#include <stdexcept>
#include <iostream>

//Formats
#include "src/common/formats/PNG.hpp"
typedef Common::Formats::PNG MAIN_FORMAT_TYPE;

namespace Common
{
    namespace Windows
    {
        QTextEdit* operator<< (QTextEdit* textArea, String str);
        QTextEdit* operator<< (QTextEdit* textArea, QString str);

        class QT : public QObject, public GUI
        {
        Q_OBJECT

            const float multiHeight = 1.0;
            const float multiWidth = 1.5;

            std::vector<String> fileNames;
            std::vector<QPushButton*> buttons;

            QMainWindow *mainWindow;
            QWidget *window;
            QFormLayout *imagesLayout;
            QFormLayout *paramsLayout;
            QGraphicsScene *sceneImage;
            QGraphicsView *viewImage;
            QComboBox *selectOperations;
            QPushButton *actionButton;
            QPushButton *addButton;
            QTextEdit *textArea;

        private slots:
            void onClickAdd();
            void onClickAction();
            void onChangeSelect(const QString&);
            void onClickRemove();

        public:
            QT();
            QT(QObject *parent);
            int execute(int argc, char **argv);
            void setupMainWindow();
            void setupLayouts();
            void setupOperations();
            void setupEvents();
        };
    }
}

#endif //COMMON_WINDOWS_QT_HPP

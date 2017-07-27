
#include "QT.h"

QTextEdit *::Windows::operator<<(QTextEdit *textArea, QString str)
{
    str = ">> " + str;
    textArea->append(str);
    return textArea;
}

QTextEdit *::Windows::operator<<(QTextEdit *textArea, Common::String str)
{
    str = ">> " + str;
    textArea->append(QString::fromStdString(str));
    return textArea;
}

int Windows::QT::execute(int argc, char **argv)
{
    QApplication app(argc, argv);
    mainWindow = new QMainWindow();
    window = new QWidget();
    mainWindow->setCentralWidget(window);
    setupMainWindow();
    setupLayouts();
    setupOperations();
    setupEvents();
    onChangeSelect("select_init");
    textArea << Common::String("Początek");
    mainWindow->show();
    return app.exec();
}

Windows::QT::QT(){}
Windows::QT::QT(QObject *parent) : QObject(parent){}

void Windows::QT::setupMainWindow()
{
    mainWindow->setWindowTitle("Program do przetwarzania obrazów - Imgus");
    mainWindow->setFixedSize(
            mainWindow->width()*multiWidth,
            mainWindow->height()*multiHeight
    );
    mainWindow->setGeometry(
            QStyle::alignedRect(
                    Qt::LeftToRight,
                    Qt::AlignCenter,
                    mainWindow->size(),
                    qApp->desktop()->geometry()
            )
    );
}

QLabel* createLabel(Common::String label)
{
    QLabel *qlabel = new QLabel(QString::fromStdString(label));
    qlabel->setAlignment(Qt::AlignCenter);
    return qlabel;
}

void Windows::QT::setupLayouts()
{
    QHBoxLayout *mainLayout = new QHBoxLayout();
    QVBoxLayout *leftLayout = new QVBoxLayout();
    QVBoxLayout *middleLayout = new QVBoxLayout();

    sceneImage = new QGraphicsScene(mainWindow);
    viewImage = new QGraphicsView(sceneImage);
    imagesLayout = new QFormLayout();
    selectOperations = new QComboBox();
    paramsLayout = new QFormLayout();
    textArea = new QTextEdit();
    addButton = new QPushButton("Dodaj Obrazek");
    actionButton = new QPushButton("Wykonaj Operacje");

    leftLayout->addWidget(createLabel("Obrazki (" + GET_MAIN_FORMAT_NAME() + ")"));
    leftLayout->addLayout(imagesLayout, 1);
    leftLayout->addWidget(addButton);

    middleLayout->addWidget(createLabel("Operacje"));
    middleLayout->addWidget(selectOperations);
    middleLayout->addLayout(paramsLayout, 1);
    middleLayout->addWidget(createLabel("Terminal"));
    middleLayout->addWidget(textArea);
    middleLayout->addWidget(actionButton);

    mainLayout->setSpacing(12);
    mainLayout->addLayout(leftLayout, 1);
    mainLayout->addLayout(middleLayout, 1);
    mainLayout->addWidget(viewImage, 2);

    window->setLayout(mainLayout);
}

void Windows::QT::setupOperations()
{
    int l = Operations::OperationsDefinition::get().ops.size();
    for (int i = 0; i < l; ++i)
    {
        QString qstr = QString::fromStdString(Operations::OperationsDefinition::get().ops.at(i).op->name);
        selectOperations->addItem(qstr);
    }
}

void Windows::QT::setupEvents()
{
    connect(actionButton, SIGNAL(released()), this, SLOT(onClickAction()));
    connect(addButton, SIGNAL(released()), this, SLOT(onClickAdd()));
    connect(selectOperations,SIGNAL(currentIndexChanged(const QString&)), this, SLOT(onChangeSelect(const QString&)));
}

void Windows::QT::onClickAdd()
{
    Common::String files = "Images (*" + GET_MAIN_EXTENSION_NAME() + ")";
    QString pathName = QFileDialog::getOpenFileName(
        window,
        tr("Dodaj Obrazek"),
        QDir::currentPath(),
        tr(files.c_str())
    );
    if (pathName.size() == 0) return;
    Common::String path = pathName.toStdString();

    Image::Image *img = nullptr;
    try { img = new MAIN_FORMAT_TYPE(path); }
    catch(std::exception &e)
    {
      img = nullptr;
      textArea << Common::String(e.what());
      //textArea << Common::String("Błąd: Nie udało się wczytać obrazka.");
      return;
    }

    fileNames.push_back(pathName.toStdString());
    Common::String fileName = "";
    size_t pos = path.find_last_of("/");
    if(pos != std::string::npos)
        fileName.assign(path.begin() + pos + 1, path.end());
    else
        fileName = path;
    QPushButton *button = new QPushButton("Skasuj");
    connect(button, SIGNAL(released()), this, SLOT(onClickRemove()));

    Common::String imageSize = (" (" + Common::convertToString(img->getHeight()) + "," + Common::convertToString(img->getWidth()) + ") ");
    Common::String pointTypeName;
    if (img->type() == Point::POINT_TYPES::BINARY) pointTypeName = "(Binarny)";
    else if (img->type() == Point::POINT_TYPES::GRAY_SCALE) pointTypeName = "(Szary)";
    else if (img->type() == Point::POINT_TYPES::RGB) pointTypeName = "(Barwny)";
    buttons.push_back(button);
    imagesLayout->addRow(QString::fromStdString(fileName + imageSize + pointTypeName), button);
    QPixmap pix(pathName);
    if (!pix.isNull())
    {
        QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pix);
        sceneImage->clear();
        sceneImage->addItem(item);
        viewImage->update();
    }
    textArea << Common::String(Common::String("Dodano: ") + fileName);
}

void Windows::QT::onClickAction()
{
    Operations::OperationDefinition* op = &Operations::OperationsDefinition::get().ops[selectOperations->currentIndex()];
    try
    {
            if ((fileNames.size() >= 2) && (op->isMulti))
            {
              Operations::ImagePack pack;
              for (auto &fileName : fileNames)
              {
                  pack.push_back(new MAIN_FORMAT_TYPE(fileName));
              }
              if (op->op->sameFormat && (pack[0]->notSame(pack[1])))
                throw WhatCustomException("BŁĄD OPERACJI: obrazki nie są jednolite.");
              if (op->op->disableBinary && (pack[0]->type() == Point::POINT_TYPES::BINARY))
                throw WhatCustomException("BŁĄD OPERACJI: zły format obrazków (binarny).");
              if (op->op->disableGrayScale && (pack[0]->type() == Point::POINT_TYPES::GRAY_SCALE))
                throw WhatCustomException("BŁĄD OPERACJI: zły format obrazków (szary).");
              if (op->op->disableRGB && (pack[0]->type() == Point::POINT_TYPES::RGB))
                throw WhatCustomException("BŁĄD OPERACJI: zły format obrazków (kolorowy).");
              Operations::operate(pack, op->op, getCurrentParamsPack());
              QFileInfo fiNaTmp(QString::fromStdString(fileNames[0]));
              Common::String fileName = fiNaTmp.path().toStdString() + "/" + op->fileNameAddon;
              for (auto &fileNameSecond : fileNames)
              {
                QFileInfo fiNaTmpInside(QString::fromStdString(fileNameSecond));
                fileName += "_" + fiNaTmpInside.fileName().split(".").at(0).toStdString();
              }
              fileName += "." + pack[0]->getExtension();
              pack[0]->save(fileName);
              QPixmap pix(QString::fromStdString(fileName));
              if (!pix.isNull())
              {
                  QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pix);
                  sceneImage->clear();
                  sceneImage->addItem(item);
                  viewImage->update();
              }
              else
              {
                  throw;
              }
              textArea << Common::String("Operacja została pomyślnie przeprowadzona.");
            }
            else if (fileNames.size() != 0)
            {
                Common::String fileName = fileNames[0];
                Image::Image *img = new MAIN_FORMAT_TYPE(fileName);
                if (op->op->disableBinary && (img->type() == Point::POINT_TYPES::BINARY))
                  throw WhatCustomException("BŁĄD OPERACJI: zły format obrazku (binarny).");
                if (op->op->disableGrayScale && (img->type() == Point::POINT_TYPES::GRAY_SCALE))
                  throw WhatCustomException("BŁĄD OPERACJI: zły format obrazku (szary).");
                if (op->op->disableRGB && (img->type() == Point::POINT_TYPES::RGB))
                  throw WhatCustomException("BŁĄD OPERACJI: zły format obrazku (kolorowy).");
                if (op->op->isOnlyMulti)
                  throw WhatCustomException("BŁĄD OPERACJI: do tej operacji trzeba dwóch obrazów.");
                Operations::operate(img, op->op, getCurrentParamsPack());
                QFileInfo fiNaTmp(QString::fromStdString(fileName));
                fileName = fiNaTmp.path().toStdString() + "/" + op->fileNameAddon + fiNaTmp.fileName().toStdString();
                img->save(fileName);
                QPixmap pix(QString::fromStdString(fileName));
                if (!pix.isNull())
                {
                    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pix);
                    sceneImage->clear();
                    sceneImage->addItem(item);
                    viewImage->update();
                }
                else
                {
                    throw;
                }
                textArea << Common::String("Operacja została pomyślnie przeprowadzona.");
            }
            else
            {
                textArea << Common::String("Błąd: Nie dodano żadnego obrazka.");
            }
        //}
    }
    catch(std::exception& e)
    {
        textArea << Common::String(e.what());
    }
    op = nullptr;
}

void Windows::QT::onClickRemove()
{
    QObject* obj = QObject::sender();
    if(QPushButton* button = dynamic_cast<QPushButton*>(obj))
    {
        uint8_t length = buttons.size();
        for(uint8_t i = 0; i < length; ++i)
        {
            if (buttons[i] == button)
            {
                fileNames.erase(fileNames.begin()+i);
                imagesLayout->labelForField(buttons[i])->deleteLater();
                buttons[i]->deleteLater();
                buttons.erase(buttons.begin()+i);
                textArea << Common::String("Skasowano obrazek");
                break;
            }
        }
    }
}

Operations::ParamsPack Windows::QT::getCurrentParamsPack()
{
    Operations::ParamsPack params;
    for (auto& pair : currentParams)
    {
        QStringList paraList = QString::fromStdString(pair.first).split('_');
        if (paraList[1].at(0) == 'n')
        {
          Common::String value = ((QLineEdit*)pair.second)->text().toStdString();
          params.insert(std::pair<Common::String,Common::String>(paraList[0].toStdString(), value));
        }
    }
    return params;
}

void Windows::QT::onChangeSelect(const QString&)
{
    Operations::OperationDefinition* op = &Operations::OperationsDefinition::get().ops[selectOperations->currentIndex()];
    Operations::ParamsPack paramsPack = op->paramsPack;
    currentParams.clear();
    QLayoutItem* item;
    while ( ( item = paramsLayout->takeAt(0) ) != nullptr )
    {
      delete item->widget();
      delete item;
    }
    for (auto& pair : paramsPack)
    {
      QString para = QString::fromStdString(pair.second);
      if (para.at(0) == 'n')
      {
          QLineEdit *input = new QLineEdit();
          input->setText(para.mid(1, para.size()-1));
          currentParams.insert( std::pair<Common::String, QWidget*>(pair.first + '_' + pair.second, input) );
          paramsLayout->addRow(QString::fromStdString(pair.first), input);
      }
    }
}

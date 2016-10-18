
#include "QT.hpp"

QTextEdit *::Common::Windows::operator<<(QTextEdit *textArea, QString str)
{
    str = ">> " + str;
    textArea->append(str);
    return textArea;
}

QTextEdit *::Common::Windows::operator<<(QTextEdit *textArea, Common::String str)
{
    str = ">> " + str;
    textArea->append(QString::fromStdString(str));
    return textArea;
}

int Common::Windows::QT::execute(int argc, char **argv)
{
    QApplication app(argc, argv);
    mainWindow = new QMainWindow();
    window = new QWidget();
    mainWindow->setCentralWidget(window);
    setupMainWindow();
    setupLayouts();
    setupOperations();
    setupEvents();
    textArea << String("Begin");
    mainWindow->show();
    return app.exec();
}

Common::Windows::QT::QT(){}
Common::Windows::QT::QT(QObject *parent) : QObject(parent){}

void Common::Windows::QT::setupMainWindow()
{
    mainWindow->setWindowTitle("Program do przetwarzania obrazów");
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

void Common::Windows::QT::setupLayouts()
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

    leftLayout->addWidget(createLabel("Obrazki"));
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

void Common::Windows::QT::setupOperations()
{
    int l = Common::Formats::OperationsDefinition::get().ops.size();
    for (int i = 0; i < l; ++i)
    {
        QString qstr = QString::fromStdString(Common::Formats::OperationsDefinition::get().ops.at(i).polishName);
        selectOperations->addItem(qstr);
    }
}

void Common::Windows::QT::setupEvents()
{
    connect(actionButton, SIGNAL(released()), this, SLOT(onClickAction()));
    connect(addButton, SIGNAL(released()), this, SLOT(onClickAdd()));
    connect(selectOperations,SIGNAL(currentIndexChanged(const QString&)), this, SLOT(onChangeSelect(const QString&)));
}

void Common::Windows::QT::onClickAdd()
{
    QString pathName = QFileDialog::getOpenFileName(
        window,
        tr("Dodaj Obrazek"),
        QDir::currentPath(),
        tr("Images (*.png)")
    );
    if (pathName.size() == 0) return;
    String path = pathName.toStdString();
    fileNames.push_back(pathName.toStdString());
    String fileName = "";
    size_t pos = path.find_last_of("/");
    if(pos != std::string::npos)
        fileName.assign(path.begin() + pos + 1, path.end());
    else
        fileName = path;
    QPushButton *button = new QPushButton("Skasuj");
    connect(button, SIGNAL(released()), this, SLOT(onClickRemove()));
    buttons.push_back(button);
    imagesLayout->addRow(QString::fromStdString(fileName), button);
    QPixmap pix(pathName);
    if (!pix.isNull())
    {
        QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pix);
        sceneImage->clear();
        sceneImage->addItem(item);
        viewImage->update();
    }
    textArea << String("Dodano: ");
    textArea << fileName;
}

void Common::Windows::QT::onClickAction()
{
    Common::Formats::OperationDefinition* op = &Common::Formats::OperationsDefinition::get().ops[selectOperations->currentIndex()];
    try
    {
        if(op->isMulti){
            //TODO
        } else {
            if (fileNames.size() != 0)
            {
                String fileName = fileNames[0];
                Common::Formats::Image *img = new MAIN_FORMAT_TYPE(fileName);
                Common::Formats::operate(img, op->op);
                img->save();
                textArea << fileName;
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
            }
            else
            {
                textArea << String("Blad: Nie dodano zadnego obrazka.");
            }
        }
        textArea << String("Operacja: Zostala pomyslnie przeprowadzona.");
    }
    catch(std::exception e)
    {
        textArea << String(e.what());
    }
    catch(...)
    {
        textArea << String("Total Exception: Cos mocno poszlo nie tak.");
    }
    op = nullptr;
}

void Common::Windows::QT::onClickRemove()
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
                buttons.erase(buttons.begin()+i);
                imagesLayout->labelForField(button)->deleteLater();
                button->deleteLater();
                textArea << String("Skasowano obrazek");
                break;
            }
        }
    }
}

void Common::Windows::QT::onChangeSelect(const QString&)
{
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
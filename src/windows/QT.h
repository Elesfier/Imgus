
#ifndef QT_H
#define QT_H

#include "src/headers/common.h"
#include "src/headers/format.h"
#include "src/headers/operation.h"
#include "src/headers/windows.h"

#include <QtGui>
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

#include <qwt_plot.h>
#include <qwt_plot_multi_barchart.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>
#include <qwt_scale_draw.h>
#include <qwt_scale_div.h>

class QConversionScaleDraw : public QwtScaleDraw {};

#include <map>
#include <vector>
#include <utility>
#include <stdexcept>
#include "src/headers/exceptions.h"

namespace Windows
{
    QTextEdit* operator<< (QTextEdit* textArea, Common::String str);
    QTextEdit* operator<< (QTextEdit* textArea, QString str);

    class QT : public QObject, public Windows::GUI
    {
        Q_OBJECT

        const float multiHeight = 1.0;
        const float multiWidth = 1.8;

        std::vector<Common::String> fileNames;
        std::vector<QPushButton*> buttons;
        std::map<Common::String, QWidget*> currentParams;

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
        Operations::ParamsPack getCurrentParamsPack();
        static void generateChart ( Common::String title, Common::ColorCounter <> counter )
        {
          QVector< QVector< double > > series(255, QVector <double> (1,0) );
          title = "Histogram (" + title + ")";
          QwtPlot *myPlot = new QwtPlot( NULL );
          myPlot->setFixedWidth(500);
          myPlot->setWindowTitle(QString::fromStdString(title));
          QConversionScaleDraw *scale = new QConversionScaleDraw();
          myPlot->setAxisScale (QwtPlot::xBottom, 0.0, 255.0);
          //myPlot->setAxisScaleDraw( QwtPlot::yLeft, scale );
          //myPlot->setAxisScale( QwtPlot::yLeft, 0, 300);

          myPlot->setAxisTitle( QwtPlot::xBottom, "Zakres Koloru" );
          myPlot->setAxisTitle( QwtPlot::yLeft, "Ilość" );

          QwtPlotGrid *grid = new QwtPlotGrid();
          grid->attach( myPlot );

          QwtPlotMultiBarChart *barChart = new QwtPlotMultiBarChart("");
          barChart->setLayoutPolicy( QwtPlotMultiBarChart::AutoAdjustSamples );
          barChart->setSpacing( 0 );
          barChart->setMargin( 0 );

          for ( int i = 0; i < series.size(); i++ )
            { series[i][0] = counter[i];   }

          myPlot->resize( 600, 400 );
          barChart->setSamples ( series );
          barChart->attach ( myPlot );
          myPlot->replot();
          myPlot->show();

          //QPixmap pixmap = QPixmap::grabWidget(myPlot);
	        //pixmap.save(QString::fromStdString(fileName), GET_MAIN_FORMAT_NAME<>().c_str());

          //delete myPlot;
        }
    };
}

#endif //QT_H

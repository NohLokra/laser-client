#include <QApplication>
#include "mainwindow.h"
#include "apiservice.h"

#include "scoreparser.h"

int main( int argc, char** argv )
{
    QApplication app(argc, argv);
    MainWindow mw;

    ScoreParser sp("test");

    mw.show();
    return app.exec();
}

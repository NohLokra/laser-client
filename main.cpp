#include <QApplication>
#include "mainwindow.h"
#include "apiservice.h"

#include "scoreparser.h"

int main( int argc, char** argv )
{
    QApplication app(argc, argv);
    MainWindow mw;

    // Tests
    QFile f("E:/Programmation/C++/Qt/laser_save/LQM_COM_FILE.TXT");
    if ( f.open(QIODevice::ReadOnly) ) {
        QTextStream in(&f);
        QString content;

        while ( !in.atEnd() ) {
            QString line = in.readLine() + "\n";
            content += line;
        }

        ScoreParser sp(content);
    } else {
        throw "File not found";
    }

    //Fin des tests

    mw.show();
    return app.exec();
}

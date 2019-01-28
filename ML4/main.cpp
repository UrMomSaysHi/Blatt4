#include "mainwindow.h"
#include <QApplication>
#include "mnist.h"

using namespace std;
using namespace chrono;

int main(int argc, char *argv[])
{
    MNIST mnist = MNIST("/Users/hannahwendland/Documents/Studium/Bachelor Info/PRG-PR/Blatt4/");
    mnist.testPrintout(40, 60);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();

}

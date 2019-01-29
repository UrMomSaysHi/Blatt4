#include "mainwindow.h"
#include <QApplication>
#include <unistd.h>
#include "mnist.h"
#include "net.h"
#include "utilities.h"

using namespace std;

int main(int argc, char *argv[])
{     
    MNIST mnist = MNIST("../../../../");
    mnist.testPrintout(40, 60);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    w.set_board(mnist.to_matrix(42));

    vector<int> topology = {784,64,10};
    Net nn = Net(topology, *sigmoid0, *dsigmoid0);

    // training to neuronal net (kinda)
    double eta = 0.3;
    double alpha = 0.01;

    int iterations = 100;

    for(int i = 0; i < iterations; i++){
        vector<double> train_vec(mnist.trainingData[i].pixelData.begin(), mnist.trainingData[i].pixelData.end());
        vector<double> label_vec(mnist.trainingData[i].output.begin(), mnist.trainingData[i].output.end());
        nn.train(train_vec, label_vec, alpha, eta);
    }

    return a.exec();
}

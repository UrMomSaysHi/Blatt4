#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <vector>
#include <QMouseEvent>

#include "net.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    vector<vector<float>> board;
    int n_rows = 30;
    int n_cols = 30;

    int recent_row = 0;
    int recent_col = 0;

    int start_pos = 50;

//    vector<int> topology = {784,64,10};
//    Net nn = Net(topology, *sigmoid0, *dsigmoid0);


    vector<vector<float>> empty_board(int nb_cols, int nb_rows);
    float box_height = 300;
    void paintEvent(QPaintEvent *);
//    void mousePressEvent( QMouseEvent*ev);
//    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *ev);
    void set_board(vector<vector<float>> new_board);
    void color_box(float xpos, float ypos);
    bool pressed = false;

    ~MainWindow();



private slots:
    void on_ResetButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

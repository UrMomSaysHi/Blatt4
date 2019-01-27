#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <vector>
#include <QMouseEvent>

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
    int n_rows;
    int n_cols;
    int start_pos = 50;


    vector<vector<float>> empty_board(int size);
    float box_height = 300;
    void paintEvent(QPaintEvent *);
    void mousePressEvent( QMouseEvent*ev);
    void color_box(float xpos, float ypos);
    ~MainWindow();



private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

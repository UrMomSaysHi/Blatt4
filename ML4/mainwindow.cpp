#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    board = empty_board(20);
    n_rows = board.size();
    n_cols = board.back().size();

    ui->setupUi(this); 
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    QPen linepen(QColor("#00e0fc"));

    painter.drawRect(start_pos,start_pos,box_height,box_height);

    float cell_height = box_height/n_rows;
    float cell_width = box_height/n_cols;

    for(int i = 0; i < n_rows; i++){
        for(int j = 0; j < n_cols; j++){
            if(board[i][j] > 0.5){
                painter.setBrush(Qt::black);
            } else {
                painter.setBrush(Qt::white);
            }

            painter.drawRect(start_pos+i*cell_height,
                             start_pos+j*cell_width,
                             cell_height,
                             cell_width);
        }
    }

}

vector<vector<float>> MainWindow::empty_board(int size){
   vector<vector<float>> r_board;
   for(int i = 0; i < size; i++){
       vector<float> row;
       for(int j = 0; j < size; j++){
           row.push_back(0);
       }
       r_board.push_back(row);
   }

   return(r_board);
}


void MainWindow::mousePressEvent(QMouseEvent*ev){
    QPoint point = ev -> pos();

    int xpos =  point.x();
    int ypos =  point.y();

    color_box(xpos, ypos);


//    if (xpos >= img_height || ypos >= img_width){
//        //throw 0;
//    } else {
//        int col = (xpos * ncols)/img_width;
//        int row = (ypos * nrows)/img_height;

//        if (game.currentGeneration[row][col].status == 0){
//            game.currentGeneration[row][col] = Cell(row, col, 1);
//        } else {
//            game.currentGeneration[row][col] = Cell(row, col, 0);
//        }
//    }
    update();

}

void MainWindow::color_box(float xpos, float ypos){
    if (xpos > start_pos && xpos < start_pos + box_height && ypos > start_pos && ypos < start_pos + box_height){
        cout << "Hi"<<endl;
        int col = ((xpos-start_pos) * n_cols)/box_height;
        int row = ((ypos-start_pos) * n_rows)/box_height;

        board[col][row] = 1;

    }
}

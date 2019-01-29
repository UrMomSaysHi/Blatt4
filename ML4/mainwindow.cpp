#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    board = empty_board(n_rows, n_cols);
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

    painter.setBrush(Qt::white);
    painter.drawRect(start_pos,start_pos,box_height,box_height);

    float cell_height = box_height/n_rows;
    float cell_width = box_height/n_cols;

    for(int i = 0; i < n_rows; i++){
        for(int j = 0; j < n_cols; j++){

//            if(board[i][j] == 0){
//                painter.setBrush(Qt::white);
//            } else if (board[i][j] <= 0.5) {
//                painter.setBrush(Qt::black);
//            } else {
//                painter.setBrush(QColor(0, 0, 0, 255*board[i][j]));
//                cout << board[i][j] << endl;
//            }

            int color = 255*board[i][j];
            painter.setBrush(QColor(0, 0, 0, color));
            painter.drawRect(start_pos+j*cell_width,
                             start_pos+i*cell_height,
                             cell_width,
                             cell_height);
        }
    }

}

vector<vector<float>> MainWindow::empty_board(int nb_rows, int nb_cols){
   vector<vector<float>> r_board;
   for(int i = 0; i < nb_rows; i++){
       vector<float> row;
       for(int j = 0; j < nb_cols; j++){
           row.push_back(0);
       }
       r_board.push_back(row);
   }

   return(r_board);
}

//void MainWindow::mouseReleaseEvent(QMouseEvent *){
//    pressed = false;
//    cout << "yo" << endl;
//}


void MainWindow::mouseMoveEvent(QMouseEvent *ev){
        QPoint point = ev -> pos();

        int xpos =  point.x();
        int ypos =  point.y();

        color_box(xpos, ypos);

}

//void MainWindow::mousePressEvent(QMouseEvent*ev){

//    pressed = true;
//    //    QPoint point = ev -> pos();

//    //    int xpos =  point.x();
//    //    int ypos =  point.y();

//    //    color_box(xpos, ypos);


////    if (xpos >= img_height || ypos >= img_width){
////        //throw 0;
////    } else {
////        int col = (xpos * ncols)/img_width;
////        int row = (ypos * nrows)/img_height;

////        if (game.currentGeneration[row][col].status == 0){
////            game.currentGeneration[row][col] = Cell(row, col, 1);
////        } else {
////            game.currentGeneration[row][col] = Cell(row, col, 0);
////        }
////    }
//    update();

//}

void MainWindow::color_box(float xpos, float ypos){
    if (xpos > start_pos && xpos < start_pos + box_height && ypos > start_pos && ypos < start_pos + box_height){
        int col = ((xpos-start_pos) * n_cols)/box_height;
        int row = ((ypos-start_pos) * n_rows)/box_height;

        if(col != recent_col || row != recent_row){

            recent_col = col;
            recent_row = row;

            board[row][col] = 1;

            for(int i = 0; i <= 1; i++){
                int i_col = col + pow(-1,i);
                if (i_col >= 0 && i_col < n_cols){
                    if(board[row][i_col] + 0.25 <= 1){
                        board[row][i_col] = board[row][i_col] + 0.25;
                    }
                }
            }

            for(int i = 0; i <= 1; i++){
                int i_row = row + pow(-1,i);
                if (i_row >= 0 && i_row < n_rows){
                    if(board[i_row][col] + 0.25 <= 1){
                        board[i_row][col] = board[i_row][col] + 0.25;
                    }
                }
            }
        }

        update();

    }
}

void MainWindow::on_ResetButton_clicked()
{
    board = empty_board(n_rows, n_cols);
    update();
}

void MainWindow::set_board(vector<vector<float>> new_board){
    n_rows = new_board.size();
    n_cols = new_board.back().size();
    board = new_board;
    update();
}

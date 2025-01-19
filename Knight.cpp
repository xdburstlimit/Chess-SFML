#include "Knight.h"
#include "Board.h"

Knight::Knight(char colour_param) : Piece((colour_param == 'W')? symbol_param = 'N' : symbol_param = 'n', colour_param){
 
}

bool Knight::isValidMove(int x_i, int y_i, int x_f, int y_f, Board& board, char colour_param){
    bool valid = false;
    if((x_f == x_i + 2) && (y_f == y_i + 1)||(x_f == x_i - 2) && (y_f == y_i + 1)||(x_f == x_i + 2) && (y_f == y_i - 1)||(x_f == x_i - 2) && (y_f == y_i - 1)){
        if(board.getSquare(x_f,y_f)!=nullptr){// checks desitination point
            valid = false;
            if(board.getColourB(x_i,y_i) != board.getColourB(x_f,y_f) ){// capture logic
                valid = true;
            }
        }else if(board.getSquare(x_f,y_f) == nullptr){
            valid = true;
        }   
    }  

    if(((x_f == x_i - 1) && (y_f == y_i + 2) )||( (x_f == x_i + 1) && (y_f == y_i + 2) )||( (x_f == x_i + 1) && (y_f == y_i - 2) )||( (x_f == x_i - 1) && (y_f == y_i - 2) )){
        if(board.getSquare(x_f,y_f)!=nullptr){// checks desitination point
            valid = false;
            if(board.getColourB(x_i,y_i) != board.getColourB(x_f,y_f) ){// capture logic
                valid = true;
            }
        }else if(board.getSquare(x_f,y_f) == nullptr){
            valid = true;
        }    
    }
    return valid;
}

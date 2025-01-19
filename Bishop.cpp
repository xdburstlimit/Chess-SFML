#include "Bishop.h"
#include "Board.h"

Bishop::Bishop(char colour_param) : Piece((colour_param == 'W')? symbol_param = 'B' : symbol_param = 'b', colour_param){

}

bool Bishop::isValidMove(int x_i, int y_i, int x_f, int y_f, Board& board,char colour_param){
    bool valid = false;
    int odC = y_i - x_i;
    int dC = x_i + y_i;   //y = mx + c
    if(y_f == x_f + odC){
        int n = y_f - y_i; //if positive on the rhs of the piece,lhs otherwise
        if(n > 0){
            int j{};
            for(int i{x_i + 1};i <= x_f;++i){
                j = i + odC;
                if(board.getSquare(i,j)!=nullptr){// checks gap between two points excluding the beginning and ending points
                    valid = false;
                    if(j == y_f){// capture logic
                        if(board.getColourB(x_i,y_i) != board.getColourB(x_f,y_f) ){
                            valid = true;
                        }
                    }
                    break;
                }else if(board.getSquare(i,j) == nullptr){
                    valid = true;
                }

            }    
        }
        if(n < 0){
            int j{};
            for(int i{x_i - 1};i >= x_f; --i){
                j = i + odC;
                
                if(board.getSquare(i,j)!=nullptr){// checks gap between two points excluding the beginning and ending points
                    valid = false;
                    if(j == y_f){// capture logic
                        if(board.getColourB(x_i,y_i) != board.getColourB(x_f,y_f) ){
                            valid = true;
                        }
                    }
                    break;
                }else if(board.getSquare(i,j) == nullptr){
                    valid = true;
                }

            }    
        }
    } 
    if(y_f == -x_f + dC){
        int n = y_f - y_i;
        if(n > 0){//rhs of the piece
            int j{};
            for(int i{x_i - 1};i >= x_f; --i){
                j = -i + dC;
                if(board.getSquare(i,j)!=nullptr){// checks gap between two points excluding the beginning and ending points
                    valid = false;
                    if(j == y_f){// capture logic
                        if(board.getColourB(x_i,y_i) != board.getColourB(x_f,y_f) ){
                            valid = true;
                        }
                    }
                    break;
                }else if(board.getSquare(i,j) == nullptr){
                    valid = true;
                }

            }  
 
            
        }
        if(n < 0){//lhs of the piece
            int j{};
            for(int i{x_i + 1};i <= x_f;++i){
                j = -i + dC;
                if(board.getSquare(i,j)!=nullptr){// checks gap between two points excluding the beginning and ending points
                    valid = false;
                    if(j == y_f){// capture logic
                        if(board.getColourB(x_i,y_i) != board.getColourB(x_f,y_f) ){
                            valid = true;
                        }
                    }
                    break;
                }else if(board.getSquare(i,j) == nullptr){
                    valid = true;
                }

            } 

        }


    }
    return valid;
}
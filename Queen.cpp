#include "Queen.h"
#include "Board.h"

Queen::Queen(char colour_param) : Piece((colour_param == 'W')? symbol_param = 'Q' : symbol_param = 'q', colour_param){
    
}

bool Queen::isValidMove(int x_i, int y_i, int x_f, int y_f, Board& board, char colour_param){
    bool valid = false;
    int dC = x_i + y_i;   //y = mx + c
    int odC = y_i - x_i;
    if(y_f == x_f + odC){//bishop code
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

    if(x_f == x_i){//rook code
        int n = y_f - y_i;
        if(n > 0){ // this is for rhs of rook
            for(int j{y_i+1}; j <= y_f ; ++j){
                //y_i+1: doesnt start at the piece itself;
                //<= y_f: to go a specific point and not end before the point
                if(board.getSquare(x_i,j)!=nullptr){// checks gap between two points excluding the beginning and ending points
                    valid = false;
                    if(j==y_f){// capture logic
                        if(board.getColourB(x_i,y_i) != board.getColourB(x_f,y_f) ){
                            valid = true;
                        }
                    }
                    break;
                }else if(board.getSquare(x_i,j) == nullptr){
                    valid = true;
                }
            }
 
        }
        
        if(n < 0){
            for(int j{y_i-1}; j >= y_f ; --j){
                //y_i-1: doesnt start at the piece itself;
                //>= y_f: to go a specific point and not end before the point
                if(board.getSquare(x_i,j)!=nullptr){// checks gap between two points excluding the beginning and ending points
                    valid = false;
                    if(j==y_f){// capture logic
                        if(board.getColourB(x_i,y_i) != board.getColourB(x_f,y_f) ){
                            valid = true;
                        }
                    }
                    break;
                }else if(board.getSquare(x_i,j) == nullptr){
                    valid = true;
                }
            }
            
        }
        
    }

    if(y_f == y_i){
        int n = x_f - x_i;
        if(n > 0){ 
            for(int i{x_i + 1}; i <= x_f; ++i){
                if(board.getSquare(i,y_i)!=nullptr){// checks gap between two points excluding the beginning and ending points
                    valid = false;
                    if(i==x_f){// capture logic
                        if(board.getColourB(x_i,y_i) != board.getColourB(x_f,y_f) ){
                            valid = true;
                        }
                    }
                    break;
                }else if(board.getSquare(i,y_i) == nullptr){
                    valid = true;
                }
            }

        }
        if(n < 0){
            for(int i{x_i-1}; i >= x_f ; --i){
                if(board.getSquare(i,y_i)!=nullptr){// checks gap between two points excluding the beginning and ending points
                    valid = false;
                    if(i == x_f){// capture logic
                        if(board.getColourB(x_i,y_i) != board.getColourB(x_f,y_f) ){
                            valid = true;
                        }
                    }
                    break;
                }else if(board.getSquare(i,y_i) == nullptr){
                    valid = true;
                }
            }

        }

    }
    return valid;
}
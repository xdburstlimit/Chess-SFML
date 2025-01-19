#include "King.h"
#include "Board.h"
#include <cmath>

King::King(char colour_param) : Piece((colour_param == 'W')? symbol_param = 'K' : symbol_param = 'k', colour_param){

}

bool King::isKingSafe(int x_i, int y_i,int x_f, int y_f, Board& board){
    
    Piece* temp =nullptr;
    Piece* king = board.getSquare(x_i, y_i);
    std::pair <int,int> enemy_pieces[16];
    std::pair <int,int> friendly_pieces[16];
    bool safe{true};
    int count1{};
    int count{};
    char king_colour = board.getColourB(x_i, y_i);
    char attack_colour = ' ';
    //find enemy pieces
    if(king_colour == 'B'){
        for(int i{}; i < 8; ++i){
            for(int j{}; j < 8; ++j){
                if(board.getSquare(i, j)!= nullptr && board.getColourB(i, j)!= king_colour){
                    if(board.getSymbolB(i, j)!='K'){
                        enemy_pieces[count] = {i , j};
                        ++count;
                    }

                }
            }
        }

        

        if(count != 0){
            if(board.getSquare(x_f, y_f) != nullptr && king_colour != board.getColourB(x_f, y_f)){
                temp = board.getSquare(x_f,y_f);
                attack_colour = board.getColourB(enemy_pieces[0].first, enemy_pieces[0].second);
                board.setNull(x_f,y_f);
                board.initPiece(x_f,y_f, king);
                for(int i{}; i < count; ++i){
                    if(board.isValidMoveB(enemy_pieces[i].first, enemy_pieces[i].second, x_f,y_f, attack_colour)){
                        safe = false;
                        break;
                    }
                }
                board.setNull(x_f,y_f);
                board.initPiece(x_f,y_f, temp);
            }

            if(board.getSquare(x_f, y_f) == nullptr){
                attack_colour = board.getColourB(enemy_pieces[0].first, enemy_pieces[0].second);
                
                board.initPiece(x_f,y_f, king);
                board.setNull(x_i,y_i);
            
                for(int i{}; i < count ; ++i){
                    if(board.isValidMoveB(enemy_pieces[i].first, enemy_pieces[i].second, x_f,y_f, attack_colour)){
                        safe = false;
                        break;
                    }
                }
                board.initPiece(x_i,y_i, king);
                board.setNull(x_f,y_f);
            }
        }
    } else if(king_colour == 'W'){
        //find enemy pieces
        for(int i{}; i < 8; ++i){
            for(int j{}; j < 8; ++j){
                if(board.getSquare(i, j)!= nullptr && board.getColourB(i, j)!= king_colour){
                    if(board.getSymbolB(i, j)!='k'){
                        enemy_pieces[count] = {i , j};
                        ++count;
                    }

                }
            }
        }

        

        if(count != 0){
            if(board.getSquare(x_f, y_f) != nullptr && king_colour != board.getColourB(x_f, y_f)){
                temp = board.getSquare(x_f,y_f);
                attack_colour = board.getColourB(enemy_pieces[0].first, enemy_pieces[0].second);
                board.setNull(x_f,y_f);
                board.initPiece(x_f,y_f, king);
                for(int i{}; i < count; ++i){
                    if(board.isValidMoveB(enemy_pieces[i].first, enemy_pieces[i].second, x_f,y_f, attack_colour)){
                        safe = false;
                        break;
                    }
                }
                board.setNull(x_f,y_f);
                board.initPiece(x_f,y_f, temp);
            }

            if(board.getSquare(x_f, y_f) == nullptr){
                attack_colour = board.getColourB(enemy_pieces[0].first, enemy_pieces[0].second);
                
                board.initPiece(x_f,y_f, king);
                board.setNull(x_i,y_i);
            
                for(int i{}; i < count ; ++i){
                    if(board.isValidMoveB(enemy_pieces[i].first, enemy_pieces[i].second, x_f,y_f, attack_colour)){
                        safe = false;
                        break;
                    }
                }
                board.initPiece(x_i,y_i, king);
                board.setNull(x_f,y_f);
            }
        }

    }




    return safe;
}

bool King::isValidMove(int x_i, int y_i, int x_f, int y_f, Board& board, char colour_param){//colour_param = currentPlayer colour
    bool valid = false;
    bool found_king{false};
    int found_king_x{};
    int found_king_y{};
    for(int i{}; i < 8; ++i){
        for(int j {}; j < 8; ++j){
            if(board.getSquare(i, j) != nullptr && colour_param != board.getColourB(i, j) &&board.getSymbolB(i, j) == 'K'){
                found_king_x = i;
                found_king_y = j;
                found_king = true;
                break;
            }else if(board.getSquare(i, j) != nullptr && colour_param != board.getColourB(i, j) &&board.getSymbolB(i, j) == 'k'){
                found_king_x = i;
                found_king_y = j;
                found_king = true;
                break;
            }
        }
        if(found_king){
            break;
        }
    }
    
    if(abs(x_f - found_king_x) <= 1 && abs(y_f - found_king_y) <=1){
        return false;
    }
    if((x_f == x_i - 1) && (y_f == y_i)||(x_f == x_i) && (y_f == y_i + 1)||(x_f == x_i + 1) && (y_f == y_i)||(x_f == x_i) && (y_f == y_i - 1)){
        if(isKingSafe(x_i, y_i, x_f, y_f, board) && board.getSquare(x_f,y_f)!=nullptr ){// checks desitination point and needs a different functio
            valid = false;
            if(isKingSafe(x_i, y_i, x_f, y_f, board) && (board.getColourB(x_i,y_i) != board.getColourB(x_f,y_f)) ){// capture logic also needs &&isKingSafe(x_f,y_f)
                valid = true;
            }
        }else if( isKingSafe(x_i, y_i, x_f, y_f, board) && board.getSquare(x_f,y_f) == nullptr  ){// &&isKingSafe(x_f,y_f)
            valid = true;
        }    
    }  
    if(((x_f == x_i - 1) && (y_f == y_i - 1) )||( (x_f == x_i + 1) && (y_f == y_i + 1) )||( (x_f == x_i + 1) && (y_f == y_i - 1) )||( (x_f == x_i - 1) && (y_f == y_i + 1) )){
        if( isKingSafe(x_i, y_i, x_f, y_f, board) && board.getSquare(x_f,y_f)!=nullptr){// checks desitination point
            valid = false;
            if(isKingSafe(x_i, y_i, x_f, y_f, board) && (board.getColourB(x_i,y_i) != board.getColourB(x_f,y_f)) ){// capture logic
                valid = true;
            }
        }else if(isKingSafe(x_i, y_i, x_f, y_f, board) && board.getSquare(x_f,y_f) == nullptr ){
            valid = true;
        }    
    }
    //castling code
    if(x_f == x_i && y_f == y_i - 2){
        if(board.getSquare(x_i, y_i) != nullptr && board.getSquare(x_i , 0) != nullptr){//lhs rook
            if(isKingSafe(x_i, y_i, x_i, y_i-2,board) && board.getSquare(x_i,y_i)->getisMoved()==false && board.getSquare(x_i,0)->getisMoved()==false){
                if(board.getSquare(x_i, y_i - 1) == nullptr && board.getSquare(x_i, y_i - 2) == nullptr && board.getSquare(x_i, y_i - 3)== nullptr){
                    valid = true;
                    board.getSquare(x_i,y_i)->setCastled();
                }
            }
        }
    } else if(x_f == x_i && y_f == y_i + 2){
        if(board.getSquare(x_i, y_i) != nullptr && board.getSquare(x_i , 7) != nullptr){//lhs rook
            if(isKingSafe(x_i, y_i, x_i, y_i + 2,board) && board.getSquare(x_i,y_i)->getisMoved()==false && board.getSquare(x_i,7)->getisMoved()==false){
                if(board.getSquare(x_i, y_i + 1) == nullptr && board.getSquare(x_i, y_i + 2) == nullptr){
                    valid = true;
                    board.getSquare(x_i,y_i)->setCastled();
                }
            }
        }

    }
    
    
    return valid;
}

 
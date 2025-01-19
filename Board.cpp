#include "Board.h"
#include "Pawn.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Player.h"
#include <iostream>
#include <iomanip>

Board::Board(){//x y (is default positions)
    char white = 'W';
    char black = 'B';

    // *** WHITE PIECES ***

    initPiece(7, 4, new King(white)); // 7 4

    initPiece(7, 3, new Queen(white));// 7 3

    initPiece(7, 0, new Rook(white));// 7 0
    initPiece(7, 7, new Rook(white));// 7 7
    

    initPiece(7, 2, new Bishop(white));// 7 2
    initPiece(7, 5, new Bishop(white));// 7 5

    initPiece(7, 1, new Knight(white));// 7 1
    initPiece(7, 6, new Knight(white));// 7 6

  
    for(int j{}; j < dim; ++j){
        initPiece(6 , j, new Pawn(white)); // 6, 0 <= j < 8 default
    }

    // *** BLACK PIECES ***

    initPiece(0, 4, new King(black)); // 0 4
 
    initPiece(0, 3, new Queen(black));// 0 3

    initPiece(0, 0, new Rook(black));// 0 0
    initPiece(0, 7, new Rook(black));// 0 7

    initPiece(0, 2, new Bishop(black));// 0 2
    initPiece(0, 5, new Bishop(black));// 0 5

    initPiece(0, 1, new Knight(black));// 0 1
    initPiece(0, 6, new Knight(black));// 0 6
    
    for(int j{}; j < dim; ++j){
        initPiece(1 , j, new Pawn(black));//1, 0 <= j < 8 is default
    }

}


void Board::printBoard(){
    for(int i{}; i < dim; ++i){
        for(int j{}; j < dim; ++j){
            if(getSquare(i, j) == nullptr){
                std::cout << std::setw(2) << '.';
            }
            else {
                getSquare(i,j)->display();
            }          
        }
        std::cout << '\n';
    }
}

void Board::movePiece(int x_i, int y_i, int x_f, int y_f){
    if(getSquare(x_f,y_f)!=nullptr){ // code for when piece is getting taken
        setTaken(x_f,y_f);
    }

    if(getSymbolB(x_i, y_i) == 'P'|| getSymbolB(x_i, y_i) == 'p'){
        if((x_i - 1 == x_f && y_i - 1 == y_f) || (x_i - 1 == x_f && y_i + 1 == y_f) || (x_i + 1 == x_f && y_i - 1 == y_f ||x_i + 1 == x_f && y_i + 1 == y_f)){
            takeEnPassant(x_i, y_i, x_f, y_f);
        }
    }


    if(getSymbolB(x_i, y_i) == 'K'|| getSymbolB(x_i, y_i) == 'k'){   
        castleRook(x_i, y_i, x_f, y_f);
    }
    
    setSquare(x_f, y_f, x_i, y_i);

    if(getSquare(x_i, y_i)->getisMoved() == false){// setting if a piece has been moved
        getSquare(x_f, y_f)->setMoved();
    }

    setNull(x_i, y_i);
}

void Board::castleRook(int x_i, int y_i, int x_f, int y_f){
    if(getSquare(x_i, y_i)->getCastled() == true && getCastle_onceW() == true){//code to move Rook if castling takes place.
        setCastle_onceW();
        if(y_i > y_f){
            setSquare(x_f, y_i-1, x_f, 0);
            setNull(x_f, 0);
        }else if(y_i < y_f){
            setSquare(x_f, y_i+1, x_f, 7);
            setNull(x_f, 7);
        }
    } else if(getSquare(x_i, y_i)->getCastled() == true && getCastle_onceB() == true){
        setCastle_onceB();
        if(y_i > y_f){
            setSquare(x_f, y_i-1, x_f, 0);
            setNull(x_f, 0);
        }else if(y_i < y_f){
            setSquare(x_f, y_i+1, x_f, 7);
            setNull(x_f, 7);
        }
    }

}

void Board::takeEnPassant(int x_i, int y_i, int x_f, int y_f){
    if(getSquare(x_f+1,y_f)!=nullptr && getSquare(x_f+1,y_f)->getenPassant() == true){
        if(getSymbolB(x_i, y_i) == 'P' && getSymbolB(x_f+1,y_f) == 'p'){
            setTaken(x_f+1,y_f);
        }
    }
    if(getSquare(x_f-1,y_f)!= nullptr  && getSquare(x_f-1,y_f)->getenPassant() == true){
        if(getSymbolB(x_i, y_i) == 'p' && getSymbolB(x_f-1,y_f) == 'P'){
            setTaken(x_f-1,y_f);     
        }
    }
}

void Board::pawnPromotion(int x, int y, const std::string& pieceType,char colour){
    if (pieceType == "queen") {
        setTaken(x,y);
        initPiece(x,y, new Queen(colour)); // Replace with a Queen object
    } else if (pieceType == "rook") {
        setTaken(x,y);
        initPiece(x,y, new Rook(colour));
    } else if (pieceType == "bishop") {
        setTaken(x,y);
        initPiece(x,y, new Bishop(colour));
    } else if (pieceType == "knight") {
        setTaken(x,y);
        initPiece(x,y, new Knight(colour));
    }
}

bool Board::isCheck(char colour,int& attack_x, int& attack_y, int& k_x, int& k_y, bool& double_check){//player colour and coordinates of  king piece
    bool king_check{false};
    
    if(colour == 'B'){// if colour b made a move check if White is in check after that move
        bool found{false};
        for(int i{}; i < 8; ++i){ // code to find king on board
            for(int j{}; j < 8; ++j){
                if(getSquare(i, j) != nullptr){
                    if(getSquare(i, j) -> getSymbol() == 'K'){
                        k_x = i;
                        k_y = j;
                        found = true;
                        break;
                    }
                }
            }
            if(found == true){
                std::cout << "found W king\n";
                break;
            }
        }
        char attack_colour{' '};
        int count{};
        for(int i{}; i < 8; ++i){
            for(int j{}; j < 8; ++j){
                if(getSquare(i, j) != nullptr){
                    if(getColourB(k_x, k_y) != getColourB(i, j)){ 
                        attack_colour = getColourB(i, j);
                        if(getSquare(i, j)->isValidMove(i, j, k_x, k_y, *this, attack_colour)){
                            attack_x = i;
                            attack_y = j;
                            king_check = true;
                            ++count;
                        }
                    }
                }
            } 
        }

        if(king_check == true){// to break out of outer loop
            std::cout << "White King is in check" << '\n';
        }
        if(count >= 2){
            double_check = true;
            std::cout << "King is double checked." << '\n';
        }

    }else if(colour == 'W'){// if white made a move check if Black king is in check
        bool found{false};
        for(int i{}; i < 8; ++i){ // code to find king on board
            for(int j{}; j < 8; ++j){
                if(getSquare(i, j) != nullptr){
                    if(getSquare(i, j) -> getSymbol() == 'k'){
                        k_x = i;
                        k_y = j;
                        found = true;
                        break;
                    }
                }
            }
            if(found == true){
                std::cout << "found B king\n";
                break;
            }
        }
        char attack_colour{' '};
        int count{};
        for(int i{}; i < 8; ++i){
            for(int j{}; j < 8; ++j){
                if(getSquare(i, j) != nullptr){
                    if(getColourB(k_x, k_y) != getColourB(i, j)){ 
                        attack_colour = getColourB(i, j);
                        if(getSquare(i, j)->isValidMove(i, j, k_x, k_y, *this, attack_colour)){
                            attack_x = i;
                            attack_y = j;
                            king_check = true;
                            ++count;
                        }
                    }
                }
            }
        }
        if(king_check == true){
            std::cout << "Black King is in check" << '\n';
        }
        if(count >= 2){
            double_check = true;
            std::cout << "King is double checked." << '\n';
        }

    }
    
    return king_check;
}

bool Board::isCheckmate(char colour){//attacking colour

    bool king_checkmate{false};
    bool found{false};
    int k_x{};
    int k_y{};
    bool b1{false};
    bool b2{false};
    bool b3{false};
    bool b4{false};
    bool b5{false};
    bool b6{false};
    bool b7{false};
    bool b8{false};

    if(colour == 'B'){
        for(int i{}; i < 8; ++i){
            for(int j{}; j < 8; ++j){
                if(getSquare(i,j) != nullptr && getSymbolB(i, j) == 'K'){
                    k_x = i;
                    k_y = j;
                    found = true;
                    break;
                }
            }
            if(found == true){
                break;
            }
        }
    }else if(colour == 'W'){
        for(int i{}; i < 8; ++i){
            for(int j{}; j < 8; ++j){
                if(getSquare(i,j) != nullptr && getSymbolB(i, j) == 'k'){
                    k_x = i;
                    k_y = j;
                    found = true;
                    break;
                }
            }
            if(found == true){
                break;
            }
        }

    }
        
    if(k_x - 1 >= 0){
        
        if((k_y - 1)>=0 && (getSquare(k_x - 1, k_y - 1) == nullptr) ||getSquare(k_x-1,k_y-1) != nullptr && getColourB(k_x, k_y) != getColourB(k_x-1,k_y-1) ){
            b1 = isKingSafeB(k_x, k_y, k_x - 1, k_y - 1);
            
        }
        if(k_y + 1 < 8 && (getSquare(k_x - 1, k_y + 1) == nullptr ||getSquare(k_x-1,k_y+1) != nullptr && getColourB(k_x, k_y) != getColourB(k_x-1,k_y+1))){
            b2 =isKingSafeB(k_x, k_y, k_x - 1, k_y + 1); 
            
        }
        if(getSquare(k_x - 1, k_y) == nullptr ||getSquare(k_x-1,k_y) != nullptr && getColourB(k_x, k_y) != getColourB(k_x-1,k_y)){
            b3 = isKingSafeB(k_x, k_y, k_x - 1, k_y);
        }
    }

    if( (k_x + 1 < 8) ){
        
        if((k_y - 1)>= 0 &&((getSquare(k_x + 1, k_y - 1) == nullptr)  ||getSquare(k_x+1,k_y-1) != nullptr && getColourB(k_x, k_y) != getColourB(k_x+1,k_y-1))){
            b4 = isKingSafeB(k_x, k_y, k_x + 1, k_y - 1);
            
        }
        if(k_y + 1 < 8 && ((getSquare(k_x + 1, k_y + 1) == nullptr  ||getSquare(k_x+1,k_y+1) != nullptr && getColourB(k_x, k_y) != getColourB(k_x+1,k_y+1))) ){
            b5 = isKingSafeB(k_x, k_y, k_x + 1, k_y + 1 );
            
        }
        if(getSquare(k_x + 1, k_y) == nullptr  ||getSquare(k_x+1,k_y) != nullptr && getColourB(k_x, k_y) != getColourB(k_x+1,k_y)){
            b6 = isKingSafeB(k_x, k_y, k_x + 1, k_y);
        }
    
    }

    if(k_y - 1 >= 0  && ((getSquare(k_x, k_y - 1) == nullptr)  ||getSquare(k_x,k_y-1) != nullptr && getColourB(k_x, k_y) != getColourB(k_x,k_y-1))){//k_x
        b7 = isKingSafeB(k_x, k_y, k_x , k_y - 1);
        
    }
    if(k_y + 1 < 8 && ((getSquare(k_x, k_y + 1) == nullptr)  ||getSquare(k_x,k_y+1) != nullptr && getColourB(k_x, k_y) != getColourB(k_x,k_y+1))){
        b8 = isKingSafeB(k_x, k_y, k_x , k_y + 1);
    }

    // i think this is probably the worst thing i have ever coded, lord please forgive me
    if(b1 == false && b2 == false && b3 == false && b4 == false && b5 == false && b6 == false && b7 == false && b8 == false){
        king_checkmate = true;
    }
    return king_checkmate;
}

bool Board::isKingSafeB(int x_i, int y_i,int x_f, int y_f){
    Piece* temp = nullptr;
    Piece* temp1 = nullptr;
    Piece* king = getSquare(x_i, y_i);
    std::pair <int,int> enemy_pieces[16];
    bool safe{true};
    int count{};
    char king_colour = getColourB(x_i, y_i);
    char attack_colour = ' ';
    if(x_i == x_f && y_i == y_f){
        return true;
    }
    //find enemy pieces

    if(king_colour == 'W'){
        for(int i{}; i < 8; ++i){
            for(int j{}; j < 8; ++j){
                if(getSquare(i, j)!= nullptr && king_colour != getColourB(i, j)){
                    if(getSymbolB(i, j) != 'k'){
                        enemy_pieces[count] = {i , j};
                        ++count;
                    }
                }
            }
        }
    }else if(king_colour == 'B'){
        for(int i{}; i < 8; ++i){
            for(int j{}; j < 8; ++j){
                if(getSquare(i, j)!= nullptr && king_colour != getColourB(i, j)){
                    if(getSymbolB(i, j)!='K'){
                        enemy_pieces[count] = {i , j};
                        ++count;
                    }
                }
            }
        }

    }
        
    if(count != 0){
        if(getSquare(x_f, y_f) != nullptr && king_colour != getColourB(x_f, y_f)){
            temp = getSquare(x_f,y_f);
            attack_colour = getColourB(enemy_pieces[0].first, enemy_pieces[0].second);
            setNull(x_f,y_f);
            initPiece(x_f,y_f, king);
            for(int i{}; i < count; ++i){
                if(isValidMoveB(enemy_pieces[i].first, enemy_pieces[i].second, x_f,y_f, attack_colour)){
                    safe = false;
                    break;
                }
            }
            setNull(x_f,y_f);
            initPiece(x_f,y_f, temp);
        }
        if(getSquare(x_f, y_f) == nullptr){
            attack_colour = getColourB(enemy_pieces[0].first, enemy_pieces[0].second);

            initPiece(x_f,y_f, king);
            setNull(x_i,y_i);
            for(int i{}; i < count; ++i){
                if(isValidMoveB(enemy_pieces[i].first, enemy_pieces[i].second, x_f,y_f, attack_colour)){

                    safe = false;
                    break;
                }
            }
            initPiece(x_i,y_i, king);
            setNull(x_f,y_f);
        }
    }

    return safe;
}

bool Board::isStalemate(char colour, int k_x, int k_y){
    //add b9 which is for if position is unchanged idk
    
    bool stale_mate{false};
    bool b1{false};
    bool b2{false};
    bool b3{false};
    bool b4{false};
    bool b5{false};
    bool b6{false};
    bool b7{false};
    bool b8{false};

        if(k_x - 1 >= 0){
            
            if((k_y - 1)>=0 ){
                b1 = isKingSafeB(k_x, k_y, k_x - 1, k_y - 1);
                
            }
            if(k_y + 1 < 8 ){
                b2 =isKingSafeB(k_x, k_y, k_x - 1, k_y + 1); 
                  
            }
            b3 = isKingSafeB(k_x, k_y, k_x - 1, k_y);
            
        }

        if( (k_x + 1 < 8) ){
            
            if((k_y - 1)>= 0 ){
                b4 = isKingSafeB(k_x, k_y, k_x + 1, k_y - 1);
                
            }
            if(k_y + 1 < 8 ){
                b5 = isKingSafeB(k_x, k_y, k_x + 1, k_y + 1 );
                   
            }
            b6 = isKingSafeB(k_x, k_y, k_x + 1, k_y);
           

        }

        if(k_y - 1 >= 0 ){//k_x
            b7 = isKingSafeB(k_x, k_y, k_x , k_y - 1);
            
        }
        if(k_y + 1 < 8 ){
           b8 = isKingSafeB(k_x, k_y, k_x , k_y + 1);
        }
         if(b1 == false && b2 == false && b3 == false && b4 == false && b5 == false && b6 == false && b7 == false && b8 == false){
            stale_mate = true;
            std::cout << "Stalemate: draw " << '\n';
        }

    
    return stale_mate;
}

bool Board::blockCheckPossible(char colour,int& count_select,std::pair<int,int> pieces_block[128], std::pair<int,int> moves[128],int attack_x, int attack_y, int k_x, int k_y){
    bool possible{false};
    char enemy_colour{};                     
    int count{};
    std::pair<int,int> pieces_avail[128];
    for(int i{}; i < 8; ++i){//code to find all pieces currently on the board
        for(int j{}; j < 8; ++j){
            if(getSquare(i, j) != nullptr && getColourB(i, j) != colour){ 
                pieces_avail[count].first = i;
                pieces_avail[count].second = j;
                ++count;
            }
        }
    }
    int count_move{};
    if(colour == 'B'){
        enemy_colour = 'W';
    }else if(colour == 'W'){
        enemy_colour = 'B';
    }
    for(int k{}; k < 128; ++k){// need to write this better and not using 3 128 arrays(128 because 16 pieces can move in 8 possible direction, probably a brutal overestimation but yeah)
        if(k != 0){
            if(pieces_avail[k].first == 0 && pieces_avail[k].second == 0){
                break;
            }
        }
        
        if(attack_x == k_x){// i guess the cool thing is that k index correspondence between the pieces_block and moves array with this code
            if(k_y < attack_y){
                for(int j{k_y+1}; j <= attack_y; ++j){
                    if(getSquare(pieces_avail[k].first, pieces_avail[k].second)!= nullptr && isValidMoveB(pieces_avail[k].first,pieces_avail[k].second,k_x,j,enemy_colour)== true){
                        possible = true;
                        pieces_block[count_select] = pieces_avail[k];
                        moves[count_move]= std::make_pair(k_x,j);
                        std::cout << "Move piece: (" << pieces_avail[k].first << ", " << pieces_avail[k].second << ')' <<
                            " to (" << moves[count_move].first << ", " << moves[count_move].second << ") to block check. " << '\n';
                        ++count_move; 
                        ++count_select;
                    }   
                }
            }

            if(attack_y < k_y){
                for(int j{k_y-1}; j >= attack_y; --j){
                    if(getSquare(pieces_avail[k].first, pieces_avail[k].second)!= nullptr && isValidMoveB(pieces_avail[k].first,pieces_avail[k].second,k_x,j,enemy_colour)== true){
                        possible = true;
                        pieces_block[count_select] = pieces_avail[k];
                        moves[count_move]= std::make_pair(k_x,j);
                        std::cout << "Move piece: (" << pieces_avail[k].first << ", " << pieces_avail[k].second << ')' <<
                            " to (" << moves[count_move].first << ", " << moves[count_move].second << ") to lift check. " << '\n';
                        ++count_move; 
                        ++count_select;
                    }  
                }
                
            }
        }

        if(attack_y == k_y){
            if(attack_x < k_x){
                for(int i{k_x-1}; i >= attack_x; --i){
                    if(getSquare(pieces_avail[k].first, pieces_avail[k].second)!= nullptr && isValidMoveB(pieces_avail[k].first, pieces_avail[k].second, i, k_y, enemy_colour) == true){
                        possible = true;
                        pieces_block[count_select] = pieces_avail[k];
                        moves[count_move]= std::make_pair(i, k_y);
                        std::cout << "Move piece: (" << pieces_avail[k].first << ", " << pieces_avail[k].second << ')' <<
                            " to (" << moves[count_move].first << ", " << moves[count_move].second << ") to lift check. " << '\n';
                        ++count_move; 
                        ++count_select;
                    }
                }
            }

            if(k_x < attack_x){
                for(int i{k_x+1}; i <= attack_x; ++i){
                    if(getSquare(pieces_avail[k].first, pieces_avail[k].second)!=nullptr && isValidMoveB(pieces_avail[k].first, pieces_avail[k].second, i, k_y, enemy_colour) == true){
                        possible = true;
                        pieces_block[count_select] = pieces_avail[k];
                        moves[count_move]= std::make_pair(i, k_y);
                        std::cout << "Move piece: (" << pieces_avail[k].first << ", " << pieces_avail[k].second << ')' <<
                            " to (" << moves[count_move].first << ", " << moves[count_move].second << ") to lift check. " << '\n';
                        ++count_move; 
                        ++count_select;
                    }
                }
            }

        }

        
            
        int dC = k_x + k_y;
        if(attack_y == -attack_x + dC){
            if(attack_x < k_x){
                for(int i{k_x - 1}; i >= attack_x ; --i){
                    int j = -i + dC;
                    if(getSquare(pieces_avail[k].first, pieces_avail[k].second)!=nullptr && isValidMoveB(pieces_avail[k].first, pieces_avail[k].second, i, j, enemy_colour)==true){
                        possible = true;
                        pieces_block[count_select] = pieces_avail[k];
                        moves[count_move]= std::make_pair(i, j);
                        std::cout << "Move piece: (" << pieces_avail[k].first << ", " << pieces_avail[k].second << ')' <<
                            " to (" << moves[count_move].first << ", " << moves[count_move].second << ") to lift check. " << '\n';
                        ++count_move; 
                        ++count_select;
                    }
                }
            }

            if(k_x < attack_x){
                for(int i{k_x + 1}; i <= attack_x; ++i){
                    int j = -i + dC;
                    if(getSquare(pieces_avail[k].first, pieces_avail[k].second)!=nullptr && isValidMoveB(pieces_avail[k].first, pieces_avail[k].second, i, j, enemy_colour)==true){
                        possible = true;
                        pieces_block[count_select] = pieces_avail[k];
                        moves[count_move]= std::make_pair(i, j);
                        std::cout << "Move piece: (" << pieces_avail[k].first << ", " << pieces_avail[k].second << ')' <<
                            " to (" << moves[count_move].first << ", " << moves[count_move].second << ") to lift check. " << '\n';
                        ++count_move; 
                        ++count_select;
                    }

                }
            }
        
        }

        int odC = k_y - k_x;
        if(attack_y == attack_x + odC){
            if(attack_x < k_x){
                for(int i{k_x - 1}; i >= attack_x ; --i){
                    int j = i + odC;
                    if(getSquare(pieces_avail[k].first, pieces_avail[k].second)!=nullptr && isValidMoveB(pieces_avail[k].first, pieces_avail[k].second, i, j, enemy_colour)==true){
                        possible = true;
                        pieces_block[count_select] = pieces_avail[k];
                        moves[count_move]= std::make_pair(i, j);
                        std::cout << "Move piece: (" << pieces_avail[k].first << ", " << pieces_avail[k].second << ')' <<
                            " to (" << moves[count_move].first << ", " << moves[count_move].second << ") to lift check. " << '\n';
                        ++count_move; 
                        ++count_select;
                    }
                }
            }

            if(k_x < attack_x){
                for(int i{k_x + 1}; i <= attack_x; ++i){
                    int j = i + odC;
                    if(getSquare(pieces_avail[k].first, pieces_avail[k].second)!=nullptr && isValidMoveB(pieces_avail[k].first, pieces_avail[k].second, i, j, enemy_colour)==true){
                        possible = true;
                        pieces_block[count_select] = pieces_avail[k];
                        moves[count_move]= std::make_pair(i, j);
                        std::cout << "Move piece: (" << pieces_avail[k].first << ", " << pieces_avail[k].second << ')' <<
                            " to (" << moves[count_move].first << ", " << moves[count_move].second << ") to lift check. " << '\n';
                        ++count_move; 
                        ++count_select;
                    }

                }
            }

        }
    }

    //seperate king logic to get rid of check
    
    ++count_move;
    ++count_select;
    if(k_x - 1 >= 0){
        if((k_y - 1)>=0){
            if(getSquare(k_x - 1, k_y - 1) == nullptr || ( getSquare(k_x - 1, k_y - 1) != nullptr && getColourB(k_x - 1, k_y - 1) != colour )){
                if(isKingSafeB(k_x, k_y, k_x - 1, k_y - 1)){
                    pieces_block[count_select] = std::make_pair(k_x,k_y);// adding king
                    ++count_select;
                    moves[count_move]= std::make_pair(k_x - 1, k_y - 1);
                    ++count_move;
                    std::cout << "Move piece: (" << pieces_avail[count_select].first << ", " << pieces_avail[count_select].second << ')' <<
                        " to (" << moves[count_move].first << ", " << moves[count_move].second << ") to lift check. " << '\n';
                }
            }
            
        }
        if(k_y + 1 < 8){
            if(getSquare(k_x - 1, k_y + 1) == nullptr || ( getSquare(k_x - 1, k_y + 1) != nullptr && getColourB(k_x - 1, k_y + 1) != colour )){
                if(isKingSafeB(k_x, k_y, k_x - 1, k_y + 1)){
                    pieces_block[count_select] = std::make_pair(k_x,k_y);// adding king
                    ++count_select;
                    moves[count_move]= std::make_pair(k_x - 1, k_y + 1);
                    ++count_move;
                    std::cout << "Move piece: (" << pieces_avail[count_select].first << ", " << pieces_avail[count_select].second << ')' <<
                        " to (" << moves[count_move].first << ", " << moves[count_move].second << ") to lift check. " << '\n';
                }     
            }  
        }
        if(getSquare(k_x - 1, k_y) == nullptr || ( getSquare(k_x - 1, k_y) != nullptr && getColourB(k_x - 1,k_y) != colour )){
            if(isKingSafeB(k_x, k_y, k_x - 1, k_y)){
                pieces_block[count_select] = std::make_pair(k_x,k_y);// adding king
                ++count_select;
                moves[count_move]= std::make_pair(k_x - 1, k_y);
                ++count_move;
                std::cout << "Move piece: (" << pieces_avail[count_select].first << ", " << pieces_avail[count_select].second << ')' <<
                    " to (" << moves[count_move].first << ", " << moves[count_move].second << ") to lift check. " << '\n';
            }
        }     
    }

    if( (k_x + 1 < 8) ){
        
        if((k_y - 1)>= 0){
            if(getSquare(k_x + 1, k_y - 1) == nullptr || ( getSquare(k_x + 1, k_y - 1) != nullptr && getColourB(k_x + 1,k_y - 1) != colour )){
                if(isKingSafeB(k_x, k_y, k_x + 1, k_y - 1)){
                    pieces_block[count_select] = std::make_pair(k_x,k_y);// adding king
                    ++count_select;
                    moves[count_move]= std::make_pair(k_x + 1, k_y - 1);
                    ++count_move;
                    std::cout << "Move piece: (" << pieces_avail[count_select].first << ", " << pieces_avail[count_select].second << ')' <<
                        " to (" << moves[count_move].first << ", " << moves[count_move].second << ") to lift check. " << '\n';
                }
            }
        }
        if(k_y + 1 < 8){
            if(getSquare(k_x + 1, k_y + 1) == nullptr || ( getSquare(k_x + 1, k_y - 1) != nullptr && getColourB(k_x + 1,k_y + 1) != colour )){
                if(isKingSafeB(k_x, k_y, k_x + 1, k_y + 1 )){
                    pieces_block[count_select] = std::make_pair(k_x,k_y);// adding king
                    ++count_select;
                    moves[count_move]= std::make_pair(k_x + 1, k_y + 1);
                    ++count_move;
                    std::cout << "Move piece: (" << pieces_avail[count_select].first << ", " << pieces_avail[count_select].second << ')' <<
                        " to (" << moves[count_move].first << ", " << moves[count_move].second << ") to lift check. " << '\n';
                }
            }    
        }
        if(getSquare(k_x + 1, k_y) == nullptr || ( getSquare(k_x + 1, k_y) != nullptr && getColourB(k_x + 1,k_y) != colour )){
            if(isKingSafeB(k_x, k_y, k_x + 1, k_y)){
                pieces_block[count_select] = std::make_pair(k_x,k_y);// adding king
                ++count_select;
                
                moves[count_move]= std::make_pair(k_x + 1, k_y);
                ++count_move;
                std::cout << "Move piece: (" << pieces_avail[count_select].first << ", " << pieces_avail[count_select].second << ')' <<
                    " to (" << moves[count_move].first << ", " << moves[count_move].second << ") to lift check. " << '\n';
            }
        }
        

    }

    if(k_y - 1 >= 0){//k_x
        if(getSquare(k_x, k_y - 1) == nullptr || ( getSquare(k_x, k_y - 1) != nullptr && getColourB(k_x,k_y - 1) != colour )){
            if(isKingSafeB(k_x, k_y, k_x , k_y - 1)){
                pieces_block[count_select] = std::make_pair(k_x,k_y);// adding king
                ++count_select;
                moves[count_move]= std::make_pair(k_x, k_y - 1);
                ++count_move;
                std::cout << "Move piece: (" << pieces_avail[count_select].first << ", " << pieces_avail[count_select].second << ')' <<
                    " to (" << moves[count_move].first << ", " << moves[count_move].second << ") to lift check. " << '\n';
            }
        }
    }
    if(k_y + 1 < 8){
        if(getSquare(k_x, k_y + 1) == nullptr || ( getSquare(k_x, k_y + 1) != nullptr && getColourB(k_x,k_y + 1) != colour )){
            if(isKingSafeB(k_x, k_y, k_x , k_y + 1)){
                std::cout << "why the fuck is this legal\n";
                pieces_block[count_select] = std::make_pair(k_x,k_y);// adding king
                ++count_select;
                moves[count_move]= std::make_pair(k_x, k_y + 1);
                ++count_move;
                std::cout << "Move piece: (" << pieces_avail[count_select].first << ", " << pieces_avail[count_select].second << ')' <<
                    " to (" << moves[count_move].first << ", " << moves[count_move].second << ") to lift check. " << '\n';
            }
        }
    }
    
    
    return possible;
}

bool Board::pieceBlockingCheck(int selectedX, int selectedY, int x, int y, char colour){
    bool safe{true};
    
    bool double_c{false};
    bool found{false};
    Piece* temp = nullptr;
    Piece* temp1 = nullptr;
    int k_x{};
    int k_y{};
    int attack_x{};
    int attack_y{};
    char attack_colour = ' ';
    if(colour == 'B'){
        char attack_colour = 'W';
        for(int i{}; i < 8; ++i){
            for(int j{}; j < 8; ++j){
                if(getSquare(i,j) != nullptr && getSymbolB(i, j) == 'K'){
                    k_x = i;
                    k_y = j;
                    found = true;
                    break;
                }
            }
            if(found == true){
                break;
            }
        }
    }else if(colour == 'W'){
        char attack_colour = 'B';
        for(int i{}; i < 8; ++i){
            for(int j{}; j < 8; ++j){
                if(getSquare(i,j) != nullptr && getSymbolB(i, j) == 'k'){
                    k_x = i;
                    k_y = j;
                    found = true;
                    break;
                }
            }
            if(found == true){
                break;
            }
        }

    }
    Piece* king = getSquare(k_x, k_y);
    char king_colour = getColourB(k_x, k_y);

    if(getSquare(x, y) != nullptr && king_colour != getColourB(x, y)){
        temp = getSquare(selectedX, selectedY); // store selected piece
        temp1 = getSquare(x, y); // store enemy piece at x,y
 
        setNull(x, y);// "take" piece
        initPiece(x,y, temp); // move selected piece to x,y
        if(isCheck(colour, attack_x, attack_y, k_x, k_y, double_c)){ // check if king is in check or not
            safe = false;
        }
        setNull(x ,y);// set x,y to null again
        initPiece(x, y, temp1);
        initPiece(selectedX , selectedY , temp);
    }
    if(getSquare(x, y) == nullptr){
        temp = getSquare(selectedX, selectedY);
        initPiece(x,y , temp);
        setNull(selectedX, selectedY);

        if(isCheck(colour, attack_x, attack_y, k_x, k_y, double_c)){
            safe = false;
        }
        initPiece(selectedX,selectedY, temp);
        setNull(x,y);
    }
    
    
    return safe;
    
}

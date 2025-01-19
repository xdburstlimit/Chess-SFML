#ifndef _PIECE_
#define _PIECE_

#include "constants.h"
#include <utility>
#include <iostream>

class Board;

class Piece{
    private:
        char symbol;
        char colour;
        bool isMoved, enPassant, capture_enPassant, castling_var;

    public:
        Piece(char symbol_param, char colour_param){
            symbol = symbol_param;
            colour = colour_param;
            isMoved = false;
            enPassant = false;
            capture_enPassant = false;
            castling_var = false;
        }

        virtual void display() = 0;
        virtual bool isValidMove(int x_i, int y_i, int x_f, int y_f, Board& board, char colour_param) = 0;// i = initial and f = final

        bool getisMoved(){
            return isMoved;
        }

        void setMoved(){
            isMoved = true;
        }

        bool getenPassant(){
            return enPassant;
        }

        void setenPassant(bool enPassant_param){
            enPassant = enPassant_param;
        }

        void setenPassant_capture(bool fr){
            capture_enPassant = fr;
        }

        void setCastled(){
            castling_var = true;
        }

        bool getCastled(){
            return castling_var;
        }

        char getSymbol(){
            return symbol;
        }
        char getColour(){
            return colour;
        }
};

#endif
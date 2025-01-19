#ifndef _PAWN_
#define _PAWN_

#include "Piece.h"
#include <iostream>
#include <iomanip>


class Pawn : public Piece{
    private:
        char symbol_param;
    public:
        Pawn(char colour_param);
        ~Pawn() = default; 
        virtual void display() override{
            std::cout << std::setw(2) << symbol_param;
        }
        virtual bool isValidMove(int x_i, int y_i, int x_f, int y_f, Board& board, char colour_param)override;    
};

#endif
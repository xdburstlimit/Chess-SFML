#ifndef _KNIGHT_
#define _KNIGHT_

#include "Piece.h"
#include <iostream>
#include <iomanip>

class Knight : public Piece{
    private:
        char symbol_param;
    public:
        Knight(char colour_param);
        ~Knight() = default; 
        virtual void display() override{
            std::cout << std::setw(2) << symbol_param;
        }
        virtual bool isValidMove(int x_i, int y_i, int x_f, int y_f, Board& board, char colour_param) override;
    
};

#endif
#ifndef _QUEEN_
#define _QUEEN_

#include "Piece.h"
#include <iostream>
#include <iomanip>

class Queen : public Piece{
    private:
        char symbol_param;
    public:
        Queen(char colour_param);
        ~Queen() = default; 
        virtual void display() override{
            std::cout << std::setw(2) << symbol_param;
        }
        virtual bool isValidMove(int x_i, int y_i, int x_f, int y_f, Board& board, char colour_param) override;
    
};

#endif
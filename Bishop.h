#ifndef _BISHOP_
#define _BISHOP_

#include "Piece.h"
#include <iostream>
#include <iomanip>

class Bishop : public Piece{
    private:
        char symbol_param;
    public:
        Bishop(char colour_param);
        ~Bishop() = default; 
        virtual void display() override{
            std::cout << std::setw(2) << symbol_param;
        }
        virtual bool isValidMove(int x_i, int y_i, int x_f, int y_f, Board& board, char colour_param) override;
    
};

#endif
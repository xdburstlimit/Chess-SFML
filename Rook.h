#ifndef _ROOK_
#define _ROOK_

#include "Piece.h"
#include <iostream>
#include <iomanip>

class Rook : public Piece{
    private:
        char symbol_param;
    public:
        Rook(char colour_param);
        ~Rook() = default;
        virtual void display() override{
            std::cout << std::setw(2) << symbol_param;
        }
        virtual bool isValidMove(int x_i, int y_i, int x_f, int y_f, Board& board, char colour_param) override;
    
};

#endif
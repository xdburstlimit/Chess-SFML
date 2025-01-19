#ifndef _KING_
#define _KING_

#include "Piece.h"
#include <iostream>
#include <iomanip>

class King : public Piece{
    private:
        char symbol_param;
    public:
        King(char colour_param);
        ~King() = default; 
        virtual void display() override{
            std::cout << std::setw(2) << symbol_param;
        }
        virtual bool isValidMove(int x_i, int y_i, int x_f, int y_f, Board& board, char colour_param) override;

        bool isKingSafe(int x_i, int y_i, int x_f, int y_f, Board& board); 
    
};

#endif